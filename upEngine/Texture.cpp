#include "Texture.h"


Texture::Texture()
{
	_bIsLoaded = false;
}

Texture::Texture( std::string sPath )
{
	_bIsLoaded = false;
	loadTexture( sPath );
}


Texture::~Texture()
{
	releaseTexture();
}

void Texture::createFromData( BYTE* p_bData, int iWidth, int iHeight, GLenum format, bool bGenMipmaps )
{
	glGenTextures( 1, &_uiTexture );
	glBindTexture( GL_TEXTURE_2D, _uiTexture );

	if( format == GL_RGBA || format == GL_BGRA )
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, p_bData );
	else if( format == GL_RGB || format == GL_BGR )
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, p_bData );
	else
		glTexImage2D( GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, p_bData );

	//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, p_bData );
	if( bGenMipmaps )
		glGenerateMipmap( GL_TEXTURE_2D );

	/*_iWidth = iWidth;
	_iHeight = iHeight;*/
	_bMipmapsGenerated = bGenMipmaps;
}

BYTE* Texture::getData()
{
	if( _pData == NULL )
		return NULL;

	return _pData;
}

void Texture::loadFile( std::string sPath )
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	
	fif = FreeImage_GetFileType( Utils::contentPath( sPath ).c_str(), 0 );

	if( fif == FIF_UNKNOWN )
		fif = FreeImage_GetFIFFromFilename( Utils::contentPath( sPath ).c_str() );

	if( fif == FIF_UNKNOWN )
	{
		printf( "ERROR! Failed to figure out filetype of file: '%s' \n", sPath );
		return;
	}

	if( FreeImage_FIFSupportsReading( fif ) )
		dib = FreeImage_Load( fif, Utils::contentPath( sPath ).c_str() );
	else
	{
		printf( "ERROR! Failed to load image file: '%s' \n", sPath );
		return;
	}

	_pData = FreeImage_GetBits(dib);
	

	_iWidth = FreeImage_GetWidth(dib);
	_iHeight = FreeImage_GetHeight(dib);
	//_pData = new BYTE[ _iWidth * _iHeight ];
	//std::copy( FreeImage_GetBits(dib), FreeImage_GetBits(dib) + _iWidth * _iHeight, _pData );

	//BYTE* test = FreeImage_GetBits(dib);

	if( _pData == NULL || _iWidth == 0 || _iHeight == 0 )
	{
		printf( "ERROR! Failed to load image file: '%s' \n", sPath );
		return;
	}

	int iBitsPerPixel = FreeImage_GetBPP(dib);
	
	if( iBitsPerPixel == 32 )
		_eFormat = GL_BGRA;
	if( iBitsPerPixel == 24 )
		_eFormat = GL_BGR;
	if( iBitsPerPixel == 8 )
		_eFormat = GL_LUMINANCE;

	//FreeImage_Unload( dib );
}

bool Texture::loadTexture( std::string sPath, bool bGenMipmaps )
{
	/*if( !isValidFile( sPath ) )
		return false;*/
	
	//BYTE* p_bData = SOIL_load_image( Utils::contentPath( sPath ).c_str(), &_iWidth, &_iHeight, &_iChannels, SOIL_LOAD_RGB );
	loadFile( sPath );

	createFromData( _pData, _iWidth, _iHeight, _eFormat, bGenMipmaps );

	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	if( bGenMipmaps )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	else
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glBindTexture( GL_TEXTURE_2D, NULL );
	//SOIL_free_image_data( p_bData );
	

	_sPath = sPath;

	_bIsLoaded = true;
	return true;
}

bool Texture::loadTexture( char* p_cPath, bool bGenMipmaps )
{
	return( loadTexture( std::string( p_cPath ), bGenMipmaps ) );
}

/*bool Texture::isValidFile( char* p_cPath )
{
	std::string sPath = std::string( p_cPath );

	std::string sExt = sPath.substr( sPath.find_last_of( "." ) + 1, sPath.length() );

	for( int i = 0; i <= sizeof( a_sAllowedExt ); i++ )
	{
		if( sExt == a_sAllowedExt[i] )
			return true;
	}

	return false;
}

bool Texture::isValidFile( std::string sPath )
{
	std::string sExt = sPath.substr( sPath.find_last_of( "." ) + 1, sPath.length() );

	for( int i = 0; i < sizeof( a_sAllowedExt ); i++ )
	{
		if( sExt == a_sAllowedExt[i] )
			return true;
	}

	return false;
}*/

void Texture::bindTexture( int iTextureUnit )
{
	glActiveTexture( GL_TEXTURE0 + iTextureUnit );
	glBindTexture( GL_TEXTURE_2D, _uiTexture );
}

void Texture::releaseTexture()
{
	glBindTexture( GL_TEXTURE_2D, NULL );
	glDeleteTextures( 1, &_uiTexture );
}

void Texture::setFiltering( int iMinification, int iMagnification )
{
	glBindTexture( GL_TEXTURE_2D, _uiTexture );
	if( iMinification == TEXTURE_FILTER_MIN_BILINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	if( iMagnification == TEXTURE_FILTER_MAG_BILINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture( GL_TEXTURE_2D, NULL );
}

void Texture::setWrapping( int iSWrapping, int iTWrapping )
{
	glBindTexture( GL_TEXTURE_2D, _uiTexture );
	if( iSWrapping == TEXTURE_WRAPPING_CLAMP_EDGE )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	else if( iSWrapping == TEXTURE_WRAPPING_CLAMP_BORDER )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	else if( iSWrapping == TEXTURE_WRAPPING_REPEAT )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );

	if( iTWrapping == TEXTURE_WRAPPING_CLAMP_EDGE )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	else if( iTWrapping == TEXTURE_WRAPPING_CLAMP_BORDER )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	else if( iTWrapping == TEXTURE_WRAPPING_REPEAT )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glBindTexture( GL_TEXTURE_2D, NULL );
}

bool Texture::isLoaded()
{
	return _bIsLoaded;
}