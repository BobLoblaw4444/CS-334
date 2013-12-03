#include "TerrainGenerator.h"

//#include <G3D/G3DAll.h>
//#include <GLG3D/GLG3D.h>

#include <string>

std::string modelName;

//class App : public GApp {
//private:
//    shared_ptr<ArticulatedModel>         model;
//
//    LocalLightingEnvironment             environment;
//	//Texture::Ref                         bumpMap;
//	//Texture::Ref                         displacementMap;
//	//Texture::Ref                         modulationMap;
//    
//    //float                                diffuseScalar;
//    int                                  diffuseColorIndex;
//
//    //float                                specularScalar;
//    int                                  specularColorIndex;
//
//    //float                                reflect;
//    //float                                shine;
//    //float                                bumpiness;
//	//float                                displacement;
//	//float								 modulation;
//
//    ////////////////////////////////////
//    // GUI
//
//    /** For dragging the model */
//    shared_ptr<ThirdPersonManipulator>   manipulator;
//    Array<GuiText>                       colorList;
//
//    void makeGui();
//    void makeColorList();
//    void makeLighting();
//    void loadTextures();
//    void configureShaderArgs(Args& args);
//
//public:
//
//    App(const GApp::Settings& settings) : GApp(settings){}
//
//    virtual void onInit();
//    virtual void onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D);
//};
//
//void App::onInit() {
//    createDeveloperHUD();
//    window()->setCaption("Forest");
//        
//    ArticulatedModel::Specification spec;
//
//	std::string dataFile = modelName;
//	
//	spec.filename = System::findDataFile(dataFile);
//    spec.stripMaterials = true;
//
//    model = ArticulatedModel::create(spec);
//
//    makeLighting();
//    makeColorList();
//    makeGui();
//	loadTextures();
//
//    // Color 1 is red
//    diffuseColorIndex = 8;
//    // Last color is white
//    specularColorIndex = colorList.size() - 1;
//    
//    m_debugCamera->setPosition(Vector3(1.0f, 1.0f, 2.5f));
//    m_debugCamera->setFieldOfView(45 * units::degrees(), FOVDirection::VERTICAL);
//    m_debugCamera->lookAt(Point3::zero());
//
//    // Add axes for dragging and turning the model
//    manipulator = ThirdPersonManipulator::create();
//    addWidget(manipulator);
//
//    // Turn off the default first-person camera controller and developer UI
//    m_debugController->setEnabled(false);
//    developerWindow->setVisible(false);
//    developerWindow->cameraControlWindow->setVisible(false);
//    showRenderingStats = false;
//}
//
//void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D) {
//    rd->clear();
//
//    rd->pushState(m_frameBuffer); {
//        rd->clear();
//
//        rd->setProjectionAndCameraMatrix(m_debugCamera->projection(), m_debugCamera->frame());
//        
//        Draw::skyBox(rd, environment.environmentMapArray[0].texture, environment.environmentMapArray[0].constant);
//        
//        rd->pushState(); {
//            Array< shared_ptr<Surface> > mySurfaces;
//            // Pose our model based on the manipulator axes
//            model->pose(mySurfaces, manipulator->frame());
//            
//            // Set up shared arguments
//            Args args;
//            configureShaderArgs(args);
//            
//            //Send model geometry to the graphics card
//            CFrame cframe;
//            for (int i = 0; i < mySurfaces.size(); ++i) {
//
//                // Downcast to UniversalSurface to access its fields
//                shared_ptr<UniversalSurface> surface = dynamic_pointer_cast<UniversalSurface>(mySurfaces[i]);
//                if (notNull(surface)) {
//                    surface->getCoordinateFrame(cframe);
//                    rd->setObjectToWorldMatrix(cframe);
//                    surface->gpuGeom()->setShaderArgs(args);
//
//                    // (If you want to manually set the material properties and vertex attributes
//                    // for shader args, they can be accessed from the fields of the gpuGeom.)
//                   // LAUNCH_SHADER("../myprog.*", args);
//                }
//            }
//        } rd->popState();
//        
//        // Render other objects, e.g., the 3D widgets
//        Surface::render(rd, m_debugCamera->frame(), m_debugCamera->projection(), surface3D, surface3D, environment);   
//    } rd->popState();
//
//    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
//    m_film->exposeAndRender(rd, m_debugCamera->filmSettings(), m_colorBuffer0, 1);
//
//}
//
//void App::configureShaderArgs(Args& args) {
//    const shared_ptr<Light>&  light   = environment.lightArray[0];
//    const Color3&       diffuseColor  = colorList[diffuseColorIndex].element(0).color(Color3::white()).rgb();
//    const Color3&       specularColor = colorList[specularColorIndex].element(0).color(Color3::white()).rgb();
//    
//    
//    // Viewer
//    args.setUniform("wsEyePosition",       m_debugCamera->frame().translation);
//    
//    // Lighting
//    args.setUniform("wsLightPos",          light->position().xyz());
//    args.setUniform("wsLightDir",          light->position().xyz().direction());
//    args.setUniform("lightColor",          light->color);
//    args.setUniform("ambient",             Color3(0.3f));
//    args.setUniform("environmentMap",      environment.environmentMapArray[0].texture);
//    args.setUniform("environmentConstant", environment.environmentMapArray[0].constant);
//    
//    // UniversalMaterial
//    /*args.setUniform("diffuseColor",        diffuseColor);
//    args.setUniform("diffuseScalar",       diffuseScalar);
//    
//    args.setUniform("specularColor",       specularColor);
//    args.setUniform("specularScalar",      specularScalar);
//    
//    args.setUniform("shine",               shine);
//    args.setUniform("reflect",             reflect);
//
//	args.setUniform("bumpMap",             bumpMap);
//	args.setUniform("bumpiness",           bumpiness);
//
//	args.setUniform("displacementMap",     displacementMap);
//	args.setUniform("displacement",        displacement);
//
//	args.setUniform("modulationMap",     modulationMap);
//	args.setUniform("modulation",        modulation);*/
//}
//
//void App::makeColorList() {
//    shared_ptr<GFont> iconFont = GFont::fromFile(System::findDataFile("icon.fnt"));
//
//    // Characters in icon font that make a solid block of color
//    static const char* block = "gggggg";
//
//    float size = 18;
//    int N = 10;
//    colorList.append(GuiText(block, iconFont, size, Color3::black(), Color4::clear()));
//    for (int i = 0; i < N; ++i) {
//        colorList.append(GuiText(block, iconFont, size, Color3::rainbowColorMap((float)i / N), Color4::clear()));
//    }
//    colorList.append(GuiText(block, iconFont, size, Color3::white(), Color4::clear()));
//}
//
//void App::makeGui() {
//    shared_ptr<GuiWindow> gui = GuiWindow::create("UniversalMaterial Parameters");    
//    GuiPane* pane = gui->pane();
//
//    //pane->beginRow();
//   /* pane->addSlider("Lambertian", &diffuseScalar, 0.0f, 1.0f);
//    pane->addDropDownList("", colorList, &diffuseColorIndex)->setWidth(80);
//    pane->endRow();
//
//    pane->beginRow();
//    pane->addSlider("Glossy",    &specularScalar, 0.0f, 1.0f);
//    pane->addDropDownList("", colorList, &specularColorIndex)->setWidth(80);
//    pane->endRow();
//    
//    pane->addSlider("Mirror",       &reflect, 0.0f, 1.0f);
//    pane->addSlider("Smoothness",   &shine, 1.0f, 100.0f);
//    pane->addSlider("Bumpiness",    &bumpiness, 0.0f, 1.0f);
//	pane->addSlider("Displacement", &displacement, 0.0f, 1.0f);
//	pane->addSlider("Modulation",   &modulation, 0.0f, 1.0f);
//    */
//    gui->pack();
//    addWidget(gui);
//    gui->moveTo(Point2(10, 10));
//}
//
//
//void App::makeLighting() {
//    environment.lightArray.append(Light::directional("Light", Vector3(1.0f, 1.0f, 1.0f), Color3(1.0f), false));
//
//    // The environmentMap is a cube of six images that represents the incoming light to the scene from
//    // the surrounding environment.  G3D specifies all six faces at once using a wildcard and loads
//    // them into an OpenGL cube map.
// 
//    Texture::Specification environmentMapTexture;
//    environmentMapTexture.filename   = FilePath::concat(System::findDataFile("noonclouds"), "noonclouds_*.png");
//    
//    environmentMapTexture.dimension  = Texture::DIM_CUBE_MAP;
//    environmentMapTexture.settings   = Texture::Settings::cubeMap();
//    environmentMapTexture.preprocess = Texture::Preprocess::gamma(2.1f);
//    // Reduce memory size required to work on older GPUs
//    environmentMapTexture.preprocess.scaleFactor = 0.25f;
//    environmentMapTexture.settings.interpolateMode = Texture::BILINEAR_NO_MIPMAP;
//    
//    environment.environmentMapArray.append(Texture::create(environmentMapTexture), 1.0f);
//}
//
//void App::loadTextures() {
//	
//	// load a standard grayscale image, and use preprocess tools to convert it to a normalmap
//	/*bumpMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT, 
//		Texture::Settings::defaults(), Texture::Preprocess::normalMap());
//
//	displacementMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);
//
//	modulationMap = Texture::fromFile("../lightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);
//	*/
//	// how to load a regular texture...
//	//anotherMap = Texture::fromFile("something.png", ImageFormat::RGB8(), Texture::DIM_2D_NPOT);
//
//}
//
//G3D_START_AT_MAIN();

int main()
{
	//initGLG3D();

//	#   ifdef G3D_WINDOWS
//      if (! FileSystem::exists("../myprog.pix", false) && FileSystem::exists("G3D.sln", false)) {
//          // The program was started from within Visual Studio and is
//          // running with cwd = G3D/VC10/.  Change to
//          // the appropriate sample directory.
//          chdir("../samples/starter/data-files");
//      } else if (FileSystem::exists("data-files")) {
//          chdir("data-files");
//      }
//#   endif
//
//	GApp::Settings settings(argc, argv);  
//    settings.colorGuardBandThickness  = Vector2int16(0, 0);
//    settings.depthGuardBandThickness  = Vector2int16(0, 0);

	TerrainGenerator* tg = new TerrainGenerator();

	tg->generateTerrain();

	modelName = "../data-files/terrain.obj";

	//return App(settings).run();
}

