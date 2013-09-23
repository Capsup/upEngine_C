#version 150

in vec3 Color;
in vec2 Texcoords;

out vec4 outColor;

uniform sampler2D tex;
uniform float time;

void main() 
{
	outColor = texture2D( tex, vec2( Texcoords.x , Texcoords.y + sin( Texcoords.x * 60.0 + time * 2.0 ) / 30.0 ) ) * vec4( 0.7, 0.7, 1.0, 1.0 );
};