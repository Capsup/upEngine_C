#version 330 core

in vec2 Texcoords;

out vec4 outColor;

uniform sampler2D tex;

void main() 
{
	outColor = texture2D( tex, Texcoords );
};