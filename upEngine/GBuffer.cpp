#include "GBuffer.h"

GBuffer::GBuffer()
{

}


GBuffer::~GBuffer()
{

}

void GBuffer::init( const unsigned int uiWindowWidth, const unsigned int uiWindowHeight )
{
	glGenFramebuffers( 1, &_uiFBO );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, _uiFBO );

	glGenTextures( GBUFFER_NUM_TEXTURES, _aTextures );
	glGenTextures( 1, &_uiDepthTexture );

	for (int i = 0; i < GBUFFER_NUM_TEXTURES; i++)
	{
		glBindTexture( GL_TEXTURE_2D, _aTextures[ i ] );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F, uiWindowWidth, uiWindowHeight, 0, GL_RGB, GL_FLOAT, NULL );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _aTextures[ i ], 0 );
	}

	glBindTexture( GL_TEXTURE_2D, _uiDepthTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, uiWindowWidth, uiWindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _uiDepthTexture, 0 );

	GLenum eDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers( Utils::arraySize( eDrawBuffers ), eDrawBuffers );

	GLenum eStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

	if( eStatus != GL_FRAMEBUFFER_COMPLETE )
		printf( "ERROR! Failed to initialise GBuffer correctly: %s", eStatus );

	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, NULL );
}

void GBuffer::bindForReading()
{
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

	for( int i = 0; i < Utils::arraySize( _aTextures ); i++ )
	{
		glActiveTexture( GL_TEXTURE0 + i );
		glBindTexture( GL_TEXTURE_2D, _aTextures[ GBUFFER_TEXTURE_TYPE_POSITION + i ] );
	}
}

void GBuffer::bindForWriting()
{
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, _uiFBO );
}

void GBuffer::setReadBuffer( GBUFFER_TEXTURE_TYPE TextureType )
{
	glReadBuffer( GL_COLOR_ATTACHMENT0 + TextureType );
}