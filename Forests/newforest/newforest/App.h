#ifndef App_h
#define App_h

#include <G3D/G3DAll.h>

class PhysicsScene;

class App : public GApp {
protected:

    bool                        m_firstPersonMode;

    std::string                 m_playerName;

    shared_ptr<Scene>    m_scene;    
    
    /** Called from onInit */
    void makeGUI();

    /** Called from onInit */
    void makeGBuffer();

public:
    
    App(const GApp::Settings& settings = GApp::Settings());
	//shared_ptr<ArticulatedModel>		 model[2501];
    virtual void onInit() override;
    virtual void onAI() override;
    virtual void onNetwork() override;
    virtual void onSimulation(RealTime rdt, SimTime sdt, SimTime idt) override;
    virtual void onPose(Array<shared_ptr<Surface> >& posed3D, Array<shared_ptr<Surface2D> >& posed2D) override;
    virtual void onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& posed3D) override;
	shared_ptr<ThirdPersonManipulator>   manipulator;
};

#endif
