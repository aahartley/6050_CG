#version 410
out vec4 fragment_color; //RGBA color


// Define INPUTS from fragment shader
uniform mat4 view_mat;
uniform vec3 cam_pos;
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 object_color;
uniform int specular_exp;
uniform bool diffuseB;
uniform bool specularB;
uniform bool albedoB;

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
    vec3 ambient;
    if(albedoB)
        ambient = ambient_strength * albedo;
    else
        ambient = ambient_strength * light_color;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse;
    if(albedoB) 
        diffuse = diff * albedo;
    else
        diffuse = diff * light_color;
    if(!diffuseB) diffuse = vec3(0);

    //specular blinn-phong
    float specularStrength = 2;
    vec3 view_dir = normalize(cam_pos - frag_pos);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(normal, halfway_dir), 0.0), specular_exp);
    vec3 specular =  specularStrength * spec * light_color; 
    if(!specularB) specular = vec3(0);

    //normal phong
    //vec3 reflect_dir = reflect(-light_dir, norm);
    //float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 8);
    //vec3 specular =  specularStrength * spec * light_color; 

    vec3 result;
    if(albedoB)
        result = (ambient + diffuse + specular) ;
    else
        result = (ambient + diffuse + specular) * object_color;
    fragment_color = vec4(result, 1.0);
    //fragment_color = texture(texture00, texture_coords);
}

