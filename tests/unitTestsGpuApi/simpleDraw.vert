#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 vertexColor;

layout(std140, row_major) uniform cb0
{
	mat4x4 worldMatrix;
	mat4x4 viewMatrix;
	mat4x4 projMatrix;
};

void main()
{
	mat4x4 worldView = worldMatrix * viewMatrix;
	vec4 viewPos = vec4( vPosition, 1.0f );
	viewPos = viewPos * worldView;

	gl_Position = viewPos * projMatrix;
	vertexColor = vColor;
}
