#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 FragmentPosition;
out vec3 Normal;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    FragmentPosition = vec3(model * vec4(pos, 1.0));
    Normal = normal;
}