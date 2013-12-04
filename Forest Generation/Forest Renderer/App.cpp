/**
  @file App.cpp
 */
//#include "App.h"
//
//#define w 900
//#define h 600
//
//float frameNum;
//
//MyCamera myCamera;
//
//void drawCube();
////G3D_START_AT_MAIN();
//
//int main(int argc, char** argv) {
//    GApp::Settings settings;
//    settings.window.caption     = "OpenGL Simple Example";
//    settings.window.width       = w; 
//    settings.window.height      = h;
//
//    /*return App(settings).run();*/
//		// Set up the camera
//
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
//	drawCube();
//}
//
//
////App::App(const GApp::Settings& settings) : 
////    GApp(settings)
////	{
////    catchCommonExceptions = false;
////}
////
////
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
////
////
//void App::makeGUI() {
//    shared_ptr<GuiWindow> window = GuiWindow::create("Controls", debugWindow->theme(), Rect2D::xywh(0,0,0,0), GuiTheme::TOOL_WINDOW_STYLE);
//    GuiPane* pane = window->pane();
//    pane->addLabel("Use WASD keys + right mouse to move");
//    window->pack();
//
//    window->setVisible(true);
//    addWidget(window);
//}
////
////
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
//	drawCube();
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

#include <GL/glut.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   glutWireCube (1.0);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}