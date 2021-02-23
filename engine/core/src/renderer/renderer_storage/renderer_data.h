#pragma once

float SkyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
};

//========================== Phong shader ========================== 

const char* PhongVertexShaderSource = R"shader(
    #version 420 core
    layout(location = 0) in vec3  a_Position;
    layout(location = 1) in vec3  a_Normal;
    layout(location = 2) in vec2  a_TexCoords;
    layout(location = 3) in vec3  a_Tangent;
    layout(location = 4) in vec3  a_Bitangent;
    
    out vec3 v_FragPos;
    out vec3 v_Normal;
    out vec2 v_TexCoords;
    out mat3 v_TBN;
    
    layout(std140, binding = 0) uniform Matrices
    {
        mat4 u_Projection;
        mat4 u_View;
    };
    uniform mat4 u_Model;
    uniform bool u_NormalMapping;
    
    void main()
    {
        mat3 ITModel = mat3(transpose(inverse(u_Model)));
    
        v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
        v_Normal  = normalize(ITModel * a_Normal);
        v_TexCoords = a_TexCoords;
    
        if (u_NormalMapping)
        {
            vec3 B = normalize(vec3(u_Model * vec4(a_Bitangent, 0.0)));
            vec3 N = normalize(vec3(u_Model * vec4(a_Normal,    0.0)));
            vec3 T = normalize(vec3(u_Model * vec4(a_Tangent,   0.0)));
            v_TBN  = mat3(T, B, N);
        }
    
        gl_Position = u_Projection * u_View * vec4(v_FragPos, 1.0);
    }
)shader";

const char* PhongFragmentShaderSource = R"shader(
    #version 420 core
    out vec4 FragColor;
    
    // Material
    struct Material {
        sampler2D diffuse_map;
        sampler2D specular_map;
        sampler2D normal_map;

        vec4 diffuse_color;
        float specular_coef;
        float ambient_coef;
        int shininess;
    };
    
    // Light type enum
    const int DirLight   = 0;
    const int PointLight = 1;
    const int SpotLight  = 2;
    
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
        float pad0;
        vec3 direction;
        float pad1;
        vec3 position;
        float pad2;
    };
    
    #define MAX_LIGHTS 30
    layout(std140, binding = 1) uniform Lights {
        int nLights;
        Light lights[MAX_LIGHTS];
    };
    
    layout(std140, binding = 2) uniform  ViewPos {
        vec3 u_ViewPos;
        float pad0;
    };

    // Fragment shader output
    in vec3 v_FragPos;
    in vec3 v_Normal;
    in vec2 v_TexCoords;
    in mat3 v_TBN;
    
    // Uniforms
    uniform Material material;
    uniform bool  u_NormalMapping;
    uniform float u_NormalMappingStrength;
    
    // Function prototypes
    vec4 CalcDirLight(Light light, vec3 normal, vec3 view_dir);
    vec4 CalcPointLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);
    vec4 CalcSpotLight(Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);
    
    void main()
    {
        vec4 diffuse_texel = texture(material.diffuse_map, v_TexCoords);
        if (diffuse_texel.a < 0.0001f) {
            discard;
        }
        vec4 specular_texel = texture(material.specular_map, v_TexCoords);
    
        vec3 norm;
        if (u_NormalMapping)
        {
            norm = texture(material.normal_map, v_TexCoords).rgb;
            norm = normalize(norm * 2.0f - 1.0f);
            norm = normalize(norm * vec3(u_NormalMappingStrength, u_NormalMappingStrength, 1));
            norm = normalize(v_TBN * norm);
        }
        else {
            norm = v_Normal;
        }

        vec3 view_dir = normalize(u_ViewPos - v_FragPos);
        vec4 result    = vec4(0.0f);
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
        vec4  diffuse_light_coef  = max(vec4(material.ambient_coef), vec4(diff_spec.xyz, 1.0f));
        float specular_light_coef = diff_spec.w;
    
        result += material.diffuse_color * diffuse_light_coef * diffuse_texel;
        result += material.diffuse_color *
                  diffuse_light_coef     *
                  material.specular_coef *
                  vec4(vec3(specular_light_coef * specular_texel.x), 0);
    
        result = min(result, vec4(1.0f));
        FragColor = result;
    }
    
    
    
    // Directional light
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
    
    
    // Point light 
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
    
    
    // Spot light
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
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    
        vec3 diffuse = light.color * diff * attenuation * intensity;
        spec *= attenuation * intensity;
        return light.brightness * vec4(diffuse, spec);
    }
)shader";


//========================== Skybox shader ========================== 

const char* SkyboxVertexShaderSource = R"shader(
    #version 420 core
    layout(location = 0) in vec3 a_Position;
    
    out vec3 v_TexCoords;
    
    
    layout(std140, binding = 0) uniform Matrices
    {
        mat4 u_Projection;
        mat4 u_View;
    };
    
    
    void main()
    {
        v_TexCoords = a_Position;
        vec4 pos = u_Projection * u_View * vec4(a_Position, 1.0f);
        gl_Position = pos.xyww;
    
    }
)shader";

const char* SkyboxFragmentShaderSource = R"shader(
    #version 420 core
    out vec4 FragColor;
    
    in vec3 v_TexCoords;
    
    uniform samplerCube u_Skybox0;
    uniform samplerCube u_Skybox1;
    uniform float u_Brightness;
    uniform float u_BlendFactor;
    
    void main()
    {
        vec4 texel0 = texture(u_Skybox0, v_TexCoords);
        vec4 texel1 = texture(u_Skybox1, v_TexCoords);
        vec4 result_color = mix(texel0, texel1, u_BlendFactor);
        FragColor = u_Brightness * result_color;
    }
)shader";

//========================== Skybox shader ========================== 
const char* SkysphereVertexShaderSource = R"shader(
    #version 420 core
    layout(location = 0) in vec3 a_Position;
    layout(location = 2) in vec2 a_TexCoords;
    
    layout(std140, binding = 0) uniform Matrices
    {
        mat4 u_Projection;
        mat4 u_View;
    };
    out vec2 v_TexCoords;
    
    void main()
    {
        v_TexCoords = a_TexCoords;
        vec4 pos = u_Projection * u_View * vec4(a_Position, 1.0f);
        gl_Position = pos.xyww;
    }
)shader";

const char* SkysphereFragmentShaderSource = R"shader(
    #version 420 core
    out vec4 FragColor;
    
    in vec2 v_TexCoords;
    
    uniform sampler2D u_Skysphere;
    
    void main()
    {
        FragColor = texture(u_Skysphere, v_TexCoords);
    }
)shader";

//====================== Solid color shader ====================== 

const char* SolidColorVertexShaderSource = R"shader(
    #version 420 core
    layout(location = 0) in vec3 a_Position;
    
    layout(std140, binding = 0) uniform Matrices
    {
        mat4 u_Projection;
        mat4 u_View;
    };
    uniform mat4 u_Model;

    void main()
    {
        gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
    }
)shader";

const char* SolidColorFragmentShaderSource = R"shader(
    #version 420 core
    out vec4 FragColor;
    
    uniform vec4 u_Color;
    
    void main()
    {
        FragColor = u_Color;
    }
)shader";

