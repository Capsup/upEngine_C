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
	
	/*~ShaderManager(void);
	GLuint loadShader( char* pcName ); 
	GLuint linkShader( unsigned int uiProgram );*/

	static ShaderManager& getInstance()
	{
		static ShaderManager instance;
		return instance;
	}
	ShaderProgram* loadShader( std::string sPath );
	void useProgram( GLuint uiProgramID );
private:
	//const char* loadSource( const char* pcPath );
	//std::string loadSource( std::string sPath );
	ShaderManager();
	//ShaderManager( ShaderManager const& );
	void operator=( ShaderManager const& );

	std::vector<ShaderProgram*> _vecShaders;
};

