#version 410

layout (location = 0) in vec3 vtxPosition;
layout (location = 1) in vec3 vtxNormal;
layout (location = 2) in vec2 tex_coord;

uniform mat4 proj_mat, view_mat, model_mat;

out vec3 frag_pos;
out vec3 normal;
out vec2 texture_coords;

void main () {

	texture_coords = tex_coord;
	frag_pos = vec3(model_mat * vec4(vtxPosition, 1.0));
	//normal = vec3(model_mat * vec4(vtxNormal, 1.0));
	normal = mat3(transpose(inverse(model_mat))) * vtxNormal;  
	gl_Position = proj_mat * view_mat * vec4(frag_pos, 1.0);

}
