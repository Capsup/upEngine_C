#include "VBO.h"


VBO::VBO()
{

}

void VBO::createVBO( int a_iSize )
{
	glGenBuffers( 1, &_uiBuffer );
	_data.reserve( a_iSize );
}

void VBO::removeVBO()
{
	glDeleteBuffers( 1, &_uiBuffer );
	_bDataUploaded = false;
	_data.empty();
}

void VBO::bindVBO( int iBufferType )
{
	_iBufferType = iBufferType;
	if( _uiBuffer == NULL || _uiBuffer < 0 )
	{
		printf( "ERROR! Attempted to bind to invalid VBO index. (Did you forget to createVBO()?)\n" );
		return;
	}
	glBindBuffer(iBufferType, _uiBuffer);
}

void VBO::uploadDataToGPU( int iDrawingHint )
{
	glBufferData( _iBufferType, _data.size(), &_data[0], iDrawingHint );
	_bDataUploaded = true;
	_data.clear();
}

void VBO::addData( void* ptrData, unsigned int uiDataSize )
{
	_data.insert( _data.end(), (BYTE*) ptrData, (BYTE*) ptrData + uiDataSize );
}