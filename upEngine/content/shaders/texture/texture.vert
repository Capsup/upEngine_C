#version 150

in vec2 position;
in vec3 color;
in vec2 texCoords;

out vec3 Color;
out vec2 Texcoords;

void main() 
{
	gl_Position = vec4( position, 0.0, 1.0 );
	Color = color;
	Texcoords = texCoords;
}