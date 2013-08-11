#include "Terrain.h"

Terrain::Terrain()
{
	/*_terrain.resize( MAP_X );
	for( int i = 0; i < MAP_X; i++ )
	{
		_terrain[i].resize( MAP_Z );

		for( int j = 0; j < MAP_Z; j++ )
			_terrain[i][j].resize(3);
	}

	
	_normals.resize( MAP_X );
	for( int i = 0; i < MAP_X; i++ )
	{
		_normals[i].resize( MAP_Z );

		for( int j = 0; j < MAP_Z; j++ )
			_normals[i][j].resize(3);
	}*/
}

void Terrain::loadHeightMap( std::string sPath )
{
	int width, height, channels;
	unsigned char* image = SOIL_load_image( Utils::contentPath( sPath ).c_str(), &width, &height, &channels, SOIL_LOAD_RGB );

	_terrain = (float*) malloc( sizeof( float ) * MAP_Z * MAP_X * 3 );
	_normals = (float*) malloc( sizeof( float ) * MAP_Z * MAP_X * 3 );

	if( image == NULL )
	{
		printf( "ERROR! HeightMap file could not be loaded. (Did you make sure the path is correct?)\n" );
		return;
	}
	
	for( int z = 0; z < MAP_Z; z++ )
    {
		for( int x = 0; x < MAP_X; x++ )
		{
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 0 ] = float( x ) * MAP_SCALE;
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 1 ] = (float) image[ ( z * MAP_Z + x ) * 3 ];
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] = -float( z ) * MAP_SCALE;
		}
    }
	SOIL_free_image_data( image );

	_initialize();
}

/*void Terrain::loadHeightMap( std::string sPath )
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	
	fif = FreeImage_GetFileType( Utils::contentPath( sPath ).c_str(), 0 );

	if( fif == FIF_UNKNOWN )
		fif = FreeImage_GetFIFFromFilename( Utils::contentPath( sPath ).c_str() );

	if( fif == FIF_UNKNOWN )
	{
		printf( "ERROR! Failed to figure out the filetype of height map." );
		return;
	}

	if( FreeImage_FIFSupportsReading( fif ) )
		dib = FreeImage_Load( fif, Utils::contentPath( sPath ).c_str() );
	else
	{
		printf( "ERROR! Failed to load height map." );
		return;
	}

	BYTE* bDataPointer = FreeImage_GetBits(dib);

	

	int test = FreeImage_GetWidth( dib ) ;
	int test2 = FreeImage_GetHeight( dib ) ;

	

	_terrain = (float*) malloc( sizeof( float ) * MAP_Z * MAP_X * 3 );
	_normals = (float*) malloc( sizeof( float ) * MAP_Z * MAP_X * 3 );

	for( int z = 0; z < MAP_Z; z++ )
    {
		for( int x = 0; x < MAP_X; x++ )
		{
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 0 ] = float( x ) * MAP_SCALE;
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 1 ] = (float) bDataPointer[ ( z * MAP_Z + x ) * 3 ];
			_terrain[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] = -float( z ) * MAP_SCALE;
		}
    }

	//FreeImage_Unload( dib );

	_initialize();
}*/



void Terrain::_initialize()
{
	glGenVertexArrays( 1, &_uiVAO );
	glBindVertexArray( _uiVAO );

	GLuint vbo;
	glGenBuffers( 1, &vbo );

	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	
	

	//Generate normals
	for (int z = 1; z < MAP_Z-1; z++)
	{
		for (int x = 1; x < MAP_X-1; x++)
		{
			glm::vec3 A = glm::vec3( _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 0 ], _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 1 ], _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] );
			glm::vec3 B = glm::vec3( _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 0 ], _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 1 ], _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 2 ] );
			glm::vec3 C = glm::vec3( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 0 ], _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 1 ], _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 2 ] );
			glm::vec3 D = glm::vec3( _terrain[ ( z * 3 * MAP_Z + ( x * 3 - 1 * 3 ) ) + 0 ], _terrain[ ( z * 3 * MAP_Z + ( x * 3 - 1 * 3 ) ) + 1 ], _terrain[ ( z * 3 * MAP_Z + ( x * 3 - 1 * 3 ) ) + 2 ] );
			glm::vec3 E = glm::vec3( _terrain[ ( ( z * 3 - 1 * 3 ) * MAP_Z + x * 3 ) + 0 ], _terrain[ ( ( z * 3 - 1 * 3 ) * MAP_Z + x * 3 ) + 1 ], _terrain[ ( ( z * 3 - 1 * 3 ) * MAP_Z + x * 3 ) + 2 ] );	

			//float test = _terrain[ 0 ];

			glm::normalize( glm::cross( B - A, C - A ) );

			glm::vec3 normal =	glm::normalize(	
								glm::normalize( glm::cross( B - A, C - A ) )
								+ glm::normalize( glm::cross( C - A, D - A ) )
								+ glm::normalize( glm::cross( D - A, E - A ) )
								+ glm::normalize( glm::cross( E - A, B - A ) )
							);

			_normals[ ( z * 3 * MAP_Z + x * 3 ) + 0 ] = normal.x;
			_normals[ ( z * 3 * MAP_Z + x * 3 ) + 1 ] = normal.y;
			_normals[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] = normal.z;
		}
	}

	/*for( int z = 1; z < MAP_Z-1; z++ )
	{
		for( int x = 1; x < MAP_X-1; x++ )
		{
			glm::vec3 A = glm::vec3( _terrain[x][z][0], _terrain[x][z][1], _terrain[x][z][2] );
			glm::vec3 B = glm::vec3( _terrain[x+1][z][0], _terrain[x+1][z][1], _terrain[x+1][z][2] );
			glm::vec3 C = glm::vec3( _terrain[x][z+1][0], _terrain[x][z+1][1], _terrain[x][z+1][2] );

			glm::vec3 normal = glm::normalize( glm::cross( B - A, C - A ) );

			_normals[x][z][0] = normal.x;
			_normals[x][z][1] = normal.y;
			_normals[x][z][2] = normal.z;
		}
	}*/

	int count = 0;

	//Generate vertices
	for (int z = 0; z < MAP_Z-1; z++)
	{
		for (int x = 0; x < MAP_X-1; x++)
		{

			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 0 ] );
			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 1 ] );
			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] );
			_vertices.push_back( 0.0f );
			_vertices.push_back( 0.0f );

			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + x * 3 ) + 0 ] );
			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + x * 3 ) + 1 ] );
			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + x * 3 ) + 2 ] );
			_elements.push_back( count * 4 );
			
			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 0 ] );
			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 1 ] );
			_vertices.push_back( _terrain[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 2 ] );
			_vertices.push_back( 1.0f );
			_vertices.push_back( 0.0f );
			
			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 0 ] );
			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 1 ] );
			_vertices.push_back( _normals[ ( z * 3 * MAP_Z + ( x * 3 + 1 * 3 ) ) + 2 ] );
			_elements.push_back( count * 4 + 1 );
			
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 0 ] );
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 1 ] );
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 2 ] );
			_vertices.push_back( 0.0f );
			_vertices.push_back( 1.0f );
			
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 0 ] );
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 1 ] );
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + x * 3 ) + 2 ] );
			_elements.push_back( count * 4 + 2 );
			
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 0 ] );
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 1 ] );
			_vertices.push_back( _terrain[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 2 ] );
			_vertices.push_back( 1.0f );
			_vertices.push_back( 1.0f );
			
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 0 ] );
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 1 ] );
			_vertices.push_back( _normals[ ( ( z * 3 + 1 * 3 ) * MAP_Z + ( x * 3 + 1 * 3 ) ) + 2 ] );
			_elements.push_back( count * 4 + 1 );
			_elements.push_back( count * 4 + 2 );
			_elements.push_back( count * 4 + 3 );

			count++;
		}
	}

	glBufferData( GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices.front(), GL_STATIC_DRAW );

	GLuint ebo;
	glGenBuffers( 1, &ebo );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, _elements.size() * sizeof(int), &_elements.front(), GL_STATIC_DRAW );

	ShaderManager sm = ShaderManager::getInstance();

	_textureShader = sm.loadShader("diffusetexture");

	GLint posAttrib = glGetAttribLocation( _textureShader->getProgramID(), "Position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0 );

	GLint texAttrib = glGetAttribLocation( _textureShader->getProgramID(), "TexCoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3*sizeof(float)) );

	GLint normAttrib = glGetAttribLocation( _textureShader->getProgramID(), "Normal" );
	glEnableVertexAttribArray( normAttrib );
	glVertexAttribPointer( normAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (5 * sizeof( float ) ) );

	_grassTexture.loadTexture( "images/green.bmp", false );
	
	glBindVertexArray( 0 );
}

void Terrain::render( Camera* cam )
{
	assert( _vertices.size() != 0 );
	glBindVertexArray( _uiVAO );
	_grassTexture.bindTexture();

	_textureShader->use();

	glm::mat4 mvp = cam->getViewProjectionMatrix() * glm::mat4(1.f);
	glm::mat4 projection = cam->getProjectionMatrix();
	_textureShader->setUniform( "g_mvpMatrix", mvp );
	_textureShader->setUniform( "g_viewMatrix", projection );
	_textureShader->setUniform( "g_Sampler", 0 );
	DirectionalLight light;
	light.fAmbientIntensity = 0.1f;
	light.fDiffuseIntensity = 0.6f;
	light.v3Color = glm::vec3( 1.f, 1.f, 204.f / 255.f );
	light.v3Direction = glm::vec3( -0.652354f, -0.510654f, 0.560060f );
	_textureShader->setUniform( "g_DirectionalLight", light );

	glEnable( GL_DEPTH_TEST );

	glDrawElements( GL_TRIANGLES, _vertices.size() / 8 * 3, GL_UNSIGNED_INT, 0 );

	glDisable( GL_DEPTH_TEST );

	glBindVertexArray( NULL );
	glUseProgram( NULL );
}