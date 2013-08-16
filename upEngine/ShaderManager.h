#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#include "Utils.h"
#include "Shader.h"



class ShaderManager
{
public:
	static ShaderManager& getInstance()
	{
		static ShaderManager instance;
		return instance;
	}
	ShaderProgram* loadShader( std::string sPath );
	void useProgram( GLuint uiProgramID );
private:
	ShaderManager();
	
	void operator=( ShaderManager const& );

	std::vector<ShaderProgram*> _vecShaders;
};

