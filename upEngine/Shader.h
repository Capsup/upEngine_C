#pragma once

#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct DirectionalLight
{
	glm::vec3 v3Color;
	float fAmbientIntensity;
	float fDiffuseIntensity;
	glm::vec3 v3Direction;
};

class Shader
{
public:
	Shader();
	Shader( char* p_cPath, unsigned int uiType );

	bool loadShader( char* p_cPath, unsigned int uiType );
	bool loadShader( std::string sPath, unsigned int uiType );

	bool loadSource( const char* p_cPath, unsigned int uiType );

	bool isLoaded();
	void deleteShader();
	GLuint getShaderID();

private:
	GLuint _uiShaderID;
	unsigned int _uiShaderType;
	bool _bIsLoaded;
};

class ShaderProgram
{
public:
	ShaderProgram();

	bool attachShader( Shader* p_Shader );
	bool linkProgram();
	void deleteProgram();
	void use();
	void stopUsing();
	GLuint getProgramID();

	void setUniform( std::string sName, const glm::mat4 m4Matrix );
	void setUniform( std::string sName, const GLint iInteger );
	void setUniform( std::string sName, const DirectionalLight& Light );

	std::string sName;

private:
	GLuint _uiProgramID;
	bool _bIsLinked;
};