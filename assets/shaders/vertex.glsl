
#version 330

uniform mat4 mvp;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;

in vec3 v_coord;
in vec3 v_normal;
in vec2 v_texcoord;

out vec3 f_normal;
out vec2 f_texcoord;

vec3 transform(mat4 m, vec3 v, float w) {
    vec4 result = mvp * vec4(v_normal, w);
    return result.xyz;
}

void main() {
    gl_Position = mvp * vec4(v_coord, 1.0f);
    f_normal = normalize((mvp * vec4(v_normal, 0.0f)).xyz);
    f_texcoord = v_texcoord;
}
