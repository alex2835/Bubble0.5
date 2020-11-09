#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;


layout (std140, binding = 0) uniform Matrices
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

#shader fragment
#version 330 core
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