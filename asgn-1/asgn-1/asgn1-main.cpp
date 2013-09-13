/**
 Department of Computer Science
 Purdue University
 Jan 13, 2012
 CS334 Assignment #1 Warmed-up Assignment
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

// HEY, CHANGE THESE VARIABLES TO TEST SPEED AND PERSPECTIVE
float speed = 1;
bool isPerspective = true;
float fps = 30.0f;
//////////////////

// Define necessary globals here
MyPoint<float> point1, point2;
MyPoint<float> perspectivePoint1, perspectivePoint2;
MyVector<float> velocity1, velocity2;

MyMatrix<float> rotation1, rotation2;
float rotAngle1, rotAngle2;
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

	MyMatrix<float> rotation, translation;

	// Set up the camera and window space; here spans (-10, -10) to (+10, +10)
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

	// Pull camera back when using perspective projection
	if(isPerspective)
	{
		glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -15.0f, 15.0f);
		glTranslated(0, 0, 10.0f);
	}

    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_LIGHTING);
	
    // Move the line in camera space
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///////////////////////////////////

	// update velocities with rotation
	velocity1 = rotation1 * velocity1;
	velocity2 = rotation2 * velocity2;

	// bounce points off the edge of the window 
	if((point1.components[0] > 10 && velocity1.components[0] > 0) || (point1.components[0] < -10 && velocity1.components[0] < 0))
	{
		velocity1 = Reflect<float>(-1, 1, 1) * velocity1;
	}

	if((point1.components[1] > 10 && velocity1.components[1] > 0) || (point1.components[1] < -10 && velocity1.components[1] < 0))
	{
		velocity1 = Reflect<float>(1, -1, 1) * velocity1;
	}
	
	if((point1.components[2] > 10 && velocity1.components[2] > 0) || (point1.components[2] < -10 && velocity1.components[2] < 0))
	{
		velocity1 = Reflect<float>(1, 1, -1) * velocity1;
	}

	if( (point2.components[0] > 10 && velocity2.components[0] > 0) || (point2.components[0] < -10 && velocity2.components[0] < 0))
	{
		velocity2 = Reflect<float>(-1, 1, 1) * velocity2;
	}

	if((point2.components[1] > 10 && velocity2.components[1] > 0) || (point2.components[1] < -10 && velocity2.components[1] < 0))
	{
		velocity2 = Reflect<float>(1, -1, 1) * velocity2;
	}

	if((point2.components[2] > 10 && velocity2.components[2] > 0) || (point2.components[2] < -10 && velocity2.components[2] < 0))
	{
		velocity2 = Reflect<float>(1, 1, -1) * velocity2;
	}

	// update position of two 3D points
	point1 = Translate(velocity1[0], velocity1[1], velocity1[2]) * point1;
	point2 = Translate(velocity2[0], velocity2[1], velocity2[2]) * point2;

	// draw a line using GL_LINES
	glBegin(GL_LINES);

	if(isPerspective)
	{
		perspectivePoint1 = Perspective<float>(5.0f) * point1;
		perspectivePoint2 = Perspective<float>(5.0f) * point2;
		glVertex3fv(perspectivePoint1.components);
		glVertex3fv(perspectivePoint2.components);
	}
	else
	{
		glVertex3fv(point1.components);
		glVertex3fv(point2.components);
	}
	
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
	// compute random initial position and velocity of two 3D points within the application window
	// ** add code here ***
	///////////
	srand(time(0));
	point1.components[0] = rand() % 10;
	point1.components[1] = rand() % 10;
	point1.components[2] = rand() % 10;
	
	point2.components[0] = rand() % 10;
	point2.components[1] = rand() % 10;
	point2.components[2] = rand() % 10;
	
	// Initialize velocity1 and multiply by fps and speed
	velocity1.components[0] = ((rand() % 5) + 1);
	velocity1.components[1] = ((rand() % 5) + 1);
	velocity1.components[2] = ((rand() % 5) + 1);
	
	velocity1.Normalize();
	velocity1/fps;
	velocity1 * (speed * 20.0f);

	// Initialize velocity2 and multiply by fps and speed
	velocity2.components[0] = ((rand() % 5) + 1);
	velocity2.components[1] = ((rand() % 5) + 1);
	velocity2.components[2] = ((rand() % 5) + 1);

	velocity2.Normalize();
	velocity2/fps;
	velocity2 * (speed * 20.0f);

	// Initialize rotation matrices
	rotation1 = RotateEverything<float>((float)rand()/((float)RAND_MAX/.25f));
	rotation2 = RotateEverything<float>((float)rand()/((float)RAND_MAX/.25f));

	// Main program loop
	for (int i=0; i<(fps * 10); i++) {

		// draw frame
        drawFrame(settings.width, settings.height);

        // Render at 30 fps
        System::sleep(1.0/fps);

        // See also RenderDevice::beginFrame, RenderDevice::endFrame
        rd->swapBuffers();
    }

    rd->cleanup();
    delete rd;

    return 0;
}