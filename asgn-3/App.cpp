/**
  @file App.cpp
 */
#include "App.h"
#include "World.h"

#include <string>
#include <sstream>
#include <iostream>

G3D_START_AT_MAIN();

float maxDist = 0;

void print(float value)
{
	std::wstringstream s;
	s << L"" <<value <<" ";
	std::wstring ws = s.str();
	OutputDebugString(ws.c_str());
}


int main(int argc, char** argv) {
    GApp::Settings settings;
    settings.window.caption     = "G3D Ray Trace Sample";
    settings.window.width       = 960; 
    settings.window.height      = 640;

    return App(settings).run();
}


App::App(const GApp::Settings& settings) : 
    GApp(settings),
    m_maxBounces(3), 
    m_raysPerPixel(1),
	m_fogginess(0),
    m_world(NULL) {
    catchCommonExceptions = false;
}


void App::onInit() {
    message("Loading...");
	
    m_world = new World();
	
    showRenderingStats = false;
    createDeveloperHUD();
    developerWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);
    m_debugCamera->filmSettings().setAntialiasingEnabled(true);
    m_debugCamera->filmSettings().setContrastToneCurve();

    // Starting position
    m_debugCamera->setFrame(CFrame::fromXYZYPRDegrees(24.3f, 0.4f, 2.5f, 68.7f, 1.2f, 0.0f));
    m_debugCamera->frame();

    makeGUI();

    // Force re-render on first frame
    m_prevCFrame = CFrame(Matrix3::zero());
}


void App::makeGUI() {
    shared_ptr<GuiWindow> window = GuiWindow::create("Controls", debugWindow->theme(), Rect2D::xywh(0,0,0,0), GuiTheme::TOOL_WINDOW_STYLE);
    GuiPane* pane = window->pane();
    pane->addLabel("Use WASD keys + right mouse to move");
    pane->addButton("Render High Res.", this, &App::onRender);
    
    pane->addNumberBox("Rays per pixel", &m_raysPerPixel, "", GuiTheme::LINEAR_SLIDER, 1, 30, 1);
    pane->addNumberBox("Max bounces", &m_maxBounces, "", GuiTheme::LINEAR_SLIDER, 1, 16, 1);
	pane->addSlider("Fogginess", &m_fogginess, 0.0f, .1f);
	//pane->addNumberBox("Fogginess", &m_fogginess, "", GuiTheme::LINEAR_SLIDER, 1, 20, 1);
	pane->addNumberBox("Focal Length", &m_focalLength, "", GuiTheme::LINEAR_SLIDER, 1, 50, 1);
    window->pack();

    window->setVisible(true);
    addWidget(window);
}


void App::onGraphics(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D, Array<shared_ptr<Surface2D> >& surface2D) {
    // Update the preview image only while moving
    if (! m_prevCFrame.fuzzyEq(m_debugCamera->frame())) {
        rayTraceImage(0.33f, 1);
        m_prevCFrame = m_debugCamera->frame();
    }

    if (m_result) {
        rd->push2D();
        rd->setTexture(0, m_result);
        Draw::rect2D(rd->viewport(), rd);
        rd->pop2D();
    }

    Surface2D::sortAndRender(rd, surface2D);
}


void App::onCleanup() {
    delete m_world;
    m_world = NULL;
}


static G3D::Random rnd(0xF018A4D2, false);

Radiance3 App::rayTrace(const Ray& ray, World* world, int bounce) {
    Radiance3 radiance = Radiance3::zero();
    const float BUMP_DISTANCE = 0.0001f;

    float dist = (float)inf();
    const shared_ptr<Surfel>& surfel = world->intersect(ray, dist);
	
	if (notNull(surfel)) {

        // Shade this point (direct illumination)
        for (int L = 0; L < world->lightArray.size(); ++L) {
            const shared_ptr<Light>& light = world->lightArray[L];

            // Shadow rays
            if (world->lineOfSight(surfel->location + surfel->geometricNormal * BUMP_DISTANCE, light->position().xyz())) {
                Vector3 w_i = light->position().xyz() - surfel->location;
                const float distance2 = w_i.squaredLength();
                w_i /= sqrt(distance2);

                // Biradiance
                const Biradiance3& B_i = light->color / (4.0f * pif() * distance2);
				
                radiance += 
                    surfel->finiteScatteringDensity(w_i, -ray.direction()) * 
                    B_i *
                    max(0.0f, w_i.dot(surfel->shadingNormal));
				
                debugAssert(radiance.isFinite());
            }
        }

        // Indirect illumination
        // Ambient
        radiance += surfel->reflectivity(m_rng) * world->ambient;

        // Specular
        if (bounce < m_maxBounces) {
            // Perfect reflection and refraction
            Surfel::ImpulseArray impulseArray;
            surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);
                
            for (int i = 0; i < impulseArray.size(); ++i) {
                const Surfel::Impulse& impulse = impulseArray[i];
                // Bump along normal *in the outgoing ray direction*. 
                const Vector3& offset = surfel->geometricNormal * sign(impulse.direction.dot(surfel->geometricNormal)) * BUMP_DISTANCE;
                const Ray& secondaryRay = Ray::fromOriginAndDirection(surfel->location + offset, impulse.direction);
                debugAssert(secondaryRay.direction().isFinite());
                radiance += rayTrace(secondaryRay, world, bounce + 1) * impulse.magnitude;
                debugAssert(radiance.isFinite());
            }
        }

		// Add radiance proportional to the distance and fogginess. Divide by 2 so that there isn't too much fog
		radiance += (radiance.one() * dist * m_fogginess)/2;

    } else {
        // Hit the sky
        radiance = world->ambient;

		// Add radiance proportional to fogginess. Multiply by 10 so the fog is noticeable
		radiance += (radiance.one() * m_fogginess * 10);
	}

	return radiance;
}


void App::message(const std::string& msg) const {
    renderDevice->clear();
    renderDevice->push2D();
        debugFont->draw2D(renderDevice, msg, renderDevice->viewport().center(), 12, 
            Color3::white(), Color4::clear(), GFont::XALIGN_CENTER, GFont::YALIGN_CENTER);
    renderDevice->pop2D();

    // Force update so that we can see the message
    renderDevice->swapBuffers();
}


void App::onRender() {
    // Show message
    message("Rendering...");

    Stopwatch timer;
    rayTraceImage(1.0f, m_raysPerPixel);
    timer.after("Trace");
    debugPrintf("%f s\n", timer.elapsedTime());
//    m_result->toImage3uint8()->save("result.png");
}


void App::trace(int x, int y) {
    Color3 sum = Color3::black();
    if (m_currentRays == 1) {
        sum = rayTrace(m_debugCamera->worldRay(x + 0.5f, y + 0.5f, m_currentImage->rect2DBounds()), m_world);
    } else {
        for (int i = 0; i < m_currentRays; ++i) {
            sum += rayTrace(m_debugCamera->worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds()), m_world);
        }
    }
    m_currentImage->set(x, y, sum / (float)m_currentRays);
}


void App::rayTraceImage(float scale, int numRays) {

    int width  = int(window()->width()  * scale);
    int height = int(window()->height() * scale);
    
    if (isNull(m_currentImage) || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }
    m_currentRays = numRays;
    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::trace);

    // Post-process
    shared_ptr<Texture> src = Texture::fromImage("Source", m_currentImage);
    if (m_result) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, m_debugCamera->filmSettings(), src, m_result);
}
