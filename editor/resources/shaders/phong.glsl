// Vertex shader
#shader vertex
#version 420 core
layout(location = 0) in vec3  a_Pos;
layout(location = 1) in vec3  a_Normal;
layout(location = 2) in vec2  a_TexCoords;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TexCoords;


layout (std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
};
uniform mat4 u_Model;


void main()
{
    v_FragPos = vec3(u_Model * vec4(a_Pos, 1.0));
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_TexCoords = a_TexCoords;
    gl_Position = u_Projection * u_View * vec4(v_FragPos, 1.0);
}

// Fragment shader
#shader fragment
#version 420 core
out vec4 FragColor;

// Material
struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
    sampler2D normal0;
    int shininess;
};

// Light type enum
const int DirLight = 0;
const int PointLight = 1;
const int SpotLight = 2;

// Light
struct Light
{
    int type;
    float brightness;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    vec3 color;
    float __pad0;
    vec3 direction;
    float __pad1;
    vec3 position;
    float __pad2;
};

// Uniforms
uniform Material material;

#define MAX_LIGHTS 30
layout (std140, binding = 1) uniform Lights {
  int nLights;
  Light lights[MAX_LIGHTS];
};


layout (std140, binding = 2) uniform  Stuff {
    vec3 view_pos;
    float __pad0;
};

// Vertex shader output
in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TexCoords;


// Function prototypes
vec4 CalcDirLight(Light light, vec3 normal, vec3 view_dir);
vec4 CalcPointLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec4 CalcSpotLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main()
{
    vec4 diffuse = texture(material.diffuse0, v_TexCoords);
    if (diffuse.a < 0.0001f){
        discard;
    }
    vec4 specular = texture(material.specular0, v_TexCoords);
    
    vec3 norm = normalize(v_Normal);
    vec3 view_dir = normalize(view_pos - v_FragPos);

    vec4 result = vec4(0.0f);
    vec4 diff_spec = vec4(0.0f);

    for (int i = 0; i < nLights; i++)
    {
        switch (lights[i].type)
        {
            case DirLight:
                diff_spec += CalcDirLight(lights[i], norm, view_dir);
                break;

            case PointLight:
                diff_spec += CalcPointLight(lights[i], norm, v_FragPos, view_dir);
                break;

            case SpotLight:
                diff_spec += CalcSpotLight(lights[i], norm, v_FragPos, view_dir);
                break;
        }
    }
    // Hard code ambient
    float ambient = 0.05f;
    vec4  diffuse_coef = max(vec4(ambient), vec4(diff_spec.xyz, 1.0f));
    float specular_coef = diff_spec.w;

    result += diffuse_coef * diffuse;
    result += vec4(vec3(specular_coef * specular.x), 0);
    
    result = min(result, vec4(1.0f));
    FragColor = result;
}



// calculates the color when using a directional light.
vec4 CalcDirLight(Light light, vec3 normal, vec3 view_dir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + view_dir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
    vec3 diffuse = light.color * diff;
    return light.brightness * vec4(diffuse, spec);
}


// calculates the color when using a point light.
vec4 CalcPointLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 lightDir = normalize(light.position - frag_pos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + view_dir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = light.color * diff * attenuation;
    spec *= attenuation;
    return light.brightness * vec4(diffuse, spec);
}


// calculates the color when using a spot light.
vec4 CalcSpotLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 lightDir = normalize(light.position - frag_pos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 halfwayDir = normalize(-light.direction + view_dir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    vec3 diffuse = light.color * diff * attenuation * intensity;
    spec *= attenuation * intensity;
    return light.brightness * vec4(diffuse, spec);
}