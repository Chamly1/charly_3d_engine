#version 330

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 texturePos;

out vec2 texturePosition;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPos.x, vertexPos.y, 0.0, 1.0);
    texturePosition = texturePos;
}
