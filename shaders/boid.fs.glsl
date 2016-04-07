#version 330 core

precision highp float;

in vec4 colour;

out vec4 fragColour;

void main() {
	fragColour = colour;
}