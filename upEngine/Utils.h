#pragma once

#define PI 3.14159265
typedef unsigned char BYTE;

/*#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x
#define checkErrorSimple() checkError( __FILE__":"STRINGIFY(__LINE__))*/

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Utils
{
	inline char* contentPath( char* pcString )
	{
		char buffer[260];
		getcwd( buffer, 260 );
		for( int i = 0; i < sizeof( buffer ); i++ )
		{
			if( buffer[i] == '\\' )
				buffer[i] = '/';
		}
		strcat( buffer, "/content/" );
		strcat( buffer, pcString );
		
		return buffer;
	}

	inline std::string contentPath( std::string sString )
	{
		char buffer[260];
		getcwd( buffer, 260 );
		for( int i = 0; i < sizeof( buffer ); i++ )
		{
			if( buffer[i] == '\\' )
				buffer[i] = '/';
		}
		//printf( "%s\n", buffer );
		return std::string(buffer) + "/content/" + sString;
	}

	inline char* conChar( char* pcString, char* pcBuffer )
	{
		char buffer[260];
		strcat( buffer, pcString );
		strcat( buffer, pcBuffer );

		return buffer;
	}

	inline int next_p2( int n )
	{
		int res = 1; 
		while( res < n )
			res <<= 1; 
		return res;
	}

	template <typename T,unsigned S>
	inline unsigned arraySize( const T (&v)[S] ) 
	{ 
		return S; 
	}
}

