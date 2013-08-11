#pragma once

#define PI 3.14159265
typedef unsigned char BYTE;

#include <direct.h>
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
		//printf( "%s\n", buffer );
		return buffer;
	}

	inline char* fixPath2( char* pcString )
	{
		char buffer[260];
		getcwd( buffer, 260 );
		/*for( int i = 0; i < sizeof( buffer ); i++ )
		{
			if( buffer[i] == '\\' )
				buffer[i] = '/';
		}*/
		strcat( buffer, pcString );
		//printf( "%s\n", buffer );
		return buffer;
		free( buffer );
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
}

