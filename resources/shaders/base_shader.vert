#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 v_Pos;
out vec3 v_Normal;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(pos, 1.0);

    v_Pos = vec3(u_Model * vec4(pos, 1.0));
    v_Normal = normal;
}