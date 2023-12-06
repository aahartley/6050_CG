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
vec3 cam_pos;
vec3 light_pos;
vec3 light_color;
vec3 object_color;

struct Quad
{
	Quad(){}
	std::vector<vec3> v = std::vector<vec3>(4);
};

struct Triangle
{
	Triangle(){}
	std::vector<vec3> v = std::vector<vec3>(3);
};
void calculateTriangleNormal(std::vector<vec3>& tri_normals, std::vector<Triangle>& tris)
{
	for(int i = 0; i < tris.size(); i++)
	{
		vec3 e0 = tris[i].v[1] - tris[i].v[0];
		vec3 e1 = tris[i].v[2] - tris[i].v[0];
		vec3 normal = cross(e0, e1);
		normal = normalise(normal);
		tri_normals[i] = normal;

	}
}

void calculateTextureCoords(std::vector<vec2>& tex_coords, std::vector<vec3>& surface)
{
	for(int i = 0; i < surface.size(); i++)
	{
		float r, theta, phi, normalizedTheta, normalizedPhi, u, v;
		r = sqrt(surface[i].v[0] * surface[i].v[0] + surface[i].v[1] * surface[i].v[1] + surface[i].v[2] * surface[i].v[2]);
		theta = atan2(surface[i].v[1], surface[i].v[0]);
		phi = acos(surface[i].v[2] / r);
	

      // Regular spherical mapping
       normalizedTheta = theta / (2.0f * M_PI);
       normalizedPhi = phi / M_PI;
      u = normalizedTheta;
      v = 1.0f - normalizedPhi;
	  u = acos(surface[i].v[1]/r)/M_PI;
	  v=(atan2(surface[i].v[2],surface[i].v[0])/M_PI+1)*0.5f;
      tex_coords[i] = vec2(v, u);
    
	}
}


void loadQuinticBezierBaseCurve(std::vector<vec2>& curve, float ymin, float ymax, float rmin, float rmax, int num_step)
{
	std::vector<vec2> ctrl_points =  {vec2{0,-.8}, vec2{0.3,-.6},
     								 vec2{0.4, -.3},
      								 vec2{0.5,0},
      								 vec2{0.4,0.3},
      								 vec2{0,0.8}};	
	// std::vector<vec2> ctrl_points =  {vec2{0,0.2}, vec2{0.4,0.2},  //dont normalise for vase
    //  								 vec2{0.5, 0.5},
    //   								 vec2{0.1,0.7},
    //   								 vec2{0.0,0.8},
    //   								 vec2{0.1,0.99}};									 
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
		curve[i] = normalise(v); //for sphere

	}

}


void loadSurfaceOfRevolution(int y_max, int theta_max) 
{

	int size, tex_size;
	/*------------------------------CREATE GEOMETRY-------------------------------*/
	std::vector<vec2> curve(y_max);
	std::vector<vec3> surface(y_max * theta_max);
	loadQuinticBezierBaseCurve(curve, 0, 1, 0, 1, y_max);
	float theta;
	for (int i = 0; i < curve.size(); ++i)
	{
  		for (int j = 0; j < theta_max; ++j)
		{
    		theta = (float)j / float(theta_max - 1) * 360;

    		float x = curve[i].v[0] * std::cos(theta * ONE_DEG_IN_RAD);
    		float y = curve[i].v[1];
    		float z = curve[i].v[0] * std::sin(theta * ONE_DEG_IN_RAD);

    		surface[i * theta_max + j] = vec3{x, y, z};
  		}
	}


	std::vector<Quad> quads(y_max*theta_max);
	int count = 0;
	for(int i = 0; i < y_max; i++)//row
	{
		for(int j = 0; j < theta_max; j++)//col
		{
			if(i != y_max-1 && j != theta_max-1)
			{
				Quad q; 
				q.v[0] = surface[((j+(i*theta_max)))];
				q.v[1] = surface[(((j+1)+(i*theta_max)))];
				q.v[2] = surface[(((j+1)+((i+1)*theta_max)))];
				q.v[3] = surface[(((j)+((i+1)*theta_max)))];
				quads[i*theta_max + j] = q;
				count++;
			}
		}
	}
	size = (y_max*theta_max*2)*9;
	tex_size = (y_max*theta_max*2)*6;
	std::vector<Triangle> tris(y_max*theta_max*2);
	int index = 0;
	for(int i = 0; i < quads.size(); i++)
	{
		Triangle t;
		t.v[0] = quads[i].v[0];
		t.v[1]= quads[i].v[1];
		t.v[2]= quads[i].v[3];
		tris[index] = t;
		index++;
		Triangle t2;
		t2.v[0] = quads[i].v[3];
		t2.v[1]= quads[i].v[1];
		t2.v[2]= quads[i].v[2];
		tris[index] = t2;
		index++;

	}
	GLfloat* vp = new GLfloat[tris.size()*9];    // array of vertex points
	for(int i = 0; i < tris.size(); i++)
	{
		//verts
		vp[(i*9)  ] = tris[i].v[0].v[0];
		vp[(i*9)+1] = tris[i].v[0].v[1];
		vp[(i*9)+2] = tris[i].v[0].v[2];

		//verts
		vp[(i*9)+3] = tris[i].v[1].v[0];
		vp[(i*9)+4] = tris[i].v[1].v[1];
		vp[(i*9)+5] = tris[i].v[1].v[2];

		//verts
		vp[(i*9)+6] = tris[i].v[2].v[0];
		vp[(i*9)+7] = tris[i].v[2].v[1];
		vp[(i*9)+8] = tris[i].v[2].v[2];

	}
	std::vector<vec3> tri_normals(y_max*theta_max*2);
	calculateTriangleNormal(tri_normals, tris);
	GLfloat* vn = new GLfloat[tris.size()*9]; // array of vertex normals
	for(int i = 0; i < tri_normals.size(); i++)
	{
		//norms
		vn[(i*9)  ] = tri_normals[i].v[0];
		vn[(i*9)+1] = tri_normals[i].v[1];
		vn[(i*9)+2] = tri_normals[i].v[2];
		//std::cout << tri_normals[i].v[2] << '\n';
		//norms
		vn[(i*9)+3] = tri_normals[i].v[0];
		vn[(i*9)+4] = tri_normals[i].v[1];
		vn[(i*9)+5] = tri_normals[i].v[2];

		//norms
		vn[(i*9)+6] = tri_normals[i].v[0];
		vn[(i*9)+7] = tri_normals[i].v[1];
		vn[(i*9)+8] = tri_normals[i].v[2];

	}
	std::vector<vec2> tex_coords(tris.size()*3);
	calculateTextureCoords(tex_coords, tris);
	GLfloat* vt = new GLfloat[tex_coords.size()*2]; //array of vertex tex
	for(int i = 0; i < tex_coords.size(); i++)
	{
		vt[(i*2)] = tex_coords[i].v[0];
		vt[(i*2)+1] = tex_coords[i].v[1];

	}
	
	// VAO -- vertex attribute objects bundle the various things associated with vertices
	GLuint vao;
	glGenVertexArrays (1, &vao);   // generating and binding is common pattern in OpenGL
	glBindVertexArray (vao);       // basically setting up memory and associating it

	// VBO -- vertex buffer object to contain coordinates
	// MODIFY THE FOLLOWING BLOCK OF CODE APPRORIATELY FOR YOUR SURFACE OF REVOLUTION
	GLuint points_vbo;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof (GLfloat), vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// VBO -- normals -- needed for shading calcuations
	// ADD CODE TO POPULATE AND LOAD PER-VERTEX SURFACE NORMALS  
	// [HINT] Vertex normals are organized in same order as that for vertex coordinates
	GLuint normals_vbo;
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof (GLfloat), vn, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
    // VBO -- vt -- texture coordinates
	// ADD CODE TO POPULATE AND LOAD PER-VERTEX TEXTURE COORDINATES  
	// [HINT] texture coordinates are organized in same order as that for vertex coordinates
	// [HINT] there are two texture coordinates instead of three vertex coordinates for each vertex
	GLuint texs_vbo;
	glGenBuffers(1, &texs_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texs_vbo);
	glBufferData(GL_ARRAY_BUFFER, tex_size * sizeof(GLfloat), vt, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0 , NULL);
	glEnableVertexAttribArray(2);
	delete []vp;
	delete []vn;
	delete []vt;
}


	
void loadUniforms(GLuint shader_programme)
{	
/*---------------------------SET RENDERING DEFAULTS---------------------------*/

	// Choose vertex and fragment shaders to use as well as view and proj matrices.
	int model_mat_location = glGetUniformLocation (shader_programme, "model_mat");
	int view_mat_location  = glGetUniformLocation (shader_programme, "view_mat");
	int proj_mat_location  = glGetUniformLocation (shader_programme, "proj_mat");

	int cam_pos_location = glGetUniformLocation(shader_programme, "cam_pos");
	int light_pos_location = glGetUniformLocation(shader_programme, "light_pos");
	int light_color_location = glGetUniformLocation(shader_programme, "light_color");
	int object_color_location = glGetUniformLocation(shader_programme, "object_color");

	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat.m);
	glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
	glUniform3fv (cam_pos_location, 1, cam_pos.v);
	glUniform3fv (light_pos_location, 1, light_pos.v);
	glUniform3fv (light_color_location, 1, light_color.v);
	glUniform3fv (object_color_location, 1, object_color.v);

	// WRITE CODE TO LOAD OTHER UNIFORM VARIABLES LIKE FLAGS FOR ENABLING OR DISABLING CERTAIN FUNCTIONALITIES
}

void drawSurfaceOfRevolution(int y_max, int theta_max)
{
	// MODIFY THIS LINE OF CODE APPRORIATELY FOR YOUR SURFACE OF REVOLUTION
	glDrawArrays(GL_TRIANGLES, 0, (y_max * theta_max*2)*3); //#of verts =tris* 3 verts

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
