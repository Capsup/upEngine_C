#version 150

//layout (location = 0) in vec2 position;
in vec2 position;
//layout (location = 1) in vec2 texCoords;
in vec2 texCoords;

out vec2 Texcoords;

uniform mat4 wvMatrix;
uniform mat4 pMatrix;

void main() 
{
	gl_Position = pMatrix * wvMatrix * vec4( position, 0.0, 1.0 );
	Texcoords = texCoords;
}