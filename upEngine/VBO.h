#pragma once

#include <GL/glew.h>
#include <vector>
#include "Utils.h"

class VBO
{
public:
	VBO();

	void createVBO( int a_iSize = 0 );
	void removeVBO();

	void bindVBO( int a_iBufferType = GL_ARRAY_BUFFER );
	void uploadDataToGPU( int iUsageHint );
	
	void addData( void* ptrData, unsigned int uiDataSize );

private:
	std::vector<BYTE> _data;
	int _iBufferType;
	unsigned int _uiBuffer;
	bool _bDataUploaded;
};

