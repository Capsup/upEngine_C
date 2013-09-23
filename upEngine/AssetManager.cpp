#include "AssetManager.h"


AssetManager::AssetManager()
{

}

/*ModelAsset* AssetManager::loadBoxAsset()
{
	if( _assetList.count( "box" ) != 0 )
		return _assetList["box"];

	ModelAsset* asset = new ModelAsset();
	Texture* p_Texture = new Texture();
	p_Texture->loadTexture( "images/wooden-crate.jpg" );

	asset->shader = ShaderManager::getInstance().loadShader( "flattexture" );
	asset->drawType = GL_TRIANGLES;
	asset->drawStart = 0;
	asset->drawCount = 6*2*3; //Sides * Triangles per side * vertices per triangle
	asset->texture = p_Texture;
	//glG->nBuffers( 1, &asset.vbo );
	asset->vbo = new VBO();
	glGenVertexArrays( 1, &asset->vao );
	asset->vbo->createVBO();
	glBindVertexArray( asset->vao );

	//glBindBuffer( GL_ARRAY_BUFFER, asset.vbo );
	asset->vbo->bindVBO();

	GLfloat vertexData[] = 
	{
        //  X     Y     Z       U     V
        // bottom
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
         1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
         1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
         1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

        // top
        -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
         1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
         1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
         1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

        // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
         1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
         1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

        // back
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
         1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
         1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
         1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

        // left
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

        // right
         1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
         1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
         1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
         1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	asset->vbo->addData( vertexData, sizeof(vertexData) );
	asset->vbo->uploadDataToGPU(GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation( asset->shader->getProgramID(), "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0 );

	GLint texAttrib = glGetAttribLocation( asset->shader->getProgramID(), "texCoords" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)) );

	glBindVertexArray( 0 );

	_assetList.insert( std::pair<std::string, ModelAsset*>( "box", asset ) );


	return asset;
}*/

ModelAsset* AssetManager::loadFile( std::string sPath )
{
	ModelAsset* asset = NULL;

	Assimp::Importer importer;
	std::string sSupportedExtensions;

	importer.GetExtensionList( sSupportedExtensions );

	//sPath.replace( sPath.begin(), sPath.end(), "\\", "/" );
	if( sSupportedExtensions.find( sPath.substr( sPath.size() - 4, sPath.size() ) ) != std::string::npos )
	{
		Mesh* mesh = new Mesh();
		bool bResult = mesh->loadMesh( sPath );

		if( bResult )
		{
			asset = new ModelAsset();
			asset->mesh = mesh;
			asset->shader = ShaderManager::getInstance().loadShader( "diffusetexture" );
		}
		else
			delete mesh;
	}
	else
	{
		printf( "ERROR! Attempted to load unsupported file: %s\n", sPath );
		return NULL;
	}

	std::string sFileName = sPath.substr( sPath.find_last_of( "/" ) + 1, sPath.size() );
	if( asset == NULL )
	{
		printf( "ERROR! Error occured while loading file: %s\n", sFileName.c_str() );
		return NULL;
	}

	std::map<std::string, ModelAsset*>::iterator it = _assetList.find( sFileName );
	if( it != _assetList.end() )
		return it->second;
	else
		_assetList.insert( it, std::pair<std::string, ModelAsset*>( sFileName, asset ) );

	return asset;
}