#version 410 core

layout (location = 0) out vec4 oColor;

uniform vec3 color;

void main() {
	oColor = vec4(color, 1.0);
}