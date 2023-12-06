#version 410
out vec4 fragment_color; //RGBA color


// Define INPUTS from fragment shader
uniform mat4 view_mat;
uniform vec3 cam_pos;
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 object_color;

in vec3 frag_pos;
in vec3 normal;

// These come from the VAO for texture coordinates.
in vec2 texture_coords;

// And from the uniform outputs for the textures setup in main.cpp.
uniform sampler2D texture00;
uniform sampler2D texture01;

void main ()
{
    vec3 albedo = texture(texture00, texture_coords).rgb;
    //ambience
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * albedo;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * albedo;

    //specular blinn-phong
    float specularStrength = 4;
    vec3 view_dir = normalize(cam_pos - frag_pos);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(normal, halfway_dir), 0.0), 48);
    vec3 specular =  specularStrength * spec * albedo; 

    //normal phong
    //vec3 reflect_dir = reflect(-light_dir, norm);
    //float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 8);
    //vec3 specular =  specularStrength * spec * vec3(0.3); 

    vec3 result = (ambient + diffuse + specular) ;
    fragment_color = vec4(result, 1.0);
    //fragment_color = texture(texture00, texture_coords);
}

