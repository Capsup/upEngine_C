#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{
	
}

void Terrain::loadHeightMap( std::string sPath )
{
	/*int width, height, channels;
	BYTE* bDataPointer = SOIL_load_image( Utils::contentPath( sPath ).c_str(), &width, &height, &channels, SOIL_LOAD_RGB );*/

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	
	fif = FreeImage_GetFileType( Utils::contentPath( sPath ).c_str(), 0 );

	if( fif == FIF_UNKNOWN )
		fif = FreeImage_GetFIFFromFilename( Utils::contentPath( sPath ).c_str() );

	if( fif == FIF_UNKNOWN )
	{
		printf( "ERROR! Failed to figure out the filetype of height map.\n" );
		return;
	}

	if( FreeImage_FIFSupportsReading( fif ) )
		dib = FreeImage_Load( fif, Utils::contentPath( sPath ).c_str() );
	else
	{
		printf( "ERROR! Failed to load height map.\n" );
		return;
	}

	BYTE* bDataPointer = FreeImage_GetBits(dib);

	if( bDataPointer == NULL )
	{
		printf( "ERROR! HeightMap file could not be loaded. (Did you make sure the path is correct?)\n" );
		return;
	}

	int width = FreeImage_GetWidth( dib ), height = FreeImage_GetHeight( dib );

	//Create terrain data
	float* p_fData = new float[ width * height * 3 ];
	for( int z = 0; z < height; z++ )
	{
		for( int x = 0; x < width; x++ )
		{
			p_fData[ z * 3 * height + ( x * 3 ) + 0 ] = float( x ) * MAP_SCALE;
			//Soil for some reason needs to have a * 3 here:
			//p_fData[ z * 3 * height + ( x * 3 ) + 1 ] = float( bDataPointer[ ( z * height + x ) * 3 ] );
			p_fData[ z * 3 * height + ( x * 3 ) + 1 ] = float( bDataPointer[ ( z * height + x ) ] );
			p_fData[ z * 3 * height + ( x * 3 ) + 2 ] = -float( z ) * MAP_SCALE;
		}
	}

	//FreeImage_Unload( dib );

	//Create normals for all vertices
	float* p_fNormals = new float[ width * height * 3 ];
	for( int z = 0; z < height; z++ )
	{
		for( int x = 0; x < width; x++ )
		{
			if( z == 0 || z == height - 1 || x == 0 || x == width - 1 )
			{
				glm::vec3 v3Normal = glm::normalize( glm::vec3( p_fData[ z * 3 * height + ( x * 3 ) + 0 ], p_fData[ z * 3 * height + ( x * 3 ) + 1 ], p_fData[ z * 3 * height + ( x * 3 ) + 2 ] ) );
				p_fNormals[ z * 3 * height + ( x * 3 ) + 0 ] = v3Normal.x;
				p_fNormals[ z * 3 * height + ( x * 3 ) + 1 ] = v3Normal.y;
				p_fNormals[ z * 3 * height + ( x * 3 ) + 2 ] = v3Normal.z;
			}
			else
			{
				//Regarding normals: Create two vectors from the diagonal neighbors (top left to bottom right, top right to bottom left) and get the cross product. //robmaister12
				glm::vec3 A, B, C, D;

				A = glm::vec3( p_fData[ ( z - 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 0 ], p_fData[ ( z - 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 1 ], p_fData[ ( z - 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 2 ] );
				B = glm::vec3( p_fData[ ( z - 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 0 ], p_fData[ ( z - 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 1 ], p_fData[ ( z - 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
				C = glm::vec3( p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 0 ], p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 1 ], p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
				D = glm::vec3( p_fData[ ( z + 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 0 ], p_fData[ ( z + 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 1 ], p_fData[ ( z + 1 ) * 3 * height + ( ( x - 1 ) * 3 ) + 2 ] );

				glm::vec3 AC = A - C, BD = B - D;

				glm::vec3 v3Normal = glm::cross( AC, BD );
				p_fNormals[ z * 3 * height + ( x * 3 ) + 0 ] = v3Normal.x;
				p_fNormals[ z * 3 * height + ( x * 3 ) + 1 ] = v3Normal.y;
				p_fNormals[ z * 3 * height + ( x * 3 ) + 2 ] = v3Normal.z;
			}
		}
	}

	//Create vertices for opengl to draw
	int count = 0;
	for( int z = 0; z < height - 1; z++ )
	{
		for( int x = 0; x < width - 1; x++ )
		{
			//X, Y, Z, U, W, NX, NY, NZ, Element
			_vertices.push_back( p_fData[ z * 3 * height + ( x * 3 ) + 0 ] );
			_vertices.push_back( p_fData[ z * 3 * height + ( x * 3 ) + 1 ] );
			_vertices.push_back( p_fData[ z * 3 * height + ( x * 3 ) + 2 ] );
			_vertices.push_back( 0.f );
			_vertices.push_back( 0.f );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( x * 3 ) + 0 ] );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( x * 3 ) + 1 ] );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( x * 3 ) + 2 ] );
			_elements.push_back( count * 4 + 0 );
					 
			_vertices.push_back( p_fData[ z * 3 * height + ( ( x + 1 ) * 3 ) + 0 ] );
			_vertices.push_back( p_fData[ z * 3 * height + ( ( x + 1 ) * 3 ) + 1 ] );
			_vertices.push_back( p_fData[ z * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
			_vertices.push_back( 1.f );
			_vertices.push_back( 0.f );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( ( x + 1 ) * 3 ) + 0 ] );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( ( x + 1 ) * 3 ) + 1 ] );
			_vertices.push_back( p_fNormals[ z * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
			_elements.push_back( count * 4 + 1 );
					 
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( x * 3 ) + 0 ] );
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( x * 3 ) + 1 ] );
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( x * 3 ) + 2 ] );
			_vertices.push_back( 0.f );
			_vertices.push_back( 1.f );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( x * 3 ) + 0 ] );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( x * 3 ) + 1 ] );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( x * 3 ) + 2 ] );
			_elements.push_back( count * 4 + 2 );
					 
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 0 ] );
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 1 ] );
			_vertices.push_back( p_fData[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
			_vertices.push_back( 1.f );
			_vertices.push_back( 1.f );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 0 ] );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 1 ] );
			_vertices.push_back( p_fNormals[ ( z + 1 ) * 3 * height + ( ( x + 1 ) * 3 ) + 2 ] );
					 
			_elements.push_back( count * 4 + 1 );
			_elements.push_back( count * 4 + 2 );
			_elements.push_back( count * 4 + 3 );
			
			count++;
		}
	}

	//Give OpenGL all that data!

	//Generate VAO
	glGenVertexArrays( 1, &_uiVAO );
	glBindVertexArray( _uiVAO );

	//Generate Vertex Buffer Object and upload all the vertices.
	GLuint vbo;
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices.front(), GL_STATIC_DRAW );

	//Generation element buffer object and upload all the element indices.
	GLuint ebo;
	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, _elements.size() * sizeof(int), &_elements.front(), GL_STATIC_DRAW );

	//Get instance of shadermanager and load the diffusetexture shader so we can some pretty lighting on that terrain!
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

	//And last but not least, load the texture to slap onto the terrain.
	_grassTexture.loadTexture( "images/green.bmp", false );
	
	glBindVertexArray( NULL );

	//Cleanup terrain data + normals. OpenGL already has them buffered.
	delete[] p_fData;
	delete[] p_fNormals;
}

void Terrain::render( Camera* cam )
{
	assert( _vertices.size() != 0 );
	glBindVertexArray( _uiVAO );
	_grassTexture.bindTexture();

	_textureShader->use();

	glm::mat4 mvp = cam->getViewProjectionMatrix() * cam->getWorldMatrix();
	glm::mat4 projection = cam->getProjectionMatrix();
	_textureShader->setUniform( "g_wvpMatrix", mvp );
	_textureShader->setUniform( "g_worldMatrix", cam->getWorldMatrix() );
	_textureShader->setUniform( "g_Sampler", 0 );
	DirectionalLight light;
	light.fAmbientIntensity = 0.1f;
	light.fDiffuseIntensity = 0.6f;
	light.v3Color = glm::vec3( 1.f, 1.f, 204.f / 255.f );
	light.v3Direction = glm::vec3( -0.749733, -0.449180, 0.485940 );
	_textureShader->setUniform( "g_DirectionalLight", light );

	glEnable( GL_DEPTH_TEST );

	glDrawElements( GL_TRIANGLES, _vertices.size() / 8 * 3, GL_UNSIGNED_INT, 0 );

	glDisable( GL_DEPTH_TEST );

	glBindVertexArray( NULL );
	glUseProgram( NULL );
}