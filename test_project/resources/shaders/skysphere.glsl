#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 2) in vec2 a_TexCoords;

layout (std140, binding = 0) uniform Matrices
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

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Skysphere;

void main()
{    
    FragColor = texture(u_Skysphere, v_TexCoords);
}