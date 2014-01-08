#pragma once

#include <GL/glew.h>
#include "Utils.h"

class GBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE
	{
		GBUFFER_TEXTURE_TYPE_POSITION = 0,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_NUM_TEXTURES
	};

	GBuffer();
	~GBuffer();

	void init( const unsigned int uiWindowWidth, const unsigned int uiWindowHeight );
	void bindForReading();
	void bindForWriting();
	void setReadBuffer( GBUFFER_TEXTURE_TYPE TextureType );

private:
	GLuint _uiFBO;
	GLuint _aTextures[GBUFFER_NUM_TEXTURES];
	GLuint _uiDepthTexture;
};

