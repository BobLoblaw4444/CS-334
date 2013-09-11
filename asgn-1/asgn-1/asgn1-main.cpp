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

MyPoint<float> point1(0,0,0);
MyPoint<float> point2(0,0,0);
MyVector<float> velocity1(0,0,0);
MyVector<float> velocity2(0,0,0);
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
	point1.components[0] += velocity1.components[0];
	point1.components[1] += velocity1.components[1];
	point1.components[2] += velocity1.components[2];

	point2.components[0] += velocity2.components[0];
	point2.components[1] += velocity2.components[1];
	point2.components[2] += velocity2.components[2];

	// bounce points off the edge of the window 
	if((point1.components[0] > 10 && velocity1.components[0] > 0) || (point1.components[0] < -10 && velocity1.components[0] < 0))
	{
		velocity1.components[0] = -velocity1.components[0];
	}

	if((point1.components[1] > 10 && velocity1.components[1] > 0) || (point1.components[1] < -10 && velocity1.components[1] < 0))
	{
		velocity1.components[1] = -velocity1.components[1];
	}
	
	if((point1.components[2] > 10 && velocity1.components[2] > 0) || (point1.components[2] < -10 && velocity1.components[2] < 0))
	{
		velocity1.components[2] = -velocity1.components[2];
	}

	if( (point2.components[0] > 10 && velocity2.components[0] > 0) || (point2.components[0] < -10 && velocity2.components[0] < 0))
	{
		velocity2.components[0] = -velocity2.components[0];
	}

	if((point2.components[1] > 10 && velocity2.components[1] > 0) || (point2.components[1] < -10 && velocity2.components[1] < 0))
	{
		velocity2.components[1] = -velocity2.components[1];
	}

	if((point2.components[2] > 10 && velocity2.components[2] > 0) || (point2.components[2] < -10 && velocity2.components[2] < 0))
	{
		velocity2.components[2] = -velocity2.components[2];
	}

	// draw a line using GL_LINES
	glBegin(GL_LINES);
	glVertex3fv(point1.components);
	glVertex3fv(point2.components);
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
	point1.components[0] = rand() % 10;
	point1.components[1] = rand() % 10;
	point1.components[2] = rand() % 10;
	
	point2.components[0] = rand() % 10;
	point2.components[1] = rand() % 10;
	point2.components[2] = rand() % 10;
	
	velocity1.components[0] = ((rand() % 5) + 1)/2.0f;
	velocity1.components[1] = ((rand() % 5) + 1)/2.0f;
	velocity1.components[2] = ((rand() % 5) + 1)/2.0f;
	
	velocity2.components[0] = ((rand() % 5) + 1)/2.0f;
	velocity2.components[1] = ((rand() % 5) + 1)/2.0f;
	velocity2.components[2] = ((rand() % 5) + 1)/2.0f;

	//MyPoint<float> point(3.0f,4.0f,2.0f);
	//point[0] = 3;
	//MyPoint<float> point2(3.0f,4.0f,5.0f);
	//MyPoint<float> point3 = point-point2;

	//MyVector<float> vector(3.0f,4.0f,2.0f);
	//MyVector<float> vector2(3.0f,7.0f,0.0f);

	//MyMatrix<float> matrix(1,2,3,0,5,6,7,0,9,10,11,0,13,14,15,1);
	//MyMatrix<float> matrix2(1,2,3,0,5,6,7,0,9,10,11,0,13,14,15,1);
	//
	//MyMatrix<float> matrixResult = matrix * matrix2;
	//MyVector<float> vectorMatrix = matrix * vector;

	//MyMatrix<float> matrixRotX = matrix2.Rotate('x', 90);
	//MyMatrix<float> matrixTrans= matrix.Translate(5,0,0);

	//for(int i = 0; i < 16; i++)
	//{
	//	print(matrixTrans.components[i]);
	//}

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