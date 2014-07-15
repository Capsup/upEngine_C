#include "Mesh.h"

Mesh::MeshEntry::MeshEntry()
{
	_uiVBO = -1;
	_uiEBO = -1;
	_numIndices = 0;
	_materialIndex = -1;
}

Mesh::MeshEntry::~MeshEntry()
{
	if ( _uiVBO != -1 )
	{
		glDeleteBuffers( 1, &_uiVBO );
	}

	if ( _uiEBO != -1 )
	{
		glDeleteBuffers( 1, &_uiEBO );
	}
}

void Mesh::MeshEntry::init( const std::vector<Vertex>& vVertices, const std::vector<unsigned int>& vIndices )
{
	_numIndices = vIndices.size();

	glGenBuffers( 1, &_uiVBO );
	glBindBuffer( GL_ARRAY_BUFFER, _uiVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vertex) * vVertices.size(), &vVertices[ 0 ], GL_STATIC_DRAW );

	glGenBuffers( 1, &_uiEBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _uiEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _numIndices, &vIndices[ 0 ], GL_STATIC_DRAW );
}

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::clear()
{
	for ( int i = 0; i < _vTextures.size(); i++ )
	{
		if ( _vTextures[ i ] != NULL )
		{
			delete _vTextures[ i ];
			_vTextures[ i ] = NULL;
		}
	}
}

bool Mesh::loadMesh( const std::string& sPath )
{
	clear();

	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile( Utils::contentPath( sPath ), aiProcess_Triangulate | aiProcess_GenSmoothNormals );

	if ( pScene != NULL )
	{
		glGenVertexArrays( 1, &_uiVAO );
		glBindVertexArray( _uiVAO );
		initFromScene( pScene, sPath );
		glBindVertexArray( NULL );
		importer.FreeScene();
	}
	else
	{
		printf( "ERROR! Failed to load mesh from %s (Was the path entered correctly?)\n", sPath.c_str() );
		return false;
	}

	return true;
}

void Mesh::initFromScene( const aiScene* pScene, const std::string& sPath )
{
	_vEntries.resize( pScene->mNumMeshes );
	_vTextures.resize( pScene->mNumMaterials );

	for ( int i = 0; i < _vEntries.size(); i++ )
	{
		const aiMesh* paiMesh = pScene->mMeshes[ i ];
		initMesh( i, paiMesh );
	}

	initMaterials( pScene, sPath );
}

void Mesh::initMesh( const unsigned int uiIndex, const aiMesh* p_aiMesh )
{
	_vEntries[ uiIndex ]._materialIndex = p_aiMesh->mMaterialIndex;

	std::vector<Vertex> vVertices;
	std::vector<unsigned int> vIndices;

	const aiVector3D Zero3D( 0.0f, 0.0f, 0.0f );

	for ( int i = 0; i < p_aiMesh->mNumVertices; i++ )
	{
		const aiVector3D* v3Pos = &( p_aiMesh->mVertices[ i ] );
		const aiVector3D* v3Normal = &( p_aiMesh->mNormals[ i ] );
		const aiVector3D* v3TexCoord = p_aiMesh->HasTextureCoords( 0 ) ? &( p_aiMesh->mTextureCoords[ 0 ][ i ] ) : &Zero3D;

		Vertex v( glm::vec3( v3Pos->x, v3Pos->y, v3Pos->z ), glm::vec2( v3TexCoord->x, v3TexCoord->y ), glm::vec3( v3Normal->x, v3Normal->y, v3Normal->z ) );

		vVertices.push_back( v );
	}

	for ( int i = 0; i < p_aiMesh->mNumFaces; i++ )
	{
		const aiFace& Face = p_aiMesh->mFaces[ i ];

		if ( Face.mNumIndices != 3 )
		{
			printf( "ERROR! Number of indices for face was not 3.\n" );
			continue;
		}

		vIndices.push_back( Face.mIndices[ 0 ] );
		vIndices.push_back( Face.mIndices[ 1 ] );
		vIndices.push_back( Face.mIndices[ 2 ] );
	}

	_vEntries[ uiIndex ].init( vVertices, vIndices );
}

void Mesh::initMaterials( const aiScene* pScene, const std::string& sPath )
{
	std::string::size_type SlashIndex = sPath.find_last_of( "/" );
	std::string sDir;

	if ( SlashIndex == std::string::npos )
		sDir = ".";
	else if ( SlashIndex == 0 )
		sDir = "/";
	else
		sDir = sPath.substr( 0, SlashIndex );

	for ( int i = 0; i < pScene->mNumMaterials; i++ )
	{
		const aiMaterial* pMaterial = pScene->mMaterials[ i ];

		_vTextures[ i ] = NULL;

		if ( pMaterial->GetTextureCount( aiTextureType_DIFFUSE ) > 0 )
		{
			aiString Path;

			if ( pMaterial->GetTexture( aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL ) == AI_SUCCESS )
			{
				std::string sFullPath = sDir + "/" + Path.data;
				_vTextures[ i ] = new Texture( sFullPath );

				if ( _vTextures[ i ] == NULL || !_vTextures[ i ]->isLoaded() )
				{
					printf( "ERROR! Failed to load texture: %s \n", sFullPath.c_str() );
					delete _vTextures[ i ];
					_vTextures[ i ] = NULL;
				}
				else
					printf( "Successfully loaded texture: %s \n", sFullPath.c_str() );
			}
		}

		if ( _vTextures[ i ] == NULL )
			_vTextures[ i ] = new Texture( "images/white.png" );
	}
}

void Mesh::render( ShaderProgram* pShader )
{
	glBindVertexArray( _uiVAO );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

	for ( int i = 0; i < _vEntries.size(); i++ )
	{
		glBindBuffer( GL_ARRAY_BUFFER, _vEntries[ i ]._uiVBO );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* ) sizeof( glm::vec3 ) );
		glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) ( sizeof( glm::vec3 ) + sizeof( glm::vec2 ) ) );
		glBindBuffer( GL_ARRAY_BUFFER, NULL );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vEntries[ i ]._uiEBO );

		const unsigned int uiMaterialIndex = _vEntries[ i ]._materialIndex;

		if ( uiMaterialIndex < _vTextures.size() && _vTextures[ uiMaterialIndex ] != NULL )
			_vTextures[ uiMaterialIndex ]->bindTexture();
		//glEnable( GL_BLEND );
		glDisable( GL_CULL_FACE );
		//glDisable( GL_DEPTH_TEST );
		//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glDrawElements( GL_TRIANGLES, _vEntries[ i ]._numIndices, GL_UNSIGNED_INT, 0 );
		//glEnable( GL_DEPTH_TEST );
		//glDisable( GL_BLEND );
	}

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
	glBindVertexArray( NULL );
}