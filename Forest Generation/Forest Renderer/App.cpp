////#include "App.h"
#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include <string.h>
#include <sstream>

int numTrees = 2500;
//ArticulatedModel::Specification spec[2501];



class App : public GApp {
private:
	shared_ptr<ArticulatedModel>		 model[2501];
    LocalLightingEnvironment             environment;
	Texture::Ref                         bumpMap;
	Texture::Ref                         displacementMap;
	Texture::Ref                         modulationMap;
    
    float                                diffuseScalar;
    int                                  diffuseColorIndex;

    float                                specularScalar;
    int                                  specularColorIndex;

    float                                reflect;
    float                                shine;
    float                                bumpiness;
	float                                displacement;
	float								 modulation;

    ////////////////////////////////////
    // GUI

    /** For dragging the model */
    shared_ptr<ThirdPersonManipulator>   manipulator;
    Array<GuiText>                       colorList;

    void makeGui();
    void makeColorList();
    void makeLighting();
    void loadTextures();
    void configureShaderArgs(Args& args);

public:

    App(const GApp::Settings& settings) : GApp(settings), diffuseScalar(0.5f), specularScalar(0.0f), reflect(0.0f), shine(0.0f), bumpiness(0.0f), displacement(0.0f), modulation(0.0f) {}

    virtual void onInit();
    virtual void onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D);
};



void App::onInit() {
    createDeveloperHUD();
    window()->setCaption("Forest");
        
	for(int i = 0; i < 50; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			ArticulatedModel::Specification spec;

			std::stringstream transform (std::stringstream::in | std::stringstream::out);
			spec.filename = System::findDataFile("../../Data/Pine_Tree.obj");
			spec.scale = .05f;
			
			transform << "transformGeometry(\"root\", Matrix4::translation(" << (0.25f+.5*i) << ", " << "0, " << (-0.25f-.5*j) << "));";
			spec.preprocess.append(ArticulatedModel::Instruction(Any::parse(transform.str())));
			model[i*50 + j] = ArticulatedModel::create(spec);
		}
	}	
	
	ArticulatedModel::Specification spec;
	spec.filename = "../../Data/terrain.obj";
	spec.scale = 0.5f;
	spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("transformGeometry(\"root\", Matrix4::pitchDegrees(-90));")));
	model[2500] = ArticulatedModel::create(spec);
			

    makeLighting();
    makeColorList();
    makeGui();
	loadTextures();

    // Color 1 is red
    diffuseColorIndex = 4;
    // Last color is white
    specularColorIndex = colorList.size() - 1;
    
    m_debugCamera->setPosition(Vector3(1.0f, 1.0f, 2.5f));
    m_debugCamera->setFieldOfView(45 * units::degrees(), FOVDirection::VERTICAL);
    m_debugCamera->lookAt(Point3::zero());

    // Add axes for dragging and turning the model
    manipulator = ThirdPersonManipulator::create();
    addWidget(manipulator);

    // Turn off the default first-person camera controller and developer UI
    m_debugController->setEnabled(false);
    developerWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);
    showRenderingStats = false;
}

void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D) {
    rd->clear();

    rd->pushState(m_frameBuffer); {
        rd->clear();

        rd->setProjectionAndCameraMatrix(m_debugCamera->projection(), m_debugCamera->frame());
        
        Draw::skyBox(rd, environment.environmentMapArray[0].texture, environment.environmentMapArray[0].constant);
        
        rd->pushState(); {
            Array< shared_ptr<Surface> > mySurfaces;
            // Pose our model based on the manipulator axes
			for(int i = 0; i < numTrees + 1; i++)
			{
				//renderTreeLine(i, mySurfaces);
				if(model[i] != NULL)
				{
					model[i]->pose(mySurfaces, manipulator->frame());
				}
				else
				{
					break;
				}
			}
				
			// Set up shared arguments
            Args args;
            configureShaderArgs(args);
            
            // Send model geometry to the graphics card
            CFrame cframe;
            for (int i = 0; i < mySurfaces.size(); ++i) {

                // Downcast to UniversalSurface to access its fields
                shared_ptr<UniversalSurface> surface = dynamic_pointer_cast<UniversalSurface>(mySurfaces[i]);
                if (notNull(surface)) {
                    surface->getCoordinateFrame(cframe);
                    rd->setObjectToWorldMatrix(cframe);
                    surface->gpuGeom()->setShaderArgs(args);

                    // (If you want to manually set the material properties and vertex attributes
                    // for shader args, they can be accessed from the fields of the gpuGeom.)
                    LAUNCH_SHADER("../myprog.*", args);
                }
            }
        } rd->popState();
        
        // Render other objects, e.g., the 3D widgets
        Surface::render(rd, m_debugCamera->frame(), m_debugCamera->projection(), surface3D, surface3D, environment);   
    } rd->popState();

    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
    m_film->exposeAndRender(rd, m_debugCamera->filmSettings(), m_colorBuffer0, 1);

}
    
    
void App::configureShaderArgs(Args& args) {
    const shared_ptr<Light>&  light   = environment.lightArray[0];
    const Color3&       diffuseColor  = colorList[diffuseColorIndex].element(0).color(Color3::white()).rgb();
    const Color3&       specularColor = colorList[specularColorIndex].element(0).color(Color3::white()).rgb();
    
    
    // Viewer
    args.setUniform("wsEyePosition",       m_debugCamera->frame().translation);
    
    // Lighting
    args.setUniform("wsLightPos",          light->position().xyz());
    args.setUniform("wsLightDir",          light->position().xyz().direction());
    args.setUniform("lightColor",          light->color);
    args.setUniform("ambient",             Color3(0.3f));
    args.setUniform("environmentMap",      environment.environmentMapArray[0].texture);
    args.setUniform("environmentConstant", environment.environmentMapArray[0].constant);
    
    // UniversalMaterial
    args.setUniform("diffuseColor",        diffuseColor);
    args.setUniform("diffuseScalar",       diffuseScalar);
    
    args.setUniform("specularColor",       specularColor);
    args.setUniform("specularScalar",      specularScalar);
    
    args.setUniform("shine",               shine);
    args.setUniform("reflect",             reflect);

	args.setUniform("bumpMap",             bumpMap);
	args.setUniform("bumpiness",           bumpiness);

	args.setUniform("displacementMap",     displacementMap);
	args.setUniform("displacement",        displacement);

	args.setUniform("modulationMap",     modulationMap);
	args.setUniform("modulation",        modulation);
}


void App::makeColorList() {
    shared_ptr<GFont> iconFont = GFont::fromFile(System::findDataFile("icon.fnt"));

    // Characters in icon font that make a solid block of color
    static const char* block = "gggggg";

    float size = 18;
    int N = 10;
    colorList.append(GuiText(block, iconFont, size, Color3::black(), Color4::clear()));
    for (int i = 0; i < N; ++i) {
        colorList.append(GuiText(block, iconFont, size, Color3::rainbowColorMap((float)i / N), Color4::clear()));
    }
    colorList.append(GuiText(block, iconFont, size, Color3::white(), Color4::clear()));
}


void App::makeGui() {
    shared_ptr<GuiWindow> gui = GuiWindow::create("UniversalMaterial Parameters");    
    GuiPane* pane = gui->pane();

    pane->beginRow();
    pane->addSlider("Lambertian", &diffuseScalar, 0.0f, 1.0f);
    pane->addDropDownList("", colorList, &diffuseColorIndex)->setWidth(80);
    pane->endRow();

    pane->beginRow();
    pane->addSlider("Glossy",    &specularScalar, 0.0f, 1.0f);
    pane->addDropDownList("", colorList, &specularColorIndex)->setWidth(80);
    pane->endRow();
    
    pane->addSlider("Mirror",       &reflect, 0.0f, 1.0f);
    pane->addSlider("Smoothness",   &shine, 1.0f, 100.0f);
    pane->addSlider("Bumpiness",    &bumpiness, 0.0f, 1.0f);
	pane->addSlider("Displacement", &displacement, 0.0f, 1.0f);
	pane->addSlider("Modulation",   &modulation, 0.0f, 1.0f);
    
    gui->pack();
    addWidget(gui);
    gui->moveTo(Point2(10, 10));
}


void App::makeLighting() {
    environment.lightArray.append(Light::directional("Light", Vector3(1.0f, 1.0f, 1.0f), Color3(1.0f), false));

    // The environmentMap is a cube of six images that represents the incoming light to the scene from
    // the surrounding environment.  G3D specifies all six faces at once using a wildcard and loads
    // them into an OpenGL cube map.
 
    Texture::Specification environmentMapTexture;
    environmentMapTexture.filename   = FilePath::concat(System::findDataFile("noonclouds"), "noonclouds_*.png");
    
    environmentMapTexture.dimension  = Texture::DIM_CUBE_MAP;
    environmentMapTexture.settings   = Texture::Settings::cubeMap();
    environmentMapTexture.preprocess = Texture::Preprocess::gamma(2.1f);
    // Reduce memory size required to work on older GPUs
    environmentMapTexture.preprocess.scaleFactor = 0.25f;
    environmentMapTexture.settings.interpolateMode = Texture::BILINEAR_NO_MIPMAP;
    
    environment.environmentMapArray.append(Texture::create(environmentMapTexture), 1.0f);
}

void App::loadTextures() {
	
	// load a standard grayscale image, and use preprocess tools to convert it to a normalmap
	bumpMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT, 
		Texture::Settings::defaults(), Texture::Preprocess::normalMap());

	displacementMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);

	modulationMap = Texture::fromFile("../lightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);

	// how to load a regular texture...
	//anotherMap = Texture::fromFile("something.png", ImageFormat::RGB8(), Texture::DIM_2D_NPOT);

}

G3D_START_AT_MAIN();

int main(int argc, const char* argv[]) {
    initGLG3D();

#   ifdef G3D_WINDOWS
      if (! FileSystem::exists("../myprog.pix", false) && FileSystem::exists("G3D.sln", false)) {
          // The program was started from within Visual Studio and is
          // running with cwd = G3D/VC10/.  Change to
          // the appropriate sample directory.
          chdir("../samples/starter/data-files");
      } else if (FileSystem::exists("data-files")) {
          chdir("data-files");
      }
#   endif

    GApp::Settings settings(argc, argv);  
    settings.colorGuardBandThickness  = Vector2int16(0, 0);
    settings.depthGuardBandThickness  = Vector2int16(0, 0);

	//if(argc > 1)
//		modelName = argv[1];

    return App(settings).run();
}
