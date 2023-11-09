#version 330

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 UVPos;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

out vec2 v_UVPos;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(pos.x, pos.y, 0.0, 1.0);
    v_UVPos = UVPos;
}
