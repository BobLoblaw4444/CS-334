////#include "App.h"
////#include <stdlib.h>
////#include <GL/glut.h>
////
//#include <fstream>
//#include <string>
//
//using std::string;
////
//#include "App.h"
//MyCamera myCamera;
//
//float vertexArray[16000];
////int faceArray[10000];
//int vertexIndex = 1;
//int vertexNum = 0;
////
////void init(void) 
////{
////   glClearColor (0.0, 0.0, 0.0, 0.0);
////   glShadeModel (GL_FLAT);
////}
////
//void parseObj(string modelPath)
//{
//	int count = 1;
//	std::ifstream model(modelPath);
//	string line;
//	while (count < 16)
//	{
//		std::getline(model, line);
//		count++;
//		/*if(++count == 6874)
//			break;*/
//
//		if(line[0] == 'v')
//		{
//			string val;
//			val.clear();
//
//			int j = 2;
//			for(int j = 2; j < line.size(); j++)
//			{
//				if(line[j] == ' ')
//				{
//					vertexArray[vertexIndex] = stof(val);
//					vertexIndex++;
//					val.clear();
//				}
//				else
//				{
//					val += line[j];
//				}
//			}
//			
//			vertexArray[vertexIndex] = stof(val);
//			vertexIndex++;
//			vertexNum++;
//
//			if(vertexNum % 3 == 0)
//			{
//				glBegin(GL_TRIANGLES);
//				glColor3f (0.0, 1.0, 0.0);
//				glVertex3f(vertexArray[vertexIndex-9], vertexArray[vertexIndex-8], vertexArray[vertexIndex-7]);
//				glVertex3f(vertexArray[vertexIndex-6], vertexArray[vertexIndex-5], vertexArray[vertexIndex-4]);
//				glVertex3f(vertexArray[vertexIndex-3], vertexArray[vertexIndex-2], vertexArray[vertexIndex-1]);
//				glEnd();
//			}
//		}
//
//	}
//	//model.close();
//}
//
////void display(void)
////{
////   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////   //glTranslatef(0,0,-50); //translates the current matrix 0 in x, 0 in y and -100 in z
////   //glColor3f (1.0, 1.0, 1.0);
////   //glLoadIdentity ();             /* clear the matrix */
////           /* viewing transformation  */
////   gluLookAt (25.0, 0.0, -150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
////   //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
////   
////   //glBegin(GL_TRIANGLES);
////   
////   
////   for(int i= 0; i < vertexIndex; i++)
////   {
////		if(i % 3 == 0)
////		{
////			glBegin(GL_TRIANGLES);
////			glColor3f (0.0, 1.0, 0.0);
////			/*glVertex3f(0.0,0.0,-2.0);
////			glVertex3f(1.0,0.0,-2.0);
////			glVertex3f(0.0,1.0,-2.0);*/
////			glVertex3f(vertexArray[vertexIndex-i-9], vertexArray[vertexIndex-i-8], vertexArray[vertexIndex-i-7]);
////			glVertex3f(vertexArray[vertexIndex-i-6], vertexArray[vertexIndex-i-5], vertexArray[vertexIndex-i-4]);
////			glVertex3f(vertexArray[vertexIndex-i-3], vertexArray[vertexIndex-i-2], vertexArray[vertexIndex-i-1]);
////			glEnd();
////		}
////   }
////   //glFlush ();
////   //glEnd();
////   //
////   glutSwapBuffers();      //swaps the front and back buffers
////}
////
//////void reshape (int w, int h)
//////{
//////   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
//////   glMatrixMode (GL_PROJECTION);
//////   glLoadIdentity ();
//////   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//////   glMatrixMode (GL_MODELVIEW);
//////}
////
////
////void keyboard(unsigned char key, int x, int y)
////{
////	
////	float fraction = 0.2f;
////	switch (key)
////	{
////		case 'a': //turn left
////			myCamera.angleY -= 0.01f;
////			myCamera.dirX = sin(myCamera.angleY);
////			myCamera.dirZ = -cos(myCamera.angleY);
////			break;
////
////		case 'd'://turn right
////			myCamera.angleY += 0.01f;
////			myCamera.dirX = sin(myCamera.angleY);
////			myCamera.dirZ = -cos(myCamera.angleY);
////			break;
////
////
////		case 'w'://forward
////			myCamera.xPos += myCamera.dirX * fraction;
////			myCamera.zPos -= myCamera.dirZ * fraction;
////			myCamera.yPos += myCamera.dirY * fraction;
////			break;
////
////		case 's'://backwards
////			myCamera.xPos -= myCamera.dirX * fraction;
////			myCamera.zPos += myCamera.dirZ * fraction;
////			myCamera.yPos -= myCamera.dirY * fraction;
////			break;
////
////	//if (ui->keyDown(GKey::KP4)) {//LEFT
////	//	float Bx=0,By=1,Bz=0;//cross product
////	//	float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
////	//	float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
////	//	float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
////	//	myCamera.xPos -= xP * fraction;
////	//	myCamera.zPos -= zP * fraction;
////	//	myCamera.yPos -= yP * fraction;
////	//}
////
////	//if (ui->keyDown(GKey::KP6)) {//RIGHT
////	//	float Bx=0,By=1,Bz=0;//cross product
////	//	float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
////	//	float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
////	//	float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
////	//	myCamera.xPos += xP * fraction;
////	//	myCamera.zPos += zP * fraction;
////	//	myCamera.yPos += yP * fraction;
////	}
////	gluLookAt(myCamera.xPos, myCamera.yPos, myCamera.zPos, myCamera.xPos+myCamera.dirX, myCamera.yPos+myCamera.dirY, myCamera.zPos+myCamera.dirZ, 0, 1, 0);
////	glutDisplayFunc(display);
////}
////
////int main(int argc, char** argv)
////{
////	glutInit(&argc, argv);
////	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
////	glutInitWindowSize (500, 500); 
////	glutInitWindowPosition (100, 100);
////	glutCreateWindow ("Forest!");
////	glutKeyboardFunc(keyboard);
////	parseObj("../Data/terrain.obj");
////	glutDisplayFunc(display); 
////	
////	//init();
////	glMatrixMode(GL_PROJECTION);   //changes the current matrix to the projection matrix
////	
////	//sets up the projection matrix for a perspective transform
////	gluPerspective(45, 	//view angle
////	          	1.0,    //aspect ratio
////	          	10.0,   //near clip
////	          	200.0); //far clip
////	
////	//glutReshapeFunc(reshape);
////	glMatrixMode(GL_MODELVIEW);   //changes the current matrix to the modelview matrix
////	
////	glutMainLoop();
////
////	return 0;
////}
//
///**
//  @file App.cpp
// */
////#include "App.h"
//
//#define w 900
//#define h 600
//
//float frameNum;
//
//
//G3D_START_AT_MAIN();
//
//int main(int argc, char** argv) {
//    GApp::Settings settings;
//    settings.window.caption     = "OpenGL Simple Example";
//    settings.window.width       = w; 
//    settings.window.height      = h;
//
//    return App(settings).run();
//}
//
//
//App::App(const GApp::Settings& settings) : 
//    GApp(settings)
//	{
//    catchCommonExceptions = false;
//}
//
//
//void App::onInit() {
//    message("Loading...");
//	
//    showRenderingStats = false;
//    createDeveloperHUD();
//    developerWindow->setVisible(false);
//    developerWindow->cameraControlWindow->setVisible(false);
//    m_debugCamera->filmSettings().setAntialiasingEnabled(true);
//    m_debugCamera->filmSettings().setContrastToneCurve();
//
//    // Starting position
//    m_debugCamera->setFrame(CFrame::fromXYZYPRDegrees(24.3f, 0.4f, 2.5f, 68.7f, 1.2f, 0.0f));
//    m_debugCamera->frame();
//
//    makeGUI();
//
//	frameNum=0;
//
//    // Force re-render on first frame
//    m_prevCFrame = CFrame(Matrix3::zero());
//}
//
//
//void App::makeGUI() {
//    shared_ptr<GuiWindow> window = GuiWindow::create("Controls", debugWindow->theme(), Rect2D::xywh(0,0,0,0), GuiTheme::TOOL_WINDOW_STYLE);
//    GuiPane* pane = window->pane();
//    pane->addLabel("Use WASD keys + right mouse to move");
//    window->pack();
//
//    window->setVisible(true);
//    addWidget(window);
//}
//
//
//void App::onGraphics(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D, Array<shared_ptr<Surface2D> >& surface2D) {
//    // Update the preview image only while moving
//    if (! m_prevCFrame.fuzzyEq(m_debugCamera->frame())) {
//        
//        m_prevCFrame = m_debugCamera->frame();
//    }
//	renderScene();
//	rd->swapBuffers();
//}
//
//
//void App::onCleanup() {
//}
//
//void App::message(const std::string& msg) const {
//    renderDevice->clear();
//    renderDevice->push2D();
//        debugFont->draw2D(renderDevice, msg, renderDevice->viewport().center(), 12, 
//            Color3::white(), Color4::clear(), GFont::XALIGN_CENTER, GFont::YALIGN_CENTER);
//    renderDevice->pop2D();
//
//    // Force update so that we can see the message
//    renderDevice->swapBuffers();
//}
//
//
//void drawCube() {
//    // Code from http://www.morrowland.com/apron/tutorials/gl/gl_rotating_cube.php
//    glBegin(GL_QUADS);
//    glColor3f(0.0f,1.0f,0.0f);// Color Blue
//    glVertex3f( 1.0f, 1.0f,-1.0f);// Top Right Of The Quad (Top)
//    glVertex3f(-1.0f, 1.0f,-1.0f);// Top Left Of The Quad (Top)
//    glVertex3f(-1.0f, 1.0f, 1.0f);// Bottom Left Of The Quad (Top)
//    glVertex3f( 1.0f, 1.0f, 1.0f);// Bottom Right Of The Quad (Top)
//
//    glColor3f(1.0f,0.5f,0.0f);// Color Orange
//    glVertex3f( 1.0f,-1.0f, 1.0f);// Top Right Of The Quad (Bottom)
//    glVertex3f(-1.0f,-1.0f, 1.0f);// Top Left Of The Quad (Bottom)
//    glVertex3f(-1.0f,-1.0f,-1.0f);// Bottom Left Of The Quad (Bottom)
//    glVertex3f( 1.0f,-1.0f,-1.0f);// Bottom Right Of The Quad (Bottom)
//    
//    glColor3f(1.0f,0.0f,0.0f);// Color Red
//    glVertex3f( 1.0f, 1.0f, 1.0f);// Top Right Of The Quad (Front)
//    glVertex3f(-1.0f, 1.0f, 1.0f);// Top Left Of The Quad (Front)
//    glVertex3f(-1.0f,-1.0f, 1.0f);// Bottom Left Of The Quad (Front)
//    glVertex3f( 1.0f,-1.0f, 1.0f);// Bottom Right Of The Quad (Front)
//    
//    glColor3f(1.0f,1.0f,0.0f);// Color Yellow
//    glVertex3f( 1.0f,-1.0f,-1.0f);// Top Right Of The Quad (Back)
//    glVertex3f(-1.0f,-1.0f,-1.0f);// Top Left Of The Quad (Back)
//    glVertex3f(-1.0f, 1.0f,-1.0f);// Bottom Left Of The Quad (Back)
//    glVertex3f( 1.0f, 1.0f,-1.0f);// Bottom Right Of The Quad (Back)
//    
//    glColor3f(0.0f,0.0f,1.0f);// Color Blue
//    glVertex3f(-1.0f, 1.0f, 1.0f);// Top Right Of The Quad (Left)
//    glVertex3f(-1.0f, 1.0f,-1.0f);// Top Left Of The Quad (Left)
//    glVertex3f(-1.0f,-1.0f,-1.0f);// Bottom Left Of The Quad (Left)
//    glVertex3f(-1.0f,-1.0f, 1.0f);// Bottom Right Of The Quad (Left)
//    
//    glColor3f(1.0f,0.0f,1.0f);// Color Violet
//    glVertex3f( 1.0f, 1.0f,-1.0f);// Top Right Of The Quad (Right)
//    glVertex3f( 1.0f, 1.0f, 1.0f);// Top Left Of The Quad (Right)
//    glVertex3f( 1.0f,-1.0f, 1.0f);// Bottom Left Of The Quad (Right)
//    glVertex3f( 1.0f,-1.0f,-1.0f);// Bottom Right Of The Quad (Right)
//    glEnd();
//}
//
//void App::renderScene() {
//
//	// Set up the camera
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(50.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
//
//    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
//    glClearDepth(1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glDisable(GL_LIGHTING);
//
//	gluLookAt(myCamera.xPos, myCamera.yPos, myCamera.zPos, myCamera.xPos+myCamera.dirX, myCamera.yPos+myCamera.dirY, myCamera.zPos+myCamera.dirZ, 0, 1, 0);
//
//	//drawCube();
//	parseObj("../Data/terrain.obj");
//}
//
//void App::onUserInput(UserInput* ui) {
//
//	if (ui->keyDown(GKey::LEFT)) {//turn left
//		myCamera.angleY -= 0.01f;
//		myCamera.dirX = sin(myCamera.angleY);
//		myCamera.dirZ = -cos(myCamera.angleY);
//	}
//
//	if (ui->keyDown(GKey::RIGHT)) {//turn right
//		myCamera.angleY += 0.01f;
//		myCamera.dirX = sin(myCamera.angleY);
//		myCamera.dirZ = -cos(myCamera.angleY);
//	}
//
//	float fraction = 0.2f;
//
//	if (ui->keyDown(GKey::KP8)) {//forward
//		myCamera.xPos += myCamera.dirX * fraction;
//		myCamera.zPos += myCamera.dirZ * fraction;
//		myCamera.yPos += myCamera.dirY * fraction;
//	}
//
//	if (ui->keyDown(GKey::KP5)) {//backwards
//		myCamera.xPos -= myCamera.dirX * fraction;
//		myCamera.zPos -= myCamera.dirZ * fraction;
//		myCamera.yPos -= myCamera.dirY * fraction;
//	}
//
//	if (ui->keyDown(GKey::KP4)) {//LEFT
//		float Bx=0,By=1,Bz=0;//cross product
//		float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
//		float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
//		float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
//		myCamera.xPos -= xP * fraction;
//		myCamera.zPos -= zP * fraction;
//		myCamera.yPos -= yP * fraction;
//	}
//
//	if (ui->keyDown(GKey::KP6)) {//RIGHT
//		float Bx=0,By=1,Bz=0;//cross product
//		float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
//		float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
//		float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
//		myCamera.xPos += xP * fraction;
//		myCamera.zPos += zP * fraction;
//		myCamera.yPos += yP * fraction;
//	}
//
//}
#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include <string.h>

std::string								 modelName;

class App : public GApp {
private:
    shared_ptr<ArticulatedModel>         model;

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

    App(const GApp::Settings& settings) : GApp(settings), diffuseScalar(0.6f), specularScalar(0.5f), reflect(0.1f), shine(20.0f), bumpiness(0.0f), displacement(0.0f), modulation(0.0f) {}

    virtual void onInit();
    virtual void onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D);
};


void App::onInit() {
    createDeveloperHUD();
    window()->setCaption("Pixel Shader Demo");
        
    ArticulatedModel::Specification spec;

	std::string dataFile = modelName;
	
	// Load each model depending on the input 
	//if(modelName.empty())
	//{
	//	dataFile = "teapot/teapot.obj";
	//	spec.scale = 0.015f;
	//	spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("setCFrame(root(), Point3(0, -0.5, 0));")));
	//}
	//// Special case to handle viper since the model isn't named like the folder
	//else if(!modelName.compare("viper"))
	//{
	//	dataFile = "viper/Viper-mk-IV-fighter.obj";
	//	spec.scale = 0.06f;
	//	spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("setCFrame(root(), CFrame::fromXYZYPRDegrees(0,0,0,-90));")));
	//}
	//else
	//{
	//	dataFile += "/";
	//	dataFile+= modelName;
	//	dataFile += ".obj";
	//}
	dataFile = "../../Data/terrain.obj";
	spec.filename = System::findDataFile(dataFile);
    spec.stripMaterials = true;

	/*spec.filename = System::findDataFile("dragon/dragon.obj");
    spec.stripMaterials = true;*/

    /*spec.filename = System::findDataFile("teapot/teapot.obj");
    spec.scale = 0.015f;
    spec.stripMaterials = true;
    spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("setCFrame(root(), Point3(0, -0.5, 0));")));*/

    /*spec.filename = System::findDataFile("viper/Viper-mk-IV-fighter.obj");
    spec.scale = 0.06f;
    spec.stripMaterials = true;
    spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("setCFrame(root(), CFrame::fromXYZYPRDegrees(0,0,0,-90));")));*/

    model = ArticulatedModel::create(spec);

    makeLighting();
    makeColorList();
    makeGui();
	loadTextures();

    // Color 1 is red
    diffuseColorIndex = 8;
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
            model->pose(mySurfaces, manipulator->frame());
            
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
	//bumpMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT, 
	//	Texture::Settings::defaults(), Texture::Preprocess::normalMap());

	//displacementMap = Texture::fromFile("../heightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);

	//modulationMap = Texture::fromFile("../lightMap.png", ImageFormat::RGBA8(), Texture::DIM_2D_NPOT);

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

	if(argc > 1)
		modelName = argv[1];

    return App(settings).run();
}
