#pragma once

#include <GL/glew.h>
//#include <GL/SOIL.h>
#include <GL/FreeImage.h>
#include <string>
#include "Utils.h"


//static std::string a_sAllowedExt[] = { "bmp", "png", "jpg", "tga", "dds", "psd", "hdr" };

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

enum ETextureWrapping
{
	TEXTURE_WRAPPING_CLAMP_EDGE = 0,
	TEXTURE_WRAPPING_CLAMP_BORDER,
	TEXTURE_WRAPPING_REPEAT,
};

class Texture
{
public:
	Texture();
	Texture( std::string sPath );
	~Texture();

	void bindTexture( int iTextureUnit = 0 );
	void createFromData( BYTE* p_bData, int iWidth, int iHeight, GLenum format, bool bGenMipMaps );
	BYTE* getData();
	bool isLoaded();
	bool loadTexture( std::string sPath, bool bGenMipmaps = false );
	bool loadTexture( char* p_cPath, bool bGenMipmaps = false );
	void loadFile( std::string sPath );
	void releaseTexture();
	void setFiltering( int iMinification, int iMagnification );
	void setWrapping( int iSWrapping, int iTWrapping );

	/*static bool isValidFile( char* p_cPath );
	static bool isValidFile( std::string sPath );*/

private:
	int _iWidth, _iHeight, _iChannels;
	bool _bMipmapsGenerated, _bIsLoaded;
	std::string _sPath;
	GLuint _uiTexture;
	BYTE* _pData;
	GLenum _eFormat;
};

