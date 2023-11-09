#version 330 core

uniform sampler2D u_Texture;
uniform vec3 u_Color;

in vec2 v_UVPos;

out vec4 color;

void main()
{
    vec4 sampled = texture(u_Texture, v_UVPos);
    color = vec4(u_Color, 1.0) * sampled;
}
