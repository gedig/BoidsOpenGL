#version 330 core

precision highp float;

in vec4 ex_Color;

out vec4 fragColour;

void main() {
	fragColour = ex_Color;
}