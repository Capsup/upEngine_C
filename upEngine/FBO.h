#pragma once

#include "Texture.h"

class FBO
{
public:
	FBO();
	~FBO();
	void init( const unsigned int uiWidth, const unsigned int uiHeight );
	void bind();
	Texture* getShadowmap();

private:
	Texture* _pShadowmapTexture;
	GLuint _uiFBO;
};

