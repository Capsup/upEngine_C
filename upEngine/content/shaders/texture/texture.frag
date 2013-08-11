#version 150

in vec3 Color;
in vec2 Texcoords;

out vec4 outColor;

uniform sampler2D tex;

void main() 
{
	outColor = texture2D( tex, Texcoords ) * vec4( 1.0, 1.0, 1.0, 1.0 );
};