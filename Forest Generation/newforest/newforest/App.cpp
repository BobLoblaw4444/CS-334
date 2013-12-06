#include "App.h"
#include <string.h>
#include <fstream>
#include <sstream>

G3D_START_AT_MAIN();

int main(int argc, const char* argv[]) {
    initGLG3D();

    GApp::Settings settings(argc, argv);
    
    settings.window.caption     = argv[0];
    settings.window.width       = 1280; 
    settings.window.height      = 720;

    return App(settings).run();
}


App::App(const GApp::Settings& settings) : GApp(settings) {
}


void App::onInit() {
    GApp::onInit();
    // Called before the application loop begins.  Load data here and
    // not in the constructor so that common exceptions will be
    // automatically caught.
    showRenderingStats    = false;

    // For higher-quality screenshots:
    // developerWindow->videoRecordDialog->setScreenShotFormat("PNG");
    // developerWindow->videoRecordDialog->setCaptureGui(false);

    m_scene = Scene::create();
    setScene(m_scene);

    m_firstPersonMode = false;

    m_playerName = "player";

    makeGBuffer();
    makeGUI();

    //developerWindow->cameraControlWindow->moveTo(Point2(developerWindow->cameraControlWindow->rect().x0(), 0));
    loadScene("Level");
    //setActiveCamera(m_scene->typedEntity<Camera>("camera"));
	m_debugCamera->setPosition(Vector3(1.0f, 1.0f, 2.5f));
    m_debugCamera->setFieldOfView(45 * units::degrees(), FOVDirection::VERTICAL);
	m_debugCamera->lookAt(Point3::zero());
	m_debugController->setEnabled(false);
	setActiveCamera(m_debugCamera);
    developerWindow->sceneEditorWindow->setPreventEntitySelect(true);

	std::ifstream heightMap("../../Data/heightmap.txt");
	std::ifstream treeMap("../../Data/treemap.txt");

	std::string heightLine;
	std::string treeLine;

	Any x;
	x.load("tree.txt");

	// For each square on the 50x50 terrain, add the appropriate tree to the model list
	for(int i = 0; i < 50; i++)
	{
		std::getline(heightMap, heightLine);
		std::getline(treeMap, treeLine);

		std::istringstream heightStream(heightLine);
		std::istringstream treeStream(treeLine);

		for(int j = 0; j < 50; j++)
		{
			float height;
			heightStream >> height;

			int treeType;
			treeStream >> treeType;

			switch(treeType)
			{
			case 1:

				x["model"]="smallTreeModel";
				x["frame"]=Point3(.5f+i,height,-.5f-j);
			
				m_scene->createEntity("VisibleEntity","newTree",x);
				break;
			case 2:

				x["model"]="treeModel";
				x["frame"]=Point3(.5f+i,height,-.5f-j);
			
				m_scene->createEntity("VisibleEntity","newTree",x);
				break;
			case 3:
				x["model"]="bigTreeModel";
				x["frame"]=Point3(.5f+i,height,-.5f-j);
			
				m_scene->createEntity("VisibleEntity","newTree",x);
					break;
			}
		}
	}
}


void App::makeGBuffer() {
    // If you do not use motion blur or deferred shading, you can avoid allocating the GBuffer here to save resources
    GBuffer::Specification specification;

    specification.format[GBuffer::Field::SS_POSITION_CHANGE]   = GLCaps::supportsTexture(ImageFormat::RG8()) ? ImageFormat::RG8() : ImageFormat::RGBA8();
    specification.encoding[GBuffer::Field::SS_POSITION_CHANGE] = Vector2(128.0f, -64.0f);

    specification.format[GBuffer::Field::DEPTH_AND_STENCIL]  = ImageFormat::DEPTH32();
    specification.depthEncoding = DepthEncoding::HYPERBOLIC;

    specification.format[GBuffer::Field::WS_NORMAL]  = ImageFormat::RGB32F();
    specification.encoding[GBuffer::Field::WS_NORMAL] = Vector2(0.5f, 0.5f);

    m_gbuffer = GBuffer::create(specification);

    m_gbuffer->resize(renderDevice->width(), renderDevice->height());
    m_gbuffer->texture(GBuffer::Field::SS_POSITION_CHANGE)->visualization = Texture::Visualization::unitVector();

    // Share the depth buffer with the forward-rendering pipeline
    m_depthBuffer = m_gbuffer->texture(GBuffer::Field::DEPTH_AND_STENCIL);
    m_frameBuffer->set(Framebuffer::DEPTH, m_depthBuffer);
}


void App::makeGUI() {
    createDeveloperHUD();

    debugWindow->setVisible(false);
    developerWindow->videoRecordDialog->setEnabled(false);
    developerWindow->sceneEditorWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);

    debugWindow->pack();
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));
}


void App::onAI() {
    GApp::onAI();
    // Add non-simulation game logic and AI code here
}


void App::onNetwork() {
    GApp::onNetwork();
    // Poll net messages here
}


void App::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
    GApp::onSimulation(rdt, sdt, idt);



    // Example GUI dynamic layout code.  Resize the debugWindow to fill
    // the screen horizontally.
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));

}



void App::onPose(Array<shared_ptr<Surface> >& posed3D, Array<shared_ptr<Surface2D> >& posed2D) {
    m_widgetManager->onPose(posed3D, posed2D);
    

        scene()->onPose(posed3D);
  
}


void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& allSurfaces) {
    // Bind the main frameBuffer
    rd->pushState(m_frameBuffer); {

        rd->setProjectionAndCameraMatrix(activeCamera()->projection(), activeCamera()->frame());

        m_gbuffer->resize(rd->width(), rd->height());
        m_gbuffer->prepare(rd, activeCamera(),  0, -(float)previousSimTimeStep(), m_settings.depthGuardBandThickness, m_settings.colorGuardBandThickness);
        if (! m_settings.colorGuardBandThickness.isZero()) {
            rd->setGuardBandClip2D(m_settings.colorGuardBandThickness);
        }        
        
        // Cull and sort
        Array<shared_ptr<Surface> > sortedVisibleSurfaces;
        Surface::cull(activeCamera()->frame(), activeCamera()->projection(), rd->viewport(), allSurfaces, sortedVisibleSurfaces);
        Surface::sortBackToFront(sortedVisibleSurfaces, activeCamera()->frame().lookVector());
        
        // Early-Z pass
        static const bool renderTransmissiveSurfaces = false;
        Surface::renderDepthOnly(rd, sortedVisibleSurfaces, CullFace::BACK, renderTransmissiveSurfaces);
        rd->setDepthWrite(false);
        
        // Render velocity buffer (if needed)
        if (activeCamera()->motionBlurSettings().enabled()) {
            Surface::renderIntoGBuffer(rd, sortedVisibleSurfaces, m_gbuffer, activeCamera()->previousFrame());
        }
        LocalLightingEnvironment environment = m_scene->localLightingEnvironment();
        environment.ambientOcclusion = m_ambientOcclusion;

        // Compute AO
        m_ambientOcclusion->update(rd, environment.ambientOcclusionSettings, activeCamera(), m_depthBuffer);
        
        // Compute shadow maps and forward-render visible surfaces
        Surface::render(rd, activeCamera()->frame(), activeCamera()->projection(), sortedVisibleSurfaces, allSurfaces, environment);
        rd->setDepthWrite(true);
        
        // Call to make the App show the output of debugDraw(...)
        drawDebugShapes();
        
        // Post-process special effects
        m_depthOfField->apply(rd, m_colorBuffer0, m_depthBuffer, activeCamera(), m_settings.depthGuardBandThickness - m_settings.colorGuardBandThickness);

    } rd->popState();

    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
    m_film->exposeAndRender(rd, activeCamera()->filmSettings(), m_colorBuffer0, 1);

}
