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
	Shader( const char* p_cPath, const unsigned int uiType );

	bool loadShader( const char* p_cPath, const unsigned int uiType );
	bool loadShader( const std::string sPath, const unsigned int uiType );

	bool loadSource( const char* p_cPath, const unsigned int uiType );

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

	void setUniform( const std::string sName, const glm::vec3 v3Vector );
	void setUniform( const std::string sName, const glm::vec4 v4Vector );
	void setUniform( const std::string sName, const glm::mat4 m4Matrix );
	void setUniform( const std::string sName, const GLint iInteger );
	void setUniform( const std::string sName, const GLfloat fFloat );
	void setUniform( const std::string sName, const DirectionalLight& Light );

	std::string sName;

private:
	GLuint _uiProgramID;
	bool _bIsLinked;
};