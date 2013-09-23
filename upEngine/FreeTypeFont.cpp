#include "FreeTypeFont.h"


FreeTypeFont::FreeTypeFont()
{

}


FreeTypeFont::~FreeTypeFont()
{

}

void FreeTypeFont::loadFont( std::string sPath, int iSize )
{
	bool bError = FT_Init_FreeType( &_FTLib );
	//bError = FT_New_Face( FTLib, Utils::fixPath( std::string( "/content/fonts/" ) + sPath ).c_str(), 0, &FTFace );
	bError = FT_New_Face( _FTLib, std::string( "C:\\Windows\\Fonts\\arial.ttf" ).c_str(), 0, &_FTFace );
	
	if( bError )
	{
		std::printf( "ERROR! Failed to load font: %s\n", "C:\\Windows\\Fonts\\arial.ttf" );
		return;
	}

	FT_Set_Pixel_Sizes( _FTFace, iSize, iSize );
	_iPixelSize = iSize;

	glGenVertexArrays( 1, &_uiVAO );
	glBindVertexArray( _uiVAO );

	_vboData.createVBO();
	_vboData.bindVBO();

	for( int i = 0; i < 128; i++ )
	{
		createChar( i );
	}

	glGenBuffers( 1, &_uiVBO );
	glBindBuffer( GL_ARRAY_BUFFER, _uiVBO );
	_vboData.uploadDataToGPU( GL_STATIC_DRAW );

	FT_Done_Face( _FTFace );
	FT_Done_FreeType( _FTLib );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( glm::vec2 ), 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( glm::vec2 ), (void*) ( 1 * sizeof( glm::vec2 ) ) );
}

void FreeTypeFont::createChar( int iCharID )
{
	FT_Load_Glyph( _FTFace, FT_Get_Char_Index( _FTFace, iCharID ), FT_LOAD_DEFAULT );
	FT_Render_Glyph( _FTFace->glyph, FT_RENDER_MODE_NORMAL );
	FT_Bitmap* p_Bitmap = &_FTFace->glyph->bitmap;

	int iWidth = p_Bitmap->width; int iHeight = p_Bitmap->rows;
	int iNWidth = Utils::next_p2( iWidth ); int iNHeight = Utils::next_p2( iHeight );

	GLubyte* bData = new GLubyte[ iNWidth * iNHeight ];
	for( int i = 0; i < iNHeight; i++ )
	{
		for( int k = 0; k < iNWidth; k++ )
		{
			bData[ i * iNWidth + k ] = ( i >= iHeight || k >= iWidth ) ? 0 : p_Bitmap->buffer[ ( iHeight - i - 1 ) * iWidth + k ];
		}
	}

	_tCharTextures[ iCharID ].createFromData( bData, iNWidth, iNHeight, GL_DEPTH_COMPONENT, false );
	_tCharTextures[ iCharID ].setFiltering( TEXTURE_FILTER_MIN_BILINEAR, TEXTURE_FILTER_MAG_BILINEAR );
	_tCharTextures[ iCharID ].setWrapping( TEXTURE_WRAPPING_CLAMP_EDGE, TEXTURE_WRAPPING_CLAMP_EDGE );
	
	_iAdvX[ iCharID ] = _FTFace->glyph->advance.x >> 6;
	_iBearingX[ iCharID ] = _FTFace->glyph->metrics.horiBearingX >> 6;
	_iCharWidth[ iCharID ] = _FTFace->glyph->metrics.width >> 6;
	
	_iAdvY[ iCharID] = ( _FTFace->glyph->metrics.height - _FTFace->glyph->metrics.horiBearingY ) >> 6;
	_iBearingY[ iCharID] = _FTFace->glyph->metrics.horiBearingY >> 6;
	_iCharHeight[ iCharID ] = _FTFace->glyph->metrics.height >> 6;
	
	_iNewLine = glm::max( 32, int( _FTFace->glyph->metrics.height >> 6 ) );

	for( int i = 0; i < 1; i++ )
	{
		//TODO: Fix this, taking the memory address of a temporary object and storing it for later use is BAD.
		_vboData.addData( &glm::vec2( 0.f, float( -_iAdvY[ iCharID ] + iNHeight ) ), sizeof( glm::vec2 ) );
		_vboData.addData( &glm::vec2( 0.f, 1.f ), sizeof( glm::vec2 ) );

		_vboData.addData( &glm::vec2( 0.f, float( -_iAdvY[ iCharID ] ) ), sizeof( glm::vec2 ) );
		_vboData.addData( &glm::vec2( 0.f, 0.f ), sizeof( glm::vec2 ) );

		_vboData.addData( &glm::vec2( float( iNWidth ), float( -_iAdvY[ iCharID ] + iNHeight ) ), sizeof( glm::vec2 ) );
		_vboData.addData( &glm::vec2( 1.f, 1.f ), sizeof( glm::vec2 ) );

		_vboData.addData( &glm::vec2( float( iNWidth ), float( -_iAdvY[ iCharID ] ) ), sizeof( glm::vec2 ) );
		_vboData.addData( &glm::vec2( 1.f, 0.f ), sizeof( glm::vec2 ) );
	}

	delete[] bData;
}

void FreeTypeFont::print( std::string sText, int iPosX, int iPosY, int iPixelSize )
{
	glBindVertexArray( _uiVAO );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	int iCurX = iPosX; int iCurY = iPosY;
	if( iPixelSize == -1 )
		iPixelSize = _iPixelSize;
	float fScale = float( iPixelSize ) / float( _iPixelSize );
	for( int i = 0; i < sText.size(); i++ )
	{
		if( sText[i] == '\n' )
		{
			iCurX = iPosX;
			iCurY -= _iNewLine * iPixelSize / _iPixelSize;
			continue;
		}

		int iIndex = int( sText[i] );
		iCurX += _iBearingX[ iIndex ] * iPixelSize / _iPixelSize;
		iCurX += 4 * iPixelSize / _iPixelSize;
		if( sText[i] != ' ' )
		{
			_tCharTextures[ iIndex ].bindTexture();
			glm::mat4 m4ModelView = glm::translate( glm::mat4( 1.f ), glm::vec3( float( iCurX ), float( iCurY ), 0.f ) );
			m4ModelView = glm::scale( m4ModelView, glm::vec3( fScale ) );
			_progShader->setUniform( "wvMatrix", m4ModelView );

			glDrawArrays( GL_TRIANGLE_STRIP, iIndex * 4, 4 );
		}
		iCurX += ( _iAdvX[ iIndex ] - _iBearingX[ iIndex ] - ( 4 * iPixelSize / _iPixelSize ) ) * iPixelSize / _iPixelSize;
	}
	glBindVertexArray( NULL );
	glDisable( GL_BLEND );
}

void FreeTypeFont::printf( int iPosX, int iPosY, int iPixelSize, char* p_cText, ... )
{
	char cBuffer[512];
	va_list vars;
	va_start( vars, p_cText );
	vsprintf( cBuffer, p_cText, vars );
	va_end( vars );
	print( cBuffer, iPosX, iPosY, iPixelSize );
}

void FreeTypeFont::setShader( ShaderProgram* progShader )
{
	_progShader = progShader;
}