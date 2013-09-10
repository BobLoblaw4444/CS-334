/**
 Department of Computer Science
 Purdue University
 Jan 13, 2012
 CS334 Assignment #0 Warm-up Assignment
 **/
#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>
#include "MyPoint.h"
#include "MyVector.h"
#include "MyMatrix.h"

////////////
// Define necessary globals here
float xPos1;
float xPos2;
float yPos1;
float yPos2;
float xVel1;
float yVel1;
float xVel2;
float yVel2;
////////////

G3D_START_AT_MAIN();

void print(float value)
{
	std::wstringstream s;
	s << L"" <<value <<" ";
	std::wstring ws = s.str();
	OutputDebugString(ws.c_str());
}

void drawFrame(int w, int h) {

	// Set up the camera and window space; here spans (-10, -10) to (+10, +10)
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	
    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_LIGHTING);
	
    // Move the line in camera space
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	///////////////
	// *** add code below ***

	// update position of two 2D points
	xPos1 += xVel1;
	yPos1 += yVel1;
	xPos2 += xVel2;
	yPos2 += yVel2;

	// bounce points off the edge of the window 
	if((xPos1 > 10 && xVel1 > 0) || (xPos1 < -10 && xVel1 < 0))
	{
		xVel1 = -xVel1;
	}

	if( (xPos2 > 10 && xVel2 > 0) || (xPos2 < -10 && xVel2 < 0))
	{
		xVel2 = -xVel2;
	}

	if((yPos1 > 10 && yVel1 > 0) || (yPos1 < -10 && yVel1 < 0))
	{
		yVel1 = -yVel1;
	}
	
	if((yPos2 > 10 && yVel2 > 0) || (yPos2 < -10 && yVel2 < 0))
	{
		yVel2 = -yVel2;
	}

	// draw a line using GL_LINES
	glBegin(GL_LINES);
	glVertex3f(xPos1, yPos1, 0);
	glVertex3f(xPos2, yPos2, 0);
	glEnd();
	// *** add code above ***
	///////////////	
}

int main(int argc, char** argv) {
    RenderDevice* rd = new RenderDevice();
    OSWindow::Settings settings;

    settings.width = 960;
    settings.height = 600;

    rd->init(settings);

	////////////
	// compute random initial position and velocity of two 2D points within the application window
	// ** add code here ***
	///////////
	srand(time(0));
	xPos1 = rand() % 10;
	xPos2 = rand() % 10;
	yPos1 = rand() % 10;
	yPos2 = rand() % 10;
	xVel1 = ((rand() % 5) + 1)/2;
	yVel1 = ((rand() % 5) + 1)/2;
	xVel2 = ((rand() % 5) + 1)/2;
	yVel2 = ((rand() % 5) + 1)/2;

	MyPoint<float> point(3.0f,4.0f,5.0f);
	MyPoint<float> point2(3.0f,4.0f,5.0f);
	MyPoint<float> point3 = point-point2;

	MyVector<float> vector(3.0f,4.0f,2.0f);
	MyVector<float> vector2(3.0f,7.0f,0.0f);
	float dotProduct = vector.DotProduct(vector2);
	MyVector<float> crossProduct = vector.CrossProduct(vector2);
	//vector.Normalize();
	MyVector<float> vector3 = vector - vector2;

	MyMatrix<float> matrix(1,2,3,0,5,6,7,0,9,10,11,0,13,14,15,1);
	
	MyVector<float> matrixResult = matrix * vector;
	for(int i = 0; i< 4; i++)
	{
		print(matrixResult.components[i]);
	}

	for (int i=0; i<300; i++) {

		// draw frame
        drawFrame(settings.width, settings.height);

        // Render at 30 fps
        System::sleep(1.0/30.0);

        // See also RenderDevice::beginFrame, RenderDevice::endFrame
        rd->swapBuffers();
    }

    rd->cleanup();
    delete rd;

    return 0;
}