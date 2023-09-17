#version 330

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 texturePos;

out vec2 out_TexturePos;

uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * vec4(vertexPos.x, vertexPos.y, 0.0, 1.0);
    out_TexturePos = texturePos;
}
