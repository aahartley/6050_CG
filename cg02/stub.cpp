//
//		          Programming Assignment #1
//
//					Daljit Singh Dhillon
//
//
/***************************************************************************/
/* Include needed files */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <climits>
/***************************************************************************/
// Forward declarations
void drawPixel(int x, int y);

// Main tasks for 4050
void drawCircle(int centerX, int centerY, int pointOnCricleX, int pointOnCricleY);
void drawParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY);
void drawCubicBezier(int* ptX, int* ptY);
/***************************************************************************/
//Main tasks for 6050
void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3);
void drawEllipse(int centerX, int centerY, int ptX1, int ptY1, int ptX2, int ptY2); //Bonus for 4050
void drawPoly(int ptX1, int ptY1, int ptX2, int ptY2);
void drawQuinticBezier(int* ptX, int* ptY);
/***************************************************************************/
//Few Bonus tasks
void drawCardinalSpline(int* ptX, int* ptY, int controlPointCount);
void drawCubicBSpline(int* ptX, int* ptY, int controlPointCount); //Not for 4050
void drawMidpointParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY);
/***************************************************************************/



// Main tasks for 4050
/***************************************************************************/
void drawCircle(int centerX, int centerY, int pointOnCricleX, int pointOnCricleY)
{
	drawPixel(centerX, centerY);
	drawPixel(pointOnCricleX, pointOnCricleY);
	//replace above two lines with your code
}

// Draw Parabola y-squared equals 'a' times x
// vertex is the tip of the parabola
void drawParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY)
{
	drawPixel(vertexX, vertexY);
	drawPixel(pointOnParabolaX, pointOnParabolaY);
	//replace above two lines with your code
}

void drawCubicBezier(int* ptX, int* ptY) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

// Main tasks for 6050
/***************************************************************************/
void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3) {
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	drawPixel(ptX3, ptY3);

	int maxX = ptX1;
	if(ptX2 > maxX) maxX =ptX2;
	if(ptX3 > maxX) maxX=ptX3;
	int minX = ptX1;
	if(ptX2 < minX) minX =ptX2;
	if(ptX3 < minX) minX=ptX3;

	int maxY = ptY1;
	if(ptY2 > maxY) maxY =ptY2;
	if(ptY3 > maxY) maxY=ptY3;

	int minY = ptY1;
	if(ptY2 < minY) minY =ptY2;
	if(ptY3 < minY) minY=ptY3;

	bool smile =false, frown =false;
	bool openP = false, closeP =false;
	if(ptY2==minY) smile =true;
	else if(ptY2==maxY) frown =true;
	else if(ptX2==minX) openP =true;
	else if(ptX2==maxX)closeP=true;
	
	//vector AB and BC
	int ABx= ptX2- ptX1;
	int ABy = ptY2- ptY1;

	int BCx = ptX3 - ptX2;
	int BCy = ptY3 - ptY2;
	
	//mid points
	int midX = (ptX1+ptX2)/2;
	int midY = (ptY1 + ptY2)/2;

	int midX2 = (ptX2 + ptX3)/2;
	int midY2 = (ptY2 + ptY3)/2;

	//Calculate perpendicular bisectors
	float m1 = -1.f*(float(ABx)/ABy);
	float m2 = -1.f*(float(BCx)/BCy);
	if(isinf(m1)) m1=midX;
	if(isinf(m2)) m2=midX2;
	float b1 = midY - m1 * midX;
	float b2 = midY2 - m2 * midX2;

	//solve system of equations to find intersection
	int centerX = (b2-b1)/(m1-m2);
	int centerY = m1 * centerX + b1;

	int radius = sqrt(std::pow(ptX2-centerX,2)+std::pow(ptY2-centerY,2));
	//draw arc
	int x = 0;
	int y = radius;
	int p = 1 - radius;
	if(closeP){

		maxX+=radius/2;
		maxY+=radius/2;
	}
	if(openP){

		minX-=radius/2;
		minY-=radius/2;
	}
	if((x+centerX < maxX && x+centerX > minX)&&frown)
		drawPixel(x+centerX, y+centerY);
	if((-x+centerX < maxX && -x+centerX > minX)&&smile)
		drawPixel(-x+centerX, -y+centerY);

	while(x<=y)
	{
		if(p<0)
			p+= ((2*x)+2)+1;
		else
		{
			p+= ((2*x)+2)+1 - ((2*y)-2);
			y--;
		}
		x++;

		int tmp1, tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8;
		int* x1 = nullptr; int* x2= nullptr; int* x3= nullptr; int* x4= nullptr;
		int* y1= nullptr; int* y2= nullptr; int* y3= nullptr; int* y4= nullptr;
		if((x+centerX <= maxX && x+centerX >= minX)){tmp1=x+centerX; x1 = &tmp1;}
		if((-x+centerX <= maxX && -x+centerX >= minX)){tmp2=-x+centerX; x2 =&tmp2;}
		if((y+centerX <= maxX && y+centerX >= minX)){tmp3=y+centerX; x3=&tmp3;}
		if((-y+centerX <= maxX && -y+centerX >= minX)){tmp4=-y+centerX; x4=&tmp4;} 

		if(openP || closeP){
			if((y+centerY <= maxY && y+centerY >= minY)){tmp5 =y+centerY; y1 =&tmp5;}
			if((-y+centerY <= maxY && -y+centerY >= minY)){tmp6 =-y+centerY; y2 =&tmp6;}
			if((x+centerY <= maxY && x+centerY >= minY)){tmp7=x+centerY; y3=&tmp7;}
			if((-x+centerY <= maxY && -x+centerY >= minY)){tmp8=-x+centerY; y4=&tmp8;}
		} 

		else{
			tmp5 =y+centerY; y1 =&tmp5;
			tmp6 =-y+centerY; y2 =&tmp6;
			tmp7=x+centerY; y3=&tmp7;
			tmp8=-x+centerY; y4=&tmp8;
		}

		if(x1 != nullptr && y1!=nullptr && !smile && !openP)
			drawPixel(*x1, *y1);
		if(x1 != nullptr && y2!=nullptr &&! frown && !openP)
			drawPixel(*x1, *y2);
		if(x2 != nullptr && y1!=nullptr &&! smile && !closeP )
			drawPixel(*x2, *y1);
		if(x2 != nullptr && y2!=nullptr && !frown && !closeP)
			drawPixel(*x2, *y2);
		if(x3 != nullptr && y3!=nullptr && !smile  && !openP)
			drawPixel(*x3, *y3);
		if(x3 != nullptr && y4!=nullptr && !frown && !openP )
			drawPixel(*x3, *y4);
		if(x4 != nullptr && y3!=nullptr && !smile && !closeP)
			drawPixel(*x4, *y3);
		if(x4 != nullptr && y4!=nullptr && !frown && !closeP)
			drawPixel(*x4, *y4);
	}

}
void drawEllipse(int centerX, int centerY, int ptX1, int ptY1, int ptX2, int ptY2)
{
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	drawPixel(centerX, centerY);

	int d1x = std::abs(ptX1-centerX);
	int d1y = std::abs(ptY1-centerY);
	int d2x = std::abs(ptX2-centerX);
	int d2y = std::abs(ptY2-centerY);
	int rx,ry;
	//the two points need to be on the major or minor axis, to find the radius or it will be arbitrary the points wont be on the ellipse
	if(d2x>d1x)
	{
		rx = std::sqrt(std::pow(ptX2-centerX,2)+std::pow(ptY2-centerY,2));
	}
	else
	{
		rx = std::sqrt(std::pow(ptX1-centerX,2)+std::pow(ptY1-centerY,2));
	}
	if(d2y>d1y)
	{
		ry = std::sqrt(std::pow(ptX2-centerX,2)+std::pow(ptY2-centerY,2));
	}
	else
	{
		ry = std::sqrt(std::pow(ptX1-centerX,2)+std::pow(ptY1-centerY,2));
	}	

    int x=0;
	int y=ry;

	int p =std::pow(ry,2) -(std::pow(rx,2)*ry)+(std::pow(rx,2)*0.25); 

	drawPixel(x+centerX, y+centerY);
	drawPixel(x+centerX, y-centerY);
	drawPixel(x-centerX, y+centerY);
	drawPixel(x-centerX, y+centerY);

	//region 1
	while((2*x*std::pow(ry,2))<=(2*y*std::pow(rx,2))) 
	{
		if(p<0) 
		{
			x++; 
			p=p+(2*std::pow(ry,2)*x) + std::pow(ry,2); 
		}
		else 
        {
            x++; 
            y--; 
            p=p+(2*std::pow(ry,2)*x) - (2*std::pow(rx,2)*y) + std::pow(ry,2); 
        }
		drawPixel(x+centerX, y+centerY);
		drawPixel(x+centerX, -y+centerY);
		drawPixel(centerX-x, -y+centerY);
		drawPixel(centerX-x, y+centerY);	
	}

    p = std::pow(ry,2)*std::pow((float)x+0.5,2) + std::pow(rx,2)*std::pow(y-1,2) - std::pow(rx,2)*std::pow(ry,2); 
	drawPixel(x+centerX, y+centerY);
	drawPixel(x+centerX, -y+centerY);
	drawPixel(-x+centerX, -y+centerY);
	drawPixel(-x+centerX, y+centerY);

	//region 2
    while(y>=0) 
    {
		if(p>0) 
        {
            y--; 
            p=p-(2*y*std::pow(rx,2))+ std::pow(rx,2); 
        }
        else 
        {
            y--; 
            x++; 
            p=p+(2*std::pow(ry,2)*x)-(2*y*std::pow(rx,2)) + std::pow(rx,2); 
        }
		drawPixel(x+centerX, y+centerY);
		drawPixel(x+centerX, -y+centerY);
		drawPixel(centerX-x, -y+centerY);
		drawPixel(centerX-x, y+centerY);  
	}
	
}

void drawPoly(int ptX1, int ptY1, int ptX2, int ptY2)
{	

	float crestX,crestY,troughY, troughX;
	if(ptY2 > ptY1){
		crestX = ptX2;
		troughX = ptX1;
		crestY = ptY2;
		troughY = ptY1;
	}
	else{
		crestX = ptX1;
		troughX = ptX2;
		crestY = ptY1;
		troughY = ptY2;
	}

	float fundamentalPeriod = std::abs(crestX - troughX)*2;
	float centerX = std::abs(crestX + troughX)/2;
	std::vector<float> coefficients;
	float c1 = std::sin(0.0);
	float c2 = 2.0/3.14;
	coefficients.push_back(c1);
	coefficients.push_back(c2);
	float amp = std::abs(crestY-troughY)/2;
	float wavelength = 1/std::abs(crestX-troughX)*2;
	//no need to measure magnitude of change, 4 is sufficient 
	for(int i=2; i<3; i++){
		//normalize the coefficients to create normalized sin wave by changing the factorial division
		coefficients.push_back((std::pow(-1.,(i-1)) * amp*wavelength)/ std::pow((i*3.14),i));

	}

	std::vector<float> xValues;
	float x = centerX;
	while(x<= centerX+fundamentalPeriod/2.0)
	{
   		xValues.push_back(x);
		x+=0.01;
	}

    std::vector<float> yValues;
    for (int j=0; j< xValues.size(); j++) {
		float value = 0.0;
    	for (int i = 0; i < coefficients.size(); i++) 
		{
      		value += coefficients[i] * std::pow(((xValues[j])- centerX)*amp*wavelength, i);
    	}

   		yValues.push_back(value);
  	}	
  	for(int i=0; i<xValues.size(); i++)
	{
		drawPixel((int)xValues[i]+crestX-centerX, (int)yValues[i]+crestY);
	}
}

void drawQuinticBezier(int* ptX, int* ptY) {

	float t=0;
	int x = ptX[0];
	int y = ptY[0];
	drawPixel(ptX[0], ptY[0]);
	while(t<=1.0f)
	{
		t+=0.001f;
		float b0 = std::pow((1 - t),5);
    	float b1 = 5 * t * std::pow((1 - t),4);
    	float b2 = 10 * std::pow(t,2) * std::pow((1 - t),3);
    	float b3 = 10 * std::pow(t,3) * std::pow((1 - t),2);
    	float b4 = 5 * std::pow(t,4) * (1 - t);
    	float b5 = std::pow(t,5);
		x=b0 * ptX[0] + b1 * ptX[1] + b2 * ptX[2] + b3 * ptX[3] + b4 * ptX[4] + b5 *ptX[5];
		y =b0 * ptY[0] + b1 * ptY[1] + b2 * ptY[2] + b3 * ptY[3] + b4 * ptY[4] + b5 *ptY[5];
		drawPixel(x, y);

	}
	

}

// BONUS TASKS
/***************************************************************************/
void drawMidpointParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY) 
{
	drawPixel(vertexX, vertexY);
	drawPixel(pointOnParabolaX, pointOnParabolaY);
	//replace above two lines with your code
}

void drawCardinalSpline(int* ptX, int* ptY, int controlPointCount) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

void drawCubicBSpline(int* ptX, int* ptY, int controlPointCount) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

