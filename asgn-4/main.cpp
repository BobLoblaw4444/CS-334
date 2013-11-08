/**

  Example of using G3D shaders and GUIs.
  
  Template by Daniel Aliaga (aliaga@cs.purdue.edu), based on PixelShader demo program.
  by Morgan McGuire, http://graphics.cs.williams.edu
 */
#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <stack>
#include <time.h>

using std::cout;
using std::string;
using std::list;

int numVertices = 6;
float radius = 1.0f/120;
float height = 1.0f/120;

bool rotateZ = false;

class ruleObject
{
	public:
		char letter;
		float weight;
		string rule;

		ruleObject(char inLetter, float inWeight, string inRule)
		{
			letter = inLetter;
			weight = inWeight;
			rule = inRule;
		}
};

class state
{
	public:
		float x;
		float y;
		float z;
		float angle;

		state(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
};

float inRadians(float deg)
{
	return deg * (3.14f/180.0f);
}

bool count = false;
int fCount = 0;

float turnAngle;
int numOfIterations;
string initialString;
list<ruleObject*> ruleList;
list<state*> vertexList;
std::stringstream vertexString;
std::stringstream faceString;
std::stringstream objString;
int vertexNum = 1;


void parseInput();
string expandRules(string startString);
string determineStochasticRule(char letter);
bool compareWeights(ruleObject* first, ruleObject* second);

state* buildCylinder(state* currentState);
void rotateVertices(float angle);

string								 modelName;

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
    window()->setCaption("Trees!");
        
    ArticulatedModel::Specification spec;

	std::string dataFile = modelName;
	
	spec.filename = System::findDataFile(dataFile);
    spec.stripMaterials = true;

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
	
	srand(time(0));

	parseInput();

	// Expand the initial string using the rules for the given number of iterations
	string expandedRules = initialString;
	for(int i = 0; i < numOfIterations; i++)
	{
		if(i == numOfIterations-1)
			count = true;
		expandedRules = expandRules(expandedRules);
	}

	// Output final string to console
	cout <<expandedRules;
	cout << fCount;

	// Create tree.txt containing the string
	std::ofstream outfile;
	outfile.open ("../data-files/tree.txt");
	outfile << expandedRules;
	outfile.close();

	
	std::stack<state> stateList;

	state* currentState = new state(0.0f, 0.0f, 0.0f);
	currentState->angle = inRadians(90.0f);

	for(int i = 0; i < expandedRules.size(); i++)
	{
		if(expandedRules[i] == initialString[0])
		{
			if((rand() % 2) == 0)
			{
				rotateZ = true;
			}

			state* newPos = buildCylinder(currentState);
			rotateVertices(currentState->angle);

			currentState->x = newPos->x;
			currentState->y = newPos->y;
			currentState->z = newPos->z;

			/*if(rotateZ)
			{
				currentState->z += radius * cos(currentState->angle);
			}
			else
			{
				currentState->x += radius * cos(currentState->angle);
			}
			currentState->y += height + height * sin(currentState->angle);*/
			
		}
		else if(expandedRules[i] == '+')
		{
			currentState->angle += inRadians(turnAngle);
		}
		else if(expandedRules[i] == '-')
		{
			currentState->angle -= inRadians(turnAngle);
		}
		else if(expandedRules[i] == '[')
		{
			stateList.push(*currentState);
		}
		else if(expandedRules[i] == ']')
		{
			*currentState = stateList.top();
			stateList.pop();
		}
	}
	
	delete(currentState);

	std::ofstream objfile;
	objfile.open ("../data-files/tree.obj");
	objfile << vertexString.rdbuf();
	objfile << faceString.rdbuf();
	objfile.close();

	modelName = "../data-files/tree.obj";

    return App(settings).run();
}

state* buildCylinder(state* currentState)
{
	float x = currentState->x;
	float y = currentState->y;
	float z = currentState->z;
	float angle = 6.28f/numVertices;

	int angleNum = 1;

	// build bottom circle point
	int centralVertex1 = vertexNum;
	int centralVertex2 = vertexNum + 3;

	float centralY2;
	float centralX2;
	float centralZ2;

	vertexList.push_back(new state(x,y,z));

	for(int i = 0; i < numVertices; i++)
	{
		// bottom circle slice 1st vertex
		z = currentState->z + (radius * cos(angle * angleNum));
		x = currentState->x + (radius * sin(angle * angleNum));

		if(rotateZ)
		{
			y = currentState->y + (radius * cos(currentState->angle))*(currentState->z - z );
		}
		else
		{
			y = currentState->y + (radius * sin(currentState->angle))*(currentState->x - x );
		}

		vertexList.push_back(new state(x,y,z));
	
		// bottom circle slice 2nd vertex
		angleNum++;
		z = currentState->z + (radius * cos(angle * angleNum));
		x = currentState->x + (radius * sin(angle * angleNum));
		
		if(rotateZ)
		{
			y = currentState->y + (radius * cos(currentState->angle))*(currentState->z - z );
		}
		else
		{
			y = currentState->y + (radius * sin(currentState->angle))*(currentState->x - x );
		}
	
		vertexList.push_back(new state(x,y,z));
	
		faceString << "f " << centralVertex1 << " " << vertexNum + 1 << " " << vertexNum + 2 <<"\n";
		faceString << "f " << vertexNum + 2 << " " << vertexNum + 1 << " " << centralVertex1 <<"\n";

		// central point of top circle
		angleNum--;
		centralY2 = currentState->y + height + (height * sin(currentState->angle));
		centralX2 = currentState->x + (radius * cos(currentState->angle));
		centralZ2 = currentState->z + (radius * cos(currentState->angle));
		z = currentState->z;

		vertexList.push_back(new state(centralX2,centralY2,z));

		faceString << "f " << vertexNum + 1 << " " << vertexNum + 2 << " " << vertexNum + 4 <<"\n";
		faceString << "f " << vertexNum + 4 << " " << vertexNum + 2 << " " << vertexNum + 1 <<"\n";

		// top circle slice 1st vertex
		z = centralZ2 + (radius * cos(angle * angleNum));
		x = centralX2 + (radius * sin(angle * angleNum));
		
		if(rotateZ)
		{
			y = centralY2 + (radius * cos(currentState->angle))*(centralZ2 - z );
		}
		else
		{
			y = centralY2 + (radius * sin(currentState->angle))*(centralX2 - x);
		}
		
		vertexList.push_back(new state(x,y,z));

		faceString << "f " << vertexNum + 2 << " " << vertexNum + 5 << " " << vertexNum + 4 <<"\n";
		faceString << "f " << vertexNum + 4 << " " << vertexNum + 5 << " " << vertexNum + 2 <<"\n";
	
		// top circle slice 2nd vertex
		angleNum++;
		z = centralZ2 + (radius * cos(angle * angleNum));
		x = centralX2 + (radius * sin(angle * angleNum));
		
		if(rotateZ)
		{
			y = centralY2 + (radius * cos(currentState->angle))*(centralZ2 - z );
		}
		else
		{
			y = centralY2 + (radius * sin(currentState->angle))*(centralX2 - x);
		}
		
		vertexList.push_back(new state(x,y,z));

		faceString << "f " << centralVertex2 << " " << vertexNum + 5 << " " << vertexNum + 4 <<"\n";
		faceString << "f " << vertexNum + 4 << " " << vertexNum + 5 << " " << centralVertex2 <<"\n";
		
		x = currentState->x;
		y = currentState->y;
		z = currentState->z;
		vertexNum+=5;
	}
	vertexNum++;

	return (new state(centralX2, centralY2, centralZ2));
}

void rotateVertices(float angle)
{
	float px = vertexList.front()->x;
	float py = vertexList.front()->y;

	for(list<state*>::iterator it = vertexList.begin(); it != vertexList.end(); it++)
	{
	
		vertexString << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z <<"\n";
	}
	vertexList.clear();
}

void parseInput()
{
	std::ifstream infile;
	infile.open("../data-files/rules.txt");
	
	string line;
	int lineCount = 0;
	int i = 0;
	for (string line; std::getline(infile, line);)
	{
		if(lineCount == 1)
		{
			turnAngle = stof(line);
		}
		else if(lineCount == 2)
		{
			numOfIterations = stoi(line);
		}
		else if(lineCount == 3)
		{
			initialString = line[0];
		}
		else if(lineCount > 3)
		{
			if(strstr(line.c_str(), "end"))
			{
				lineCount++;
				continue;
			}
			// Default the weight to 1 and save the letter corresponding to the rule
			float weight = 1.0f;
			char letter = line[0];

			// Check if this rule has a weight, if so process it
			unsigned pos = 0;
			pos = line.find("(");
			if(pos < line.length())
			{
				// Find position of parenteheses so the weight can be collected from in between them
				int first = pos;
				int last = line.find(")");
				
				// There isn't a closed parenthese, abandon everything
				if(last > line.length())
				{
					cout << "Invalid input!";
					exit(1);
				}
				// Save the weight of this rule
				weight = stof(line.substr(first+1, last - first - 1));
			}
			// Locate the arrow and save the rest of the string as the rule
			pos = line.find(" -> ");
			string rule = line.substr(pos+4);
			ruleList.push_front(new ruleObject(letter, weight, rule));
			i++;
		}
		lineCount++;
	}
}

string expandRules(string startString)
{
	string resultString;
	bool foundInRules = false;

	for each(char letter in startString)
	{
		for(list<ruleObject*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
		{
			if(letter == (*it)->letter)
			{
				resultString += determineStochasticRule(letter);
				foundInRules = true;
				if(count)
					fCount+=5;
				break;
			}
		}
		if(!foundInRules)
		{
			resultString += letter;
		}
		else
		{
			foundInRules = false;
		}
	}
	return resultString;
}

bool compareWeights(ruleObject* first, ruleObject* second)
{
	if(first->weight > second->weight)
	{
		return true;
	}
	else
		return false;
}

string determineStochasticRule(char letter)
{
	list<ruleObject*> rules;
	ruleObject* weightedArray[10];
	int count = 0;

	for(list<ruleObject*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
	{
		if(letter == (*it)->letter)
		{
			if((*it)->weight != 1.0f)
			{
				for(int i = 0; i < std::floor((*it)->weight *10); i++)
				{
					weightedArray[count] = (*it);
					count++;
				}
			}
			else
			{
				return (*it)->rule;
			}
		}
	}
	return weightedArray[rand() % 10]->rule;
}