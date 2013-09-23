#include "FBO.h"


FBO::FBO()
{

}


FBO::~FBO()
{

}

void FBO::init( const unsigned int uiWidth, const unsigned int uiHeight )
{
	glGenFramebuffers( 1, &_uiFBO );

	_pShadowmapTexture = new Texture();
	_pShadowmapTexture->createFromSettings( NULL, GL_DEPTH_COMPONENT, uiWidth, uiHeight, GL_FLOAT );

	_pShadowmapTexture->setFiltering( TEXTURE_FILTER_MIN_BILINEAR, TEXTURE_FILTER_MAG_BILINEAR );
	_pShadowmapTexture->setWrapping( TEXTURE_WRAPPING_CLAMP_EDGE, TEXTURE_WRAPPING_CLAMP_EDGE );

	glBindFramebuffer( GL_FRAMEBUFFER, _uiFBO );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _pShadowmapTexture->getID(), 0 );

	glDrawBuffer( GL_NONE );
	glReadBuffer( GL_NONE );
	
	GLenum eStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );
	if( eStatus != GL_FRAMEBUFFER_COMPLETE )
	{
		printf( "ERROR! Framebuffer failed to initialize properly: %s", eStatus );
		return;
	}

}

void FBO::bind()
{
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, _uiFBO );
}

Texture* FBO::getShadowmap()
{
	return _pShadowmapTexture;
}