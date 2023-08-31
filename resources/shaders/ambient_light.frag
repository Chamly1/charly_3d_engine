#version 330

uniform vec3 uColor;
uniform vec3 uLightColor;
uniform float uLightStrength;

out vec4 color;

void main() {
    color = vec4((uLightStrength * uLightColor) * uColor, 1.f);
}