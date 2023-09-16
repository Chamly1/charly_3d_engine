#version 330

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 texturePos;

out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertexPos.x, vertexPos.y, 0.0, 1.0);
    TexCoords = texturePos;
}
