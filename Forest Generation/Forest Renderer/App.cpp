#include "App.h"
#include <stdlib.h>
#include <GL/glut.h>

#include <fstream>
#include <string>

using std::string;

MyCamera myCamera;

float vertexArray[16000];
//int faceArray[10000];
int vertexIndex = 1;
int vertexNum = 0;

//void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void parseObj(string modelPath)
{
	int count = 0;
	std::ifstream model(modelPath);
	string line;
	while (std::getline(model, line))
	{
		if(++count == 6874)
			break;

		if(line[0] == 'v')
		{
			string val;
			val.clear();

			int j = 2;
			for(int j = 2; j < line.size(); j++)
			{
				if(line[j] == ' ')
				{
					vertexArray[vertexIndex] = stof(val);
					vertexIndex++;
					val.clear();
				}
				else
				{
					val += line[j];
				}
			}
			
			vertexArray[vertexIndex] = stof(val);
			vertexIndex++;
			vertexNum++;

			if(vertexNum % 3 == 0)
			{
				glBegin(GL_TRIANGLES);
				glColor3f (0.0, 1.0, 0.0);
				glVertex3f(vertexArray[vertexIndex-9], vertexArray[vertexIndex-8], vertexArray[vertexIndex-7]);
				glVertex3f(vertexArray[vertexIndex-6], vertexArray[vertexIndex-5], vertexArray[vertexIndex-4]);
				glVertex3f(vertexArray[vertexIndex-3], vertexArray[vertexIndex-2], vertexArray[vertexIndex-1]);
				glEnd();
			}
		}

	}
	//model.close();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   
   //glBegin(GL_TRIANGLES);
   
   parseObj("../Data/terrain.obj");
   
   //glEnd();
   //
   glFlush ();
}

//void reshape (int w, int h)
//{
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity ();
//   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//   glMatrixMode (GL_MODELVIEW);
//}


void keyboard(unsigned char key, int x, int y)
{
	
	float fraction = 0.2f;
	switch (key)
	{
		case 'a': //turn left
			myCamera.angleY -= 0.01f;
			myCamera.dirX = sin(myCamera.angleY);
			myCamera.dirZ = -cos(myCamera.angleY);
			break;

		case 'd'://turn right
			myCamera.angleY += 0.01f;
			myCamera.dirX = sin(myCamera.angleY);
			myCamera.dirZ = -cos(myCamera.angleY);
			break;


		case 'w'://forward
			myCamera.xPos += myCamera.dirX * fraction;
			myCamera.zPos += myCamera.dirZ * fraction;
			myCamera.yPos += myCamera.dirY * fraction;
			break;

		case 's'://backwards
			myCamera.xPos -= myCamera.dirX * fraction;
			myCamera.zPos -= myCamera.dirZ * fraction;
			myCamera.yPos -= myCamera.dirY * fraction;
			break;

	//if (ui->keyDown(GKey::KP4)) {//LEFT
	//	float Bx=0,By=1,Bz=0;//cross product
	//	float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
	//	float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
	//	float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
	//	myCamera.xPos -= xP * fraction;
	//	myCamera.zPos -= zP * fraction;
	//	myCamera.yPos -= yP * fraction;
	//}

	//if (ui->keyDown(GKey::KP6)) {//RIGHT
	//	float Bx=0,By=1,Bz=0;//cross product
	//	float xP = myCamera.dirY*Bz - By*myCamera.dirZ; 
	//	float yP = Bx*myCamera.dirZ - myCamera.dirX*Bz; 
	//	float zP = myCamera.dirX*By - myCamera.dirY*Bx; 
	//	myCamera.xPos += xP * fraction;
	//	myCamera.zPos += zP * fraction;
	//	myCamera.yPos += yP * fraction;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutKeyboardFunc(keyboard);

   init();
   
   glutDisplayFunc(display); 
   //glutReshapeFunc(reshape);
   gluLookAt(myCamera.xPos, myCamera.yPos, myCamera.zPos, myCamera.xPos+myCamera.dirX, myCamera.yPos+myCamera.dirY, myCamera.zPos+myCamera.dirZ, 0, 1, 0);
   glutMainLoop();
   return 0;
}