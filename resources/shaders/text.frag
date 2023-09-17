#version 330 core
in vec2 texturePosition;
out vec4 color;

uniform sampler2D u_Texture;
uniform vec3 u_TextColor;

void main()
{
    vec4 sampled = texture(u_Texture, texturePosition);
    color = vec4(u_TextColor, 1.0) * sampled;
}
