#version 330 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec2 texCoords;

out vec2 Texcoords;

uniform mat4 wvpMatrix;

void main() 
{
	gl_Position = ( wvpMatrix * vec4( position, 1.0 ) ).xyww;
	Texcoords = texCoords;
}