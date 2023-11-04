#version 330 core
in vec2 texturePosition;
out vec4 color;

uniform sampler2D u_Texture;
uniform vec3 uColor;

void main()
{
    vec4 sampled = texture(u_Texture, texturePosition);
    color = vec4(uColor, 1.0) * sampled;
}
