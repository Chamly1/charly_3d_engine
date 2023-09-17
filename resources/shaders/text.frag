#version 330 core
in vec2 in_TexturePos;
out vec4 out_Color;

uniform sampler2D u_Texture;
uniform vec3 u_TextColor;

void main()
{
    vec4 sampled = texture(u_Texture, in_TexturePos);
    out_Color = vec4(u_TextColor, 1.0) * sampled;
}
