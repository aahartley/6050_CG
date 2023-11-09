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
float worldZ = -30.f
;
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
			gluOrtho2D(-100 * ratio , 100 * ratio, -100, 100);
		}
		else
		{
			gluOrtho2D(-100, 100, -100 / ratio, 100 / ratio);
		}
	}
    glMatrixMode( GL_MODELVIEW );

}
void reset()
{
	std::cout << "reset\n";
	transZ = 0;
	transY = 0;
	transX = 0;
	thetaX = 0;
	thetaY = 0;
	thetaZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	camX = 0;
	camY = 0;
	camZ = 10;
	fov = 50;
	if(projection == 0)
		worldZ = -30.f;
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

	glPushMatrix();
	glTranslatef(transX, transY, transZ);
    glTranslatef( 0.f, 0.f, worldZ ); // move to world coords [-100,100] for xyz based on projection
	glRotatef(thetaX, 1, 0, 0);
	glRotatef(thetaY, 0, 1, 0);
	glRotatef(thetaZ, 0, 0, 1);
	glScalef(scaleX, scaleY, scaleZ);
	glScalef(10,10,10); // scale to world
	if(obj == 0) drawCube();
	else if(obj == 1) drawSphere(1, 20, 20); //slices/stacks low in so you can see the sphere move better
	else if(obj == 2) drawCylinder(1, 1);
	else if(obj == 3) drawCone(1, 1);

	glPopMatrix();

	glutSwapBuffers();                                      // Draw Frame Buffer 
	glutPostRedisplay();
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
			gluOrtho2D(-100 * ratio , 100 * ratio, -100, 100);
		}
		else
		{
			gluOrtho2D(-100, 100, -100 / ratio, 100 / ratio);
		}
	}

	glMatrixMode( GL_MODELVIEW );
	
	glutPostRedisplay();

}

void idle()
{
	//thetaX += 1;
	//if( theta > 360) theta=0;
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
			worldZ = -30.f;
		}
		initWindow();
		break;
	case 'x' :
		thetaX += 1;
		break;
	case 'y':
		thetaY += 1;
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
	case '+':
		transZ += 1;
		break;
	case '-':
		transZ -= 1;
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
		windowHandle = glutCreateWindow("aahartl CG4050/6050 A#03: Object Transformations and Projections" );
		glutDisplayFunc(display);  
		glutReshapeFunc(reshape);
		glutIdleFunc(idle);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(specialKeys);
		initWindow();				             //create_window
		
		glutMainLoop();                 // Initialize The Main Loop
	}
}


