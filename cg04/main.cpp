//
//		          Programming Assignment #3 CPSC4050/6050
//
//
//
/***************************************************************************/

/* Include needed files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <time.h>
#include <thread>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>   

#include <math.h>
#include <iostream>

#include "objects.cpp"


int WIDTH = 800;
int HEIGHT = 600;

int windowHandle;
int projection = 0;
int obj = 0;

float fov = 50;
float worldZ = -80.f;

float scaleX = 1;
float scaleY = 1;
float scaleZ = 1;

float thetaX = 0;
float thetaY = 0;
float thetaZ = 0;

float transZ = 0;
float transY = 0;
float transX = 0;

float camX = 0;
float camY = 0;
float camZ = 10;

float upArmThetaZ = 0;
float upArmThetaY = 0;
float loArmThetaZ = 0;
float loArmThetaY = 0;

float legsThetaX = 0;
bool legUp = false;

bool walking = false;
int FPS = 60;
int frames = 0;
float walkZ = 0;
std::chrono::high_resolution_clock::time_point timer;
std::chrono::high_resolution_clock::time_point startTime;
std::chrono::high_resolution_clock::time_point endTime;
double second, elapsed, dt;

void drawRobot()
{
	//head
	glPushMatrix();
	glTranslatef(0, 9, 1.4);
	glScalef(3, 3, 3);
	drawSphere(1, 20, 20);
	glPopMatrix();

	//body
	glPushMatrix();
	glTranslatef(0, 0, 1.4);
	glScalef(4, 6, 3);
	drawCube(1);
	glPopMatrix();

	//shoulders
	glPushMatrix();
	glTranslatef(4.9, 3.5, 2);
	glScalef(2, 1.4, 2);
	drawCylinder(1, 1); //right
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.9, 3.5, 2);
	glScalef(2, 1.4, 2);
	drawCylinder(1, 1); //left
	glPopMatrix();

	//legs
	glPushMatrix();
	glTranslatef(2, -5, 2); //stay connected to hip
	glRotatef(legsThetaX, 1, 0, 0);
	glTranslatef(0, -7, -1); //rotate at hip
	glScalef(1.3, 7, 2);
	drawCylinder(1, 1); //right
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -5, 2); //stay connected to hip
	glRotatef(-legsThetaX, 1, 0, 0); 
	glTranslatef(0, -7, -1); //rotate at hip
	glScalef(1.3, 7, 2);
	drawCylinder(1, 1); //left
	glPopMatrix();

	//right arm
	glPushMatrix();
	glTranslatef(6.5, 3.2, 2.1); //stay connected to shoulder
	glRotatef(upArmThetaY, 0, 1, 0);
	glRotatef(upArmThetaZ, 0, 0, 1);
	glTranslatef(2, 0, 0); //rotate around end of arm not origin
	glPushMatrix();
	glScalef(2, 1.1, 2);
	drawCylinder(1, 1); //up
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0, 0); //stay connected to upper arm
	glRotatef(loArmThetaY, 0, 1, 0);
	glRotatef(loArmThetaZ, 0, 0, 1);
	glTranslatef(1.5, 0, 0); //rotate around end of arm not origin
	glPushMatrix();
	glScalef(1.5, 0.9, 2);
	drawCylinder(1, 1); //low
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//left arm
	glPushMatrix();
	glTranslatef(-6.5, 3.2, 2.1); //stay connected to shoulder
	//glRotatef(upArmThetaY, 0, 1, 0);
	//glRotatef(upArmThetaZ, 0, 0, 1);
	glTranslatef(-2, 0, 0); //rotate around end of arm not origin
	glPushMatrix();
	glScalef(2, 1.1, 2);
	drawCylinder(1, 1); //up
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 0, 0); //stay connected to upper arm
	//glRotatef(loArmThetaY, 0, 1, 0);
	//glRotatef(loArmThetaZ, 0, 0, 1);
	glTranslatef(-1.5, 0, 0); //rotate around end of arm not origin
	glPushMatrix();
	glScalef(1.5, 0.9, 2);
	drawCylinder(1, 1); //low
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



}

/***************************************************************************/
void initWindow()
/* Clear the image area, and set up the coordinate system */
{
	float ratio = WIDTH*1.0 / (HEIGHT*1.0);

    glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);


    glViewport( 0, 0, WIDTH, HEIGHT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	if(projection == 0)
	{
    	gluPerspective( fov, (float)WIDTH/(float)HEIGHT, 0.1, 100 );
	}
	else
	{
		if (ratio >= 1)
		{
			//gluOrtho2D(-100 * ratio , 100 * ratio, -100, 100);
			glOrtho(-100 * ratio , 100 * ratio, -100, 100, -100, 100);//so movement in Z doesnt lose object

		}
		else
		{
			//gluOrtho2D(-100, 100, -100 / ratio, 100 / ratio);
			glOrtho(-100 , 100 , -100 / ratio, 100 / ratio, -100, 100);//so movement in Z doesnt lose object

		}
	}
    glMatrixMode( GL_MODELVIEW );

}
void reset()
{
	std::cout << "reset, click ; to stop the animation walking\n";
	transZ = 0;
	transY = 0;
	transX = 0;
	thetaX = 0;
	thetaY = 0;
	thetaZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	upArmThetaY = 0;
	upArmThetaZ = 0;
	loArmThetaY = 0;
	loArmThetaZ = 0;
	legsThetaX = 0;
	legUp = false;
	walkZ = 0;
	camX = 0;
	camY = 0;
	camZ = 10;
	fov = 50;
	if(projection == 0)
		worldZ = -80.f;
	else worldZ = 0;
	initWindow();
	glutPostRedisplay();
}
/***************************************************************************/
void display(void)   
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

	//scale * rotate * translate
	glPushMatrix();
	//glTranslatef(0, 0, walkZ);
	glTranslatef(transX, transY, transZ); //user
    glTranslatef( 0.f, 0.f, worldZ + walkZ); // move to world coords [-100,100] for xyz based on projection and walk
	glRotatef(thetaX, 1, 0, 0); //user
	glRotatef(thetaY, 0, 1, 0); //user
	glRotatef(thetaZ, 0, 0, 1); //user
	glScalef(scaleX, scaleY, scaleZ); //user
	//glScalef(10,10,10); // scale to world
	drawRobot();
	// if(obj == 0) drawCube(1);
	// else if(obj == 1) drawSphere(1, 20, 20); //slices/stacks low in so you can see the sphere move better
	// else if(obj == 2) drawCylinder(1, 1);
	// else if(obj == 3) drawCone(1, 1);
	// else if(obj == 4) drawTorus(10, 20);
	glPopMatrix();


	glutSwapBuffers();                                      // Draw Frame Buffer 
	
	
}

void reshape( int w, int h )
{
	WIDTH = w;
	HEIGHT = h;
	float ratio = w*1.0 / (h*1.0);

    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	if(projection == 0)
	{
    	gluPerspective( fov, (float)w/(float)h, 0.1, 100 );
	}
	else
	{
		if (ratio >= 1)
		{
			//gluOrtho2D(-100 * ratio , 100 * ratio, -100, 100);
			glOrtho(-100 * ratio , 100 * ratio, -100, 100, -100, 100); //so movement in Z doesnt lose object

		}
		else
		{
			//gluOrtho2D(-100, 100, -100 / ratio, 100 / ratio);
			glOrtho(-100 , 100 , -100 / ratio, 100 / ratio, -100, 100);//so movement in Z doesnt lose object

		}
	}

	glMatrixMode( GL_MODELVIEW );
	
	glutPostRedisplay();

}

void idle()
{
	glutPostRedisplay();

	if(walking)
	{
		endTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<double, std::milli>(endTime - startTime).count() / 1000;
		elapsed = std::chrono::duration<double, std::milli>(endTime - timer).count() / 1000;
		if(dt <= (float)1/FPS) std::this_thread::sleep_for(std::chrono::milliseconds((int)(((float)1/FPS)*1000)-(int)(dt*1000)));
		second += (float)1/FPS;
		frames++;
		if(second >= 1){  second = 0; frames = 0;}
		startTime = endTime;

		walkZ += 2 * dt;
		if(legsThetaX >= 45) legUp = true;
		if(legsThetaX <= -45) legUp = false;
		if(legUp) legsThetaX--;
		else legsThetaX++;

		if(elapsed >= 30) 
		{
			walking = false;
			reset();
		}
	}
	//else walkZ = 0;
}
/***************************************************************************/
// Callback function for key click events
void keyboard(unsigned char key, int x, int y)  
{

	switch (key) {
	case 27: //Escape key
		glutDestroyWindow(windowHandle);
		break;
	case 'r':
		reset();
		break;
	case 'p':
		if(projection == 0)
		{
			projection = 1;
			worldZ = 0;
		}
		else if(projection == 1)
		{
			projection = 0;
			worldZ = -80.f;
		}
		initWindow();
		break;
	case 'x' :
		thetaX += 1;
		break;
	case 'y':
		thetaY += 6;
		break;
	case 'z' :
		thetaZ += 1;
		break;
	case 'X' :
		scaleX += 0.1;
		break;
	case 'Y':
		scaleY += 0.1;
		break;
	case 'Z' :
		scaleZ += 0.1;
		break;
	case 'w':
		camY += 1;
		break;
	case 's':
		camY -= 1;
		break;
	case 'W':
		camZ += 1;
		break;
	case 'S':
		camZ -= 1;
		break;
	case 'a':
		camX -= 1;
		break;
	case 'd':
		camX += 1;
		break;
	case 'f':
		fov += 1;
		initWindow();
		break;
	case 'F':
		fov -= 1;
		initWindow();
		break;
	case 'c':
		obj = 0;
		break;
	case 'v':
		obj = 1;
		break;
	case 'b':
		obj = 2;
		break;
	case 'n':
		obj = 3;
		break;		
	case 'm':
		obj = 4;
		break;	
	case '+':
		transZ += 1;
		break;
	case '-':
		transZ -= 1;
		break;
	case 'u':
		upArmThetaY += 1;
		break;
	case 'i':
		upArmThetaY -= 1;
		break;
	case 'o':
		upArmThetaZ += 1;
		break;
	case '0':
		upArmThetaZ -= 1;
		break;
	case 'h':
		loArmThetaY += 1;
		break;
	case 'j':
		loArmThetaY -= 1;
		break;
	case 'l':
		loArmThetaZ += 1;
		break;
	case 'k':
		loArmThetaZ -= 1;
		break;
	case ';':
		if(walking)
		{
			walking = false;
		}
		else 
		{
			walking = true;
			timer = std::chrono::high_resolution_clock::now();
			startTime = timer;
		}
		break;
	default:
		break;
	}
}
void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
	{
		transX -= 1;
	}
	else if (k == GLUT_KEY_RIGHT)
	{
		transX += 1;
	}
	else if (k == GLUT_KEY_UP)
	{
		transY += 1;
	}
	else if (k == GLUT_KEY_DOWN)
	{
		transY -= 1;

	}
}
int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						  */
	
	//while (currExample != 0)
	{
		//intakeChoice();
		
		glutInit(&argc, argv); 
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); 
		glutInitWindowSize(WIDTH,HEIGHT); 
		//glutInitWindowPosition(100,100);
		windowHandle = glutCreateWindow("aahartl CG4050/6050 A#04: Scene Graph and Animations" );
		glutDisplayFunc(display);  
		glutReshapeFunc(reshape);
		//glutTimerFunc(1000/FPS, idle, 0);
		glutIdleFunc(idle);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(specialKeys);
		initWindow();				             //create_window
		
		glutMainLoop();                 // Initialize The Main Loop
	}
}


