#version 330 core

layout( location = 0 ) in vec3 Position;
layout( location = 1 ) in vec2 TexCoord;
layout( location = 2 ) in vec3 Normal;

out vec3 WorldSpacePos0;
out vec2 TexCoord0;
out vec3 Normal0;

uniform mat4 g_wvpMatrix;
uniform mat4 g_worldMatrix;

void main() 
{
	gl_Position = g_wvpMatrix * vec4( Position, 1.0 );
	TexCoord0 = TexCoord;
	Normal0 = ( g_worldMatrix * vec4( Normal, 0.0 ) ).xyz;
	WorldSpacePos0 = ( g_worldMatrix * vec4( Position, 1.0 ) ).xyz;
}