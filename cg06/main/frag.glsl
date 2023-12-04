#version 410


// Define INPUTS from fragment shader
uniform mat4 view_mat;


// These come from the VAO for texture coordinates.
//in vec2 texture_coords;

// And from the uniform outputs for the textures setup in main.cpp.
uniform sampler2D texture00;
uniform sampler2D texture01;

out vec4 fragment_color; //RGBA color
void main () {

fragment_color = vec4(1.0,0.5,0.0,1.0);
}
