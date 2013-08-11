#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Camera.h"
#include "Texture.h"
#include "ShaderManager.h"

class Skybox
{
public:
	Skybox(void);
	~Skybox(void);

	void loadSkybox();
	void render( Camera* cam );

	GLuint _uiVAO;

private:
	Texture _Textures[6];

	//GLuint _uiVAO;
	GLuint _uiVBO;

	ShaderProgram* _skyboxShader;
};

