//
//		          Programming Assignment #1
//
//					Daljit Singh Dhillon
//
//
/***************************************************************************/
/* Include needed files */



/***************************************************************************/
#include <iostream>
#include <cmath>
// Forward declarations
void drawPixel(int x, int y);

void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd);
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd);
void drawThickLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int lineWidth);
void drawLineSlopeIntercept(float slope, float yIntercept);
void draw2dAxesAndSquare(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float sqrBaseX, float sqrBaseY, float sqrWidth);
void draw3dAxesAndCube(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float zVecE1, float zVecE2, float cubeBaseX, float cubeBaseY, float cubeBaseZ, float cubeWidth);
void drawStyleDottedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDashedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDotAndDashLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);

void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd)
{
	drawPixel((int)xStart,(int)yStart);
	drawPixel((int)xEnd, (int)yEnd);

	//replace above two lines with your own inplementation
}

void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd)
{
	int x = xStart;
	int y = yStart;

	int dx = std::abs(xEnd - xStart);
	int dy = std::abs(yEnd - yStart);

	//signs for neg / pos slope. to add or subtract x/y
	int sX = (xEnd-xStart < 0) ? -1 : 1;
	int sY = (yEnd-yStart < 0) ? -1 : 1;
	bool flip =false;

	if(dy > dx) // slope greater than 1, swap dx and dy , to step along the y direction
	{
		int tmp = dx;
		dx = dy;
		dy = tmp;
		flip = true;
	}

	//decision parameter
	int P_k = 2*dy - dx;

	for(int i=0; i<dx; i++) // step along the longest axis
	{
		drawPixel(x,y);
		//std::cout << x << ' ' << y << '\n';
		if(P_k < 0) //plot upper pixel (dUpper is closer)
		{
			if(flip)
			{
				y = y+sY;
			}
			else
			{
				x = x+sX;
			}
			P_k = P_k + 2*dy;
		
		}
		else //plot lower pixel (dLower is closer)
		{
			y = y + sY;
			x = x +sX;
			P_k = P_k + (2*dy) - (2*dx);
		
		}
	}

}

void drawThickLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int lineWidth)
{
	int x = xStart;
	int y = yStart;

	int dx = std::abs(xEnd - xStart);
	int dy = std::abs(yEnd - yStart);

	//signs for neg / pos slope. to add or subtract x/y
	int sX = (xEnd-xStart < 0) ? -1 : 1;
	int sY = (yEnd-yStart < 0) ? -1 : 1;
	bool flip =false;

	if(dy > dx) // slope greater than 1, swap dx and dy , to step along the y direction
	{
		int tmp = dx;
		dx = dy;
		dy = tmp;
		flip = true;
	}

	//decision parameter
	int P_k = 2*dy - dx;

	for(int i=0; i<dx; i++) // step along the longest axis
	{
		for(int j=0; j<lineWidth; j++)
		{
			if(flip)
			{
				drawPixel(x+j,y);

			}
			else
			{
				drawPixel(x,y+j);
			}
		}
		//std::cout << x << ' ' << y << '\n';
		if(P_k < 0) //plot upper pixel (dUpper is closer)
		{
			if(flip)
			{
				y = y+sY;
			}
			else
			{
				x = x+sX;
			}
			P_k = P_k + 2*dy;
		
		}
		else //plot lower pixel (dLower is closer)
		{
			y = y + sY;
			x = x +sX;
			P_k = P_k + (2*dy) - (2*dx);
		
		}
	}
}

void drawStyleDottedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	int x = xStart;
	int y = yStart;

	int dx = std::abs(xEnd - xStart);
	int dy = std::abs(yEnd - yStart);

	//signs for neg / pos slope. to add or subtract x/y
	int sX = (xEnd-xStart < 0) ? -1 : 1;
	int sY = (yEnd-yStart < 0) ? -1 : 1;
	bool flip =false;

	if(dy > dx) // slope greater than 1, swap dx and dy , to step along the y direction
	{
		int tmp = dx;
		dx = dy;
		dy = tmp;
		flip = true;
	}

	//decision parameter
	int P_k = 2*dy - dx;
	int dot = 10;
	for(int i=0; i<dx; i++) // step along the longest axis
	{
	
		if(i%dot==0)drawPixel(x,y);
		//std::cout << x << ' ' << y << '\n';
		if(P_k < 0) //plot upper pixel (dUpper is closer)
		{
			if(flip)
			{
				y = y+sY;
			}
			else
			{
				x = x+sX;
			}
			P_k = P_k + 2*dy;
		
		}
		else //plot lower pixel (dLower is closer)
		{
			y = y + sY;
			x = x +sX;
			P_k = P_k + (2*dy) - (2*dx);
		
		}
	}
}

void drawStyleDashedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	int x = xStart;
	int y = yStart;

	int dx = std::abs(xEnd - xStart);
	int dy = std::abs(yEnd - yStart);

	//signs for neg / pos slope. to add or subtract x/y
	int sX = (xEnd-xStart < 0) ? -1 : 1;
	int sY = (yEnd-yStart < 0) ? -1 : 1;
	bool flip =false;

	if(dy > dx) // slope greater than 1, swap dx and dy , to step along the y direction
	{
		int tmp = dx;
		dx = dy;
		dy = tmp;
		flip = true;
	}

	//decision parameter
	int P_k = 2*dy - dx;
	int dash = 10;
	int count = 0;
	bool countSpace = false;
	int countS =0;
	for(int i=0; i<dx; i++) // step along the longest axis
	{
		for(int j=0; j<lineWidth; j++)
		{
			if(flip)
			{
				if(count!=dash&&!countSpace)
				{
					drawPixel(x+j,y);
				}
				else
				{
					countSpace = true;
					countS++;
					if(countS==15)
					{
						count=0;
						countS=0;
						countSpace=false;
					}
				}

			}
			else
			{
				if(count!=dash&&!countSpace)
				{
					drawPixel(x,y+j);
				}
				else
				{
					countSpace = true;
					countS++;
					if(countS==15)
					{
						count=0;
						countS=0;
						countSpace=false;
					}
				}
			}
		}
 
		//std::cout << x << ' ' << y << '\n';
		if(P_k < 0) //plot upper pixel (dUpper is closer)
		{
			if(flip)
			{
				y = y+sY;
			}
			else
			{
				x = x+sX;
			}
			P_k = P_k + 2*dy;
		
		}
		else //plot lower pixel (dLower is closer)
		{
			y = y + sY;
			x = x +sX;
			P_k = P_k + (2*dy) - (2*dx);
		
		}
		count++;
	}
}

void drawStyleDotAndDashLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	drawPixel((int)xStart,(int)yStart);
	drawPixel((int)xEnd, (int)yEnd);

	//replace above two lines with your own inplementation
}


void drawLineSlopeIntercept(float slope, float yIntercept)
{
	//800x600
	int yEnd = slope*800+yIntercept;
	//int xEnd = yEnd/slope -yIntercept;
	drawLineBresenham(0,yIntercept,800,yEnd);

	//replace above two lines with your own inplementation
}
void draw2dAxesAndSquare(float orgX, float orgY,
						 float xVecE1, float xVecE2,
						 float yVecE1, float yVecE2,
						 float cubeBaseX, float cubeBaseY, float cubeWidth)
{
	drawPixel((int)orgX,(int)orgY);
	drawPixel((int)orgX, (int)orgY);

	//replace above two lines with your own inplementation
}
void draw3dAxesAndCube(float orgX, float orgY,
					   float xVecE1, float xVecE2,
					   float yVecE1, float yVecE2,
					   float zVecE1, float zVecE2,
					   float cubeBaseX, float cubeBaseY, float cubeBaseZ, float cubeWidth)
{
	drawPixel((int)orgX,(int)orgY); //origin

	float xMag = sqrt(std::pow(xVecE1,2)+std::pow(xVecE2,2));
	xVecE1 = xVecE1/xMag;
	xVecE2 = xVecE2/xMag;
	drawLineBresenham(-800*xVecE1+(int)orgX, (-600*xVecE2)+(int)orgY, 800*xVecE1+(int)orgX, (600*xVecE2)+(int)orgY); //x


	float yMag = sqrt(std::pow(yVecE1,2)+std::pow(yVecE2,2));
	yVecE1 = yVecE1/yMag;
	yVecE2 = yVecE2/yMag;
	drawLineBresenham(-800*yVecE1+(int)orgX, (-600*yVecE2)+(int)orgY, 800*yVecE1+(int)orgX, (600*yVecE2)+(int)orgY); //y

	float zMag = sqrt(std::pow(zVecE1,2)+std::pow(zVecE2,2));
	zVecE1 = zVecE1/zMag;
	zVecE2 = zVecE2/zMag;
	drawLineBresenham(-800*zVecE1+(int)orgX, (-600*zVecE2)+(int)orgY, 800*zVecE1+(int)orgX, (600*zVecE2)+(int)orgY); //z

	float x_1 = cubeBaseX*xVecE1;
	float x_2 = cubeBaseX*xVecE2;
	float y_1 = cubeBaseY*yVecE1;
	float y_2 = cubeBaseY*yVecE2;
	float z_1 = cubeBaseZ*zVecE1;
	float z_2 = cubeBaseZ*zVecE2;
	float x = x_1 + y_1 + z_1;
	float y = x_2 + y_2 + z_2;

	//verts
	drawPixel(x+(int)orgX, y+(int)orgY);
	drawPixel(x+(int)orgX, y+(int)orgY+cubeWidth);
	drawPixel(x+(int)orgX+cubeWidth, y+(int)orgY);
	drawPixel(x+(int)orgX+cubeWidth, y+(int)orgY+cubeWidth);

	drawPixel(x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2);
	drawPixel(x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2+cubeWidth);
	drawPixel(x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2);
	drawPixel(x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2+cubeWidth);

	//squares
	drawLineBresenham(x+(int)orgX, y+(int)orgY,x+(int)orgX, y+(int)orgY+cubeWidth);
	drawLineBresenham(x+(int)orgX, y+(int)orgY,x+(int)orgX+cubeWidth, y+(int)orgY);
	drawLineBresenham(x+(int)orgX, y+(int)orgY+cubeWidth,x+(int)orgX+cubeWidth, y+(int)orgY+cubeWidth);
	drawLineBresenham(x+(int)orgX+cubeWidth, y+(int)orgY,x+(int)orgX+cubeWidth, y+(int)orgY+cubeWidth);

	drawLineBresenham(x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2,x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2+cubeWidth);
	drawLineBresenham(x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2,x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2);
	drawLineBresenham(x+(int)orgX+cubeWidth/2, y+(int)orgY+cubeWidth/2+cubeWidth,x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2+cubeWidth);
	drawLineBresenham(x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2,x+(int)orgX+cubeWidth/2+cubeWidth, y+(int)orgY+cubeWidth/2+cubeWidth);

	//connect squares
	drawLineBresenham(x+(int)orgX, y+(int)orgY, x+(int)orgX+cubeWidth/2,y+(int)orgY+cubeWidth/2);
	drawLineBresenham(x+(int)orgX+cubeWidth, y+(int)orgY, x+(int)orgX+cubeWidth/2+cubeWidth,y+(int)orgY+cubeWidth/2);

	drawLineBresenham(x+(int)orgX, y+(int)orgY+cubeWidth, x+(int)orgX+cubeWidth/2,y+(int)orgY+cubeWidth/2+cubeWidth);
	drawLineBresenham(x+(int)orgX+cubeWidth, y+(int)orgY+cubeWidth, x+(int)orgX+cubeWidth/2+cubeWidth,y+(int)orgY+cubeWidth/2+cubeWidth);

}