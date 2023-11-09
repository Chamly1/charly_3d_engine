#version 330

uniform vec3 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightStrength;

in vec3 v_Pos;
in vec3 v_Normal;

out vec4 color;

void main() {
    vec3 ambient = u_AmbientLightStrength * u_AmbientLightColor;

    vec3 normalizedNormal = normalize(v_Normal);
    vec3 lightDirection = normalize(u_LightPos - v_Pos);

    float diff = max(dot(normalizedNormal, lightDirection), 0.f);
    vec3 diffuse = diff * u_LightColor;

    color = vec4((ambient + diffuse) * u_Color, 1.f);
}