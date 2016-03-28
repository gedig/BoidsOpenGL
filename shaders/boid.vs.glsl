#version 330 core

in vec3 in_Position;
in vec4 in_Color;

out vec4 color;

void main() {
	gl_Position = vec4(in_Position, 1.0f);
	
	color = in_Color;
}