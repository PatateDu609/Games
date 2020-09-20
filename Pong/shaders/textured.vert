#version 330 core

layout (location = 0) in vec3 coord;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(coord, 1.0f);
	texCoord = inTexCoord;
}