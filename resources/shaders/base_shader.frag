#version 330

uniform vec3 uColor;

//in vec4 vertexColor;
out vec4 color;

void main() {
    color = vec4(uColor, 1.f);
}