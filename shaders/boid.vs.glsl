#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;

out vec4 color;

uniform mat4 mvp;

void main() {
	vec4 pos = vec4(in_Position, 1.0f);
	gl_Position = mvp * pos;
	
	color = in_Color;
}