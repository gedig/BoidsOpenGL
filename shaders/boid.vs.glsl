#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Colour;

out vec4 colour;

uniform mat4 mvp;

void main() {
	vec4 pos = vec4(in_Position, 1.0f);
	gl_Position = mvp * pos;
	
	colour = in_Colour;
}