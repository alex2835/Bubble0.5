#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

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

uniform samplerCube u_Skybox;
uniform float u_Brightness;

void main()
{    
    FragColor = u_Brightness * texture(u_Skybox, v_TexCoords);
}