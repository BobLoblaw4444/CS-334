#ifndef App_h
#define App_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>

class MyCamera{
public:
	float angleX,angleY,dirX,dirY,dirZ,xPos,yPos,zPos;

	MyCamera(){
		angleX = 0.0;
		angleY = 0.0;
		dirX = 0.0;
		dirZ = -1.0;
		dirY = 0.0;
		xPos = 0.0;
		yPos = 0.0;
		zPos = 10.0;
	}
};

class App : public GApp {
private:
    
   
    /** Position during the previous frame */
    CFrame              m_prevCFrame;

    /** Called from onInit() */
    void makeGUI();

   
    /** Show a full-screen message */
    void message(const std::string& msg) const;


public:

    App(const GApp::Settings& settings = GApp::Settings());

    virtual void onInit();

    void renderScene();

	void onUserInput(UserInput* ui);

    virtual void onGraphics(RenderDevice* rd, Array<shared_ptr<Surface> >& posed3D, Array<shared_ptr<Surface2D> >& posed2D);
    virtual void onCleanup();
};

#endif