#version 330 core

layout (location = 0) in vec4 vertex;
out vec2 texCoord;

uniform mat4 projection;

void main()
{
	vec4 coord = projection * vec4(vertex.xy, 0.0f, 1.0f);
	gl_Position = vec4(coord.x, coord.y, coord.zw);
	texCoord = vertex.zw;
}