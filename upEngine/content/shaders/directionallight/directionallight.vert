#version 330 core

layout( location = 0 ) in vec3 Position;

uniform mat4 g_wvpMatrix;

void main() 
{
	gl_Position = g_wvpMatrix * vec4( Position, 1.0 );;
}