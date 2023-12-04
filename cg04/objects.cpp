#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>  
#include <math.h>

const float DtoR = 0.017453f;
const float PI = 3.14159f;


inline void drawCone(float r, float h)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0, h);
	for (int theta = 0; theta <= 360; theta += 5)
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);

	glEnd();
}


inline void drawCylinder(float r, float h)
{
	glBegin(GL_QUAD_STRIP);
	for (int theta = 0; theta <= 360; theta += 5)
	{
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), h);
	}
	glEnd();

	// top
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, h); 
	for (int theta = 0; theta <= 360; theta += 5) 
	{
    	glVertex3f(r * cos(theta * DtoR), r * sin(theta * DtoR), h);
	}
	glEnd();
	
	//bottom
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int theta = 0; theta <= 360; theta += 5)
	{
    	glVertex3f(r * cos(theta * DtoR), r * sin(theta * DtoR), 0);
	}
	glEnd();

}

inline void drawSphere(float r, int slices, int stacks)
{
	int longitude = 360 / slices;
	int latitude = 180 / stacks;
	int phi, theta;
	float p1[3], p2[3], p3[3], p4[3];

	for (phi = 0; phi < 180; phi += latitude) {
		for (theta = 0; theta < 360; theta += longitude) {
			p1[0] = r * sin(phi * DtoR) * cos(theta * DtoR);
			p1[1] = r * sin(phi * DtoR) * sin(theta * DtoR);
			p1[2] = r * cos(phi * DtoR);

			p2[0] = r * sin((phi + latitude) * DtoR) * cos(theta * DtoR);
			p2[1] = r * sin((phi + latitude) * DtoR) * sin(theta * DtoR);
			p2[2] = r * cos((phi + latitude) * DtoR);

			p3[0] = r * sin((phi + latitude) * DtoR) * cos((theta + longitude) * DtoR);
			p3[1] = r * sin((phi + latitude) * DtoR) * sin((theta + longitude) * DtoR);
			p3[2] = r * cos((phi + latitude) * DtoR);

			p4[0] = r * sin(phi * DtoR) * cos((theta + longitude) * DtoR);
			p4[1] = r * sin(phi * DtoR) * sin((theta + longitude) * DtoR);
			p4[2] = r * cos(phi * DtoR);

			glBegin(GL_POLYGON);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			glEnd();

		}
	}
}


inline void drawCube(float size)
{
	//local coords in [-1,1]
	glBegin(GL_QUADS);               
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(size, size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);

	glColor3f(0.7f, 0.3f, 0.3f);     // Orangey
	glVertex3f(size, -size, size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, -size, -size);
	glVertex3f(size, -size, -size);

	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);

	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);

	glColor3f(0.7f, .4f, .7f);     // Purpley
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	glColor3f(1.0f, 0.0f, 1.0f);     // Pink
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glEnd();  
	glColor3f(0.4f, 0.0f, 0.0f);     // Red

}

inline void drawTorus(int segments, int circumference) //shape of torus, # of points to approximate(smoothness)
{
   double twopi = 2 * PI;
   for (int i = 0; i < segments; i++) {
      glBegin(GL_QUAD_STRIP);
      for (int j = 0; j <= circumference; j++) {
         for (int k = 1; k >= 0; k--) {
            double s = (i + k) % segments + 0.5;
            double t = j % circumference;

            double x = (1+.1*cos(s*twopi/segments))*cos(t*twopi/circumference);
            double y = (1+.1*cos(s*twopi/segments))*sin(t*twopi/circumference);
            double z = .1 * sin(s * twopi / segments);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}
