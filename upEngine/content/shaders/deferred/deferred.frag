#version 330 core

in vec3 WorldSpacePos0;
in vec2 TexCoord0;
in vec3 Normal0;

out vec3 WorldSpacePos;
out vec3 Diffuse;
out vec3 Normal;
out vec3 TexCoord;

uniform sampler2D g_Sampler;

void main() 
{
	WorldSpacePos = WorldSpacePos0;
	Diffuse = texture( g_Sampler, TexCoord0 ).xyz;
	Normal = normalize( Normal0 );
	TexCoord = vec3( TexCoord0, 0.0 );
}