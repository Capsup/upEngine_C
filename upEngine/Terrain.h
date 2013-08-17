#pragma once

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Utils.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "Camera.h"

#define MAP_X	128
#define MAP_Z	128
#define MAP_SCALE	10.f

class Terrain
{
public:
	Terrain();
	~Terrain();
	void loadHeightMap( std::string sPath );
	void render( Camera* cam );

	GLuint _uiVAO;

private:
	ShaderProgram* _textureShader;
	Texture _grassTexture;

	std::vector<float> _vertices;
	std::vector<int> _elements;
};

