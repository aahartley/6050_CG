/******************************************************************************|
| CPSC 4050/6050 Computer Garphics Assignment 5, Daljit Singh Dhillon, 2020    |
| Reference:                                                                   |
|                                                                              |
| Some OpenGL setup code here including math_funcs, and gl_utils               |
| are from Angton Gerdelan and "Anton's OpenGL 4 Tutorials."                   |
| http://antongerdelan.net/opengl/                                             |
| Email: anton at antongerdelan dot net                                        |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
|******************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>

#include <math.h>
#include <time.h>

#include "maths_funcs.h"   // Anton's maths functions.
#include "gl_utils.h"      // Anton's opengl functions and small utilities like logs
#include "stb_image.h"     // Sean Barrett's image loader with Anton's load_texture()

#define _USE_MATH_DEFINES
#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

mat4 view_mat;
mat4 proj_mat;
mat4 model_mat;


int pointCount;

// void drawQuinticBezier(int* ptX, int* ptY) {

// 	float t=0;
// 	int x = ptX[0];
// 	int y = ptY[0];
// 	drawPixel(ptX[0], ptY[0]);
// 	while(t<=1.0f)
// 	{
// 		t+=0.0001f;
// 		float b0 = std::pow((1 - t),5);
//     	float b1 = 5 * t * std::pow((1 - t),4);
//     	float b2 = 10 * std::pow(t,2) * std::pow((1 - t),3);
//     	float b3 = 10 * std::pow(t,3) * std::pow((1 - t),2);
//     	float b4 = 5 * std::pow(t,4) * (1 - t);
//     	float b5 = std::pow(t,5);
// 		x=b0 * ptX[0] + b1 * ptX[1] + b2 * ptX[2] + b3 * ptX[3] + b4 * ptX[4] + b5 *ptX[5];
// 		y =b0 * ptY[0] + b1 * ptY[1] + b2 * ptY[2] + b3 * ptY[3] + b4 * ptY[4] + b5 *ptY[5];
// 		drawPixel(x, y);

// 	}
	

// }

void loadQuinticBezierBaseCurve(std::vector<vec2>& curve, float ymin, float ymax, float rmin, float rmax, int num_step)
{
	// std::vector<vec2> ctrl_points =  {vec2{ymin + 0.1, rmin}, vec2{0.2 * (ymax - ymin) + ymin, rmax},
    //  								 vec2{0.4 * (ymax - ymin) + ymin - 0.1, 0.5 * (rmax - rmin) + rmin},
    //   								 vec2{0.6 * (ymax - ymin) + ymin + 0.1, 0.5 * (rmax - rmin) + rmin},
    //   								 vec2{0.8 * (ymax - ymin) + ymin, rmax},
    //   								 vec2{ymax - 0.1, rmin}};
	std::vector<vec2> ctrl_points =  {vec2{0,0.1}, vec2{0.4,0.2},
     								 vec2{0.5, 0.5},
      								 vec2{0.1,0.7},
      								 vec2{0.0,0.8},
      								 vec2{0.1,0.99}};									 
	float t = 0;
	for(int i = 0; i < num_step; i++)
	{	
		t = (float)i/float(num_step-1);
		float b0 = ((1-t) * (1-t) * (1-t) * (1-t) * (1-t));
    	float b1 = 5 * t * ((1-t) * (1-t) * (1-t) * (1-t));
    	float b2 = 10 * (t*t) * ((1-t) * (1-t) * (1-t));
    	float b3 = 10 * (t*t*t) * ((1-t) * (1-t));
    	float b4 = 5 * (t*t*t*t) * (1 - t);
    	float b5 = (t*t*t*t*t);
		float x = b0 * ctrl_points[0].v[0] + b1 * ctrl_points[1].v[0] + b2 * ctrl_points[2].v[0] + b3 * ctrl_points[3].v[0] + b4 * ctrl_points[4].v[0] + b5 *ctrl_points[5].v[0];
		float y = b0 * ctrl_points[0].v[1] + b1 * ctrl_points[1].v[1] + b2 * ctrl_points[2].v[1] + b3 * ctrl_points[3].v[1] + b4 * ctrl_points[4].v[1] + b5 *ctrl_points[5].v[1];
		vec2 v = {x,y};
		curve[i] = v;
	

	}

}


void loadSurfaceOfRevolution(int y_max, int theta_max) 
{

	int size = y_max * theta_max * 3;
	/*------------------------------CREATE GEOMETRY-------------------------------*/
	GLfloat* vp1 = new GLfloat[y_max*theta_max*3];    // array of vertex points
	GLfloat* vp2 = new GLfloat[y_max*theta_max*3*4];    // array of vertex points
	GLfloat* vp3 = new GLfloat[y_max*theta_max*3*3];    // array of vertex points

	std::vector<vec2> curve(y_max);
	std::vector<vec3> surface(y_max * theta_max);
	loadQuinticBezierBaseCurve(curve, 0, 1, 0, 1, y_max);
	float theta;
	for (int i = 0; i < curve.size(); ++i) {
  		for (int j = 0; j < theta_max; ++j) {
    		theta = (float)j / float(theta_max - 1) * 360;

    		float x = curve[i].v[0] * std::cos(theta * ONE_DEG_IN_RAD);
    		float y = curve[i].v[1];
    		float z = curve[i].v[0] * std::sin(theta * ONE_DEG_IN_RAD);

    		surface[i * theta_max + j] = vec3{x, y, z};
  		}
	}

	for(int i = 0; i < y_max * theta_max; i++)
	{
		vp1[i*3] = surface[i].v[0];
		vp1[(i*3)+1] = surface[i].v[1];
		vp1[(i*3)+2] = surface[i].v[2];

	}
	//(((j+1)+(i*100))*3)
	for(int i = 0; i < y_max; i+=4)//row
	{
		for(int j = 0; j < theta_max; j+=4)//col
		{
			//0
			vp2[((j+(i*100))*3)] = vp1[((j+(i*100))*3)];
			vp2[((j+(i*100))*3)+1] = vp1[((j+(i*100))*3)+1];
			vp2[((j+(i*100))*3)+2] = vp1[((j+(i*100))*3)+2];

			//1
			vp2[(((j)+(i*100))*3)+3] = vp1[(((j+1)+(i*100))*3)];
			vp2[(((j)+(i*100))*3)+4] = vp1[((j+(i*100))*3)+1];
			vp2[(((j)+(i*100))*3)+5] = vp1[((j+(i*100))*3)+2];

			//2
			vp2[(((j)+((i)*100))*3)+6] = vp1[(((j+1)+((i+1)*100))*3)];
			vp2[(((j)+((i)*100))*3)+7] = vp1[((j+((i+1)*100))*3)+1];
			vp2[(((j)+((i)*100))*3)+8] = vp1[((j+((i+1)*100))*3)+2];

			//3
			vp2[((j+(i*100))*3)+9] = vp1[((j+((i+1)*100))*3)];
			vp2[((j+(i*100))*3)+10] = vp1[((j+((i+1)*100))*3)+1];
			vp2[((j+(i*100))*3)+11] = vp1[((j+((i+1)*100))*3)+2];
		}
	}
	








/*------------------------------CREATE GEOMETRY-------------------------------*/
	GLfloat vp[18];    // array of vertex points
	
	//face 1, vertex 1
	vp[0] = -1; //x
	vp[1] = -1; //y
	vp[2] = 0; //z
	//face 1, vertex 2
	vp[3] = 1; //x
	vp[4] = -1; //y
	vp[5] = 0; //z
	//face 1, vertex 3
	vp[6] = -1; //x
	vp[7] =  1; //y
	vp[8] =  0; //z
	
	//face 2, vertex 1
	vp[ 9] = -1; //x
	vp[10] =  1; //y
	vp[11] = 0; //z
	//face 2, vertex 2
	vp[12] =  1; //x
	vp[13] = -1; //y
	vp[14] = 0; //z
	//face 2, vertex 3
	vp[15] =  1; //x
	vp[16] =  1; //y
	vp[17] =  0; //z
	
	
	
	// VAO -- vertex attribute objects bundle the various things associated with vertices
	GLuint vao;
	glGenVertexArrays (1, &vao);   // generating and binding is common pattern in OpenGL
	glBindVertexArray (vao);       // basically setting up memory and associating it

	// VBO -- vertex buffer object to contain coordinates
	// MODIFY THE FOLLOWING BLOCK OF CODE APPRORIATELY FOR YOUR SURFACE OF REVOLUTION
	GLuint points_vbo;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof (GLfloat), vp2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// VBO -- normals -- needed for shading calcuations
	// ADD CODE TO POPULATE AND LOAD PER-VERTEX SURFACE NORMALS  
	// [HINT] Vertex normals are organized in same order as that for vertex coordinates

    // VBO -- vt -- texture coordinates
	// ADD CODE TO POPULATE AND LOAD PER-VERTEX TEXTURE COORDINATES  
	// [HINT] texture coordinates are organized in same order as that for vertex coordinates
	// [HINT] there are two texture coordinates instead of three vertex coordinates for each vertex
}


	
void loadUniforms(GLuint shader_programme)
{	
/*---------------------------SET RENDERING DEFAULTS---------------------------*/

	// Choose vertex and fragment shaders to use as well as view and proj matrices.
	int model_mat_location = glGetUniformLocation (shader_programme, "model_mat");
	int view_mat_location  = glGetUniformLocation (shader_programme, "view_mat");
	int proj_mat_location  = glGetUniformLocation (shader_programme, "proj_mat");
	
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat.m);
	glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
	
	// WRITE CODE TO LOAD OTHER UNIFORM VARIABLES LIKE FLAGS FOR ENABLING OR DISABLING CERTAIN FUNCTIONALITIES
}

void drawSurfaceOfRevolution(int y_max, int theta_max)
{
	// MODIFY THIS LINE OF CODE APPRORIATELY FOR YOUR SURFACE OF REVOLUTION
	glDrawArrays(GL_POINTS, 0, y_max * theta_max * 3);
}
	
void keyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// MODIFY THIS FUNCTION FOR KEYBOARD INTERACTIVITY
	//GLFW Reference Links:
	// Callback Example: https://www.glfw.org/docs/3.3/input_guide.html#input_key
	// List of Keys: https://www.glfw.org/docs/3.3/group__keys.html
	
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
		printf("\nKey 'E' pressed.... \n");
        // Example case. Key 'E' pressed. Doing nothing
	}
        
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
		// Close window when esacape is pressed
			glfwSetWindowShouldClose (g_window, 1);
	}

}
