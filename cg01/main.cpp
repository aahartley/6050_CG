//
//		          Programming Assignment #1 
//
//					Daljit Singh Dhillon 
//
// (Heavily!) adapted from the sample code from Prof. Victor Zordan - 
// CPSC4050/6050 : Spring2019
//
/***************************************************************************/

/* Include needed files */
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#define WIDTH 800
#define HEIGHT 600

int currExample =1;
int	xPrev = -1, yPrev = -1, xCurr = 0, yCurr = 0;

float slope, yInter;

float orgX, orgY, xVecE1, xVecE2, yVecE1, yVecE2, zVecE1, zVecE2;
float baseX, baseY, baseZ, sizeA;

int lineThick;

/***************************************************************************/
// Forward declarations
void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd);
void drawLineSlopeIntercept(float slope, float yIntercept);
void draw2dAxesAndSquare(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float sqrBaseX, float sqrBaseY, float sqrWidth);
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd);
void drawThickLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int lineWidth);
void draw3dAxesAndCube(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float zVecE1, float zVecE2, float cubeBaseX, float cubeBaseY, float cubeBaseZ, float cubeWidth);
void drawStyleDottedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDashedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDotAndDashLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);

void drawPixel(int x, int y);

void callDrawLineDDA()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawLineDDA(xPrev, yPrev, xCurr, yCurr);
	}
}

void callDrawLineBresenham()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawLineBresenham( xPrev, yPrev, xCurr, yCurr);
	}
}


void callDrawThickLineBresenham()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawThickLineBresenham( xPrev, yPrev, xCurr, yCurr, lineThick);
	}
}

void callDot()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawStyleDottedLine( xPrev, yPrev, xCurr, yCurr, lineThick);
	}
}

void callDash()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawStyleDashedLine( xPrev, yPrev, xCurr, yCurr, lineThick);
	}
}

void callDDStyle()
{
	drawPixel(xCurr,yCurr);
	if (xPrev>0) {
		drawStyleDotAndDashLine( xPrev, yPrev, xCurr, yCurr, lineThick);
	}
}


void callDrawLineSlopeIntercept()
{
	drawPixel(xCurr,yCurr);
	drawLineSlopeIntercept(slope, yInter);
	
}

void callSquare()
{

	drawPixel(orgX,orgY);
	draw2dAxesAndSquare( orgX,  orgY,  
						xVecE1,  xVecE2,  
						yVecE1,  yVecE2,  
						baseX,  baseY, sizeA);

	
}
void callCube()
{

	drawPixel(orgX,orgY);
	draw3dAxesAndCube( orgX,  orgY,  
						xVecE1,  xVecE2,  
						yVecE1,  yVecE2,  
						zVecE1,  zVecE2,  
						baseX,  baseY,  baseZ,  sizeA);

	
}
/***************************************************************************/

void initWindow()
/* Clear the image area, and set up the coordinate system */
{
    glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
    glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/

void drawPixel(int x, int y)
/* Turn on the pixel found at x,y */
{
        glColor3f (1.0, 1.0, 1.0);                 
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();	
}

//***************************************************************************/
/*
 * 		printf("\nChoose one of the following menu options and enter required data.\n");
		printf("When all required data is entered, a window will appear with results for the corresponding example.\n");
		printf("Press \'Escape\' key with focus on any such window to exit the main program.\n\n Your menu options are:\n");
		printf("Enter 1 :  to draw line using DDA (cpsc4050)\n");
		printf("Press 2 :  to draw line using slope-intercept form (both cpsc4050 and cpsc6050)\n");
		printf("Press 3 :  to draw 2D axes and a square (cpsc4050)\n");
		printf("Press 4 :  to draw dotted line (both cpsc4050 and cpsc6050)\n");
		printf("Press 5 :  to draw dashed line (both cpsc4050 and cpsc6050)\n");
		printf("Press 6 :  to draw dot-dash line (both cpsc4050 and cpsc6050)\n");
		printf("Press 7 :  to draw line using Bresenham algorithm (cpsc6050)\n");
		printf("Press 8 :  to draw 3D axes and a cube (cpsc6050)\n");
		printf("Press 9 :  to draw thick line using Bresenham algorithm (cpsc6050)\n\n");
		printf("Enter 0 :  to exit main program\n");
		* */
void display(void)   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 

	switch ( currExample ) 
	{
		case 0:              
			exit ( 0 );      // Exit The Program
		case 1:             
		        callDrawLineDDA();
			break;
		case 2:            
		        callDrawLineSlopeIntercept();
			break;
		case 3:             
		        callSquare();
			break;
			
		case 4:             
		        callDot();
			break;
			
		case 5:             
		        callDash();
			break;
			
		case 6:             
		        callDDStyle();
			break;
			
		case 7:             
		        callDrawLineBresenham();
			break;


		case 8:             
		        callCube();
			break;
		case 9:             
		        callDrawThickLineBresenham();
			break;
		default:       
			break;
	}
	
  glutSwapBuffers();                                      // Draw Frame Buffer 
}


/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{

	switch ( key ) {
		case 27:              // When Escape Is Pressed...
			//initWindow();
			xPrev = -1;
			yPrev = -1;
			xCurr = 0;
			yCurr = 0;
			break;        
	     default:       
			break;
	}
}

#define MENU_OPTION_COUNT 9
/***************************************************************************/
void intakeChoice()
{
		printf("\nChoose one of the following menu options and enter required data.\n");
		printf("When all required data is entered, a window will appear with results for the corresponding example.\n");
		printf("Press \'Escape\' key with focus on any such window to exit the main program.\n\n Your menu options are:\n");
		printf("Enter 1 :  to draw line using DDA (cpsc4050)\n");
		printf("Press 2 :  to draw line using slope-intercept form (both cpsc4050 and cpsc6050)\n");
		printf("Press 3 :  to draw 2D axes and a square (cpsc4050)\n");
		printf("Press 4 :  to draw dotted line (both cpsc4050 and cpsc6050)\n");
		printf("Press 5 :  to draw dashed line (both cpsc4050 and cpsc6050)\n");
		printf("Press 6 :  to draw dot-dash line (both cpsc4050 and cpsc6050)\n");
		printf("Press 7 :  to draw line using Bresenham algorithm (cpsc6050)\n");
		printf("Press 8 :  to draw 3D axes and a cube (cpsc6050)\n");
		printf("Press 9 :  to draw thick line using Bresenham algorithm (cpsc6050)\n\n");
		printf("Enter 0 :  to exit main program\n");
		printf("Enter your choice: ");
		scanf("%d", &currExample);
		
		if(currExample ==0)
		{
			exit(0);
		}
		
		while (0 > currExample || currExample > MENU_OPTION_COUNT)
		{
			printf("\nInvalid choice, enter your choice again: ");
			scanf("%d", &currExample);
		}
		
		switch (currExample)
		{
			case 4:
			case 5:
			case 6:
			case 9:
				printf("\nEnter your line's thickness in pixel units: ");
				scanf("%d", &lineThick);
			case 1:
			case 7:
				printf("\n Click two points with mouse to draw a line.");
				printf("\n Any additional click will connect previous point to current click.");
				printf("\n Press escape to re-initialize point selections.\n");
				break;
			case 2:
				printf("\n Enter slope (i.e. m, in y=mx+c) for your line: ");
				scanf("%f", &slope);
				printf("\n Enter its y-intercept (i.e. c, in y=mx+c) for it: ");
				scanf("%f", &yInter);
				
				printf("\n Draw line for given value of slope m = %f, and y-intercept c = %f.", slope, yInter);
				break;
			case 3:
				printf("\n Enter x and y coordinates for your origin separated by whitespace/blank: ");
				scanf("%f", &orgX);
				scanf("%f", &orgY);

				printf("\n Enter 'a' and 'b' as in vector [a,b] pointing towards your (+) x-axis: ");
				scanf("%f", &xVecE1);
				scanf("%f", &xVecE2);

				printf("\n Enter 'c' and 'd' as in vector [c,d] pointing towards your (+) y-axis: ");
				scanf("%f", &yVecE1);
				scanf("%f", &yVecE2);


				printf("\n Enter 'p' and 'q' for the point (p,q) that forms the base for your square : ");
				scanf("%f", &baseX);
				scanf("%f", &baseY);

				printf("\n Enter size for your square : ");
				scanf("%f", &sizeA);
				printf("\n Draw axes and the square with the input data.\n");
				
				break;
			case 8:
				printf("\n Enter x and y coordinates for your origin separated by whitespace/blank: ");
				scanf("%f", &orgX);
				scanf("%f", &orgY);

				printf("\n Enter 'a' and 'b' as in vector [a,b] pointing towards your (+) x-axis: ");
				scanf("%f", &xVecE1);
				scanf("%f", &xVecE2);

				printf("\n Enter 'c' and 'd' as in vector [c,d] pointing towards your (+) y-axis: ");
				scanf("%f", &yVecE1);
				scanf("%f", &yVecE2);

				printf("\n Enter 'e' and 'f' as in vector [e,f] pointing towards your (+) z-axis: ");
				scanf("%f", &zVecE1);
				scanf("%f", &zVecE2);

				printf("\n Enter 'p', 'q' and 'r' for the point (p,q,r) that forms the base for your cube : ");
				scanf("%f", &baseX);
				scanf("%f", &baseY);
				scanf("%f", &baseZ);

				printf("\n Enter size for your cube : ");
				scanf("%f", &sizeA);
				printf("\n Draw axes and the cube with the input data.\n");
				
				break;
			default:
				break;
		}
}
/***************************************************************************/
void mouse(int button, int state, int x, int y)
{
/* This function I(Victor) finessed a bit, the value of the printed x,y should
   match the screen, also it remembers where the old value was to avoid multiple
   readings from the same mouse click.  This can cause problems when trying to
   start a line or curve where the last one ended */
        static int oldx = 0;
        static int oldy = 0;
	int mag;
	
	y *= -1;  //align y with mouse
	y += HEIGHT; //ignore 
	mag = (oldx - x)*(oldx - x) + (oldy - y)*(oldy - y);
	if (mag > 5) {
		printf(" x,y is (%d,%d)\n", x,y);
		oldx = x;
		oldy = y;
		xPrev = xCurr;
		yPrev = yCurr;
		xCurr = x;
		yCurr = y;
	}
}

int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						  */
	
	//while (currExample != 0)
	{
		intakeChoice();
		
		glutInit            ( &argc, argv ); 
		glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
		glutInitWindowSize  ( WIDTH,HEIGHT ); 
		glutCreateWindow    ( "CG4050/6050 A#01: Lets get few things straight! --aahartl" ); 
		glutDisplayFunc     (display);  
		glutIdleFunc	    (display);
		glutMouseFunc       ( mouse );
		glutKeyboardFunc    ( keyboard);
		initWindow();				             //create_window
		
		glutMainLoop();                 // Initialize The Main Loop

		
	}
}


