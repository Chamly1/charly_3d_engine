#version 330

uniform vec3 uColor;
uniform vec3 uLightColor;
//uniform float uLightStrength;
uniform vec3 uLightPosition;

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 color;

void main() {
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(uLightPosition - FragmentPosition);

    float diff = max(dot(normal, lightDirection), 0.f);
    vec3 diffuse = diff * uLightColor;

    color = vec4(diffuse * uColor, 1.f);
}