#version 330

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;

uniform sampler2D tex_diffuse;

in vec3 f_normal;
in vec2 f_texcoord;

out vec4 p_color;

void main() {
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec3 light_dir = normalize(vec3(0.2f, 0.75f, 0.0f));
    float light_factor = max(dot(f_normal, light_dir), 0.0f);
    
    // ambient y emissive
    color += mat_ambient + mat_emissive;

    if (light_factor > 0.0) {
        // diffuse
        // color += (mat_diffuse*0.5f + texture(tex_diffuse, f_texcoord)*0.5f) * light_factor;
        // color += mat_diffuse * texture(tex_diffuse, f_texcoord) * light_factor;
        color += texture(tex_diffuse, f_texcoord) * mat_diffuse * light_factor;
        
        // specular
        vec3 light_dir_half = normalize(light_dir + vec3(0.0f, 0.0f, 1.0f));
        float light_factor_specular = max(dot(f_normal, light_dir_half), 0.0f);
        
        color += mat_specular * pow(light_factor_specular, mat_shininess);
    }
    
    p_color = color;
}
