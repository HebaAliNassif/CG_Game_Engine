#version 330 core

#ifndef OUR_LIGHT_COMMON_GLSL_INCLUDED
#define OUR_LIGHT_COMMON_GLSL_INCLUDED

float calculate_lambert(vec3 normal, vec3 light_direction){
    return max(0.0f, dot(normal, -light_direction));
}

float calculate_phong(vec3 normal, vec3 light_direction, vec3 view, float shininess){
    vec3 reflected = reflect(light_direction, normal);
    return pow(max(0.0f, dot(view, reflected)), shininess);
}

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float shininess;
};

#endif

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 world;
    vec3 view;
    vec3 normal;
} fsin;

struct DirectionalLight {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    vec3 direction;
};

uniform Material material;
uniform DirectionalLight light;

out vec4 frag_color;

void main() {
    vec3 normal = normalize(fsin.normal);
    vec3 view = normalize(fsin.view);

    vec3 diffuse = material.diffuse * light.diffuse * calculate_lambert(normal, light.direction);
    vec3 specular = material.specular * light.specular * calculate_phong(normal, light.direction, view, material.shininess);
    vec3 ambient = material.ambient * light.ambient;

    frag_color = fsin.color * vec4(diffuse + specular + ambient, 1.0f);
}
