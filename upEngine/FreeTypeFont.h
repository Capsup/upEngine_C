#pragma once

#include <string>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "Utils.h"
#include <GL/glew.h>
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"
#include "VBO.h"

class FreeTypeFont
{

public:
	FreeTypeFont();
	~FreeTypeFont();
	
	void loadFont( std::string sPath, int iSize );
	void print( std::string sText, int iPosX, int iPosY, int iPixelSize = -1 );
	void printf( int iPosX, int iPosY, int iPixelSize, char* p_cText, ... );
	void setShader( ShaderProgram* progShader );

private:
	void createChar( int iCharID );
	//void createChar2( int iCharID );

	FT_Library _FTLib;
	FT_Face _FTFace;
	GLuint _uiVAO;
	GLuint _uiVBO;
	Texture _tCharTextures[256];
	int _iAdvX[256], _iAdvY[256];
	int _iBearingX[256], _iBearingY[256];
	int _iCharWidth[256], _iCharHeight[256];
	int _iNewLine, _iPixelSize;
	std::vector<float> _fData;

	ShaderProgram* _progShader;

	VBO _vboData;
};

