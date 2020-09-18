#version 330 core

layout (location = 0) in vec3 coord;
layout (location = 1) in vec3 color;

out vec3 col;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * model * vec4(coord, 1.0f);
	col = color;
}