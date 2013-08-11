#version 150

in vec2 Texcoords;

out vec4 outColor;

uniform sampler2D tex;
uniform vec4 Color;

void main() 
{
	vec4 vTexColor = texture2D( tex, Texcoords );
	outColor = vec4( vTexColor.r, vTexColor.r, vTexColor.r, vTexColor.r ) * vec4( 1.f, 1.f, 1.f, 1.f );
};