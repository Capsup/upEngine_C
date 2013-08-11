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

	if( asset == NULL )
	{
		printf( "ERROR! Error occured while loading file: %s\n", sPath.substr(sPath.find_last_of( "/" ), sPath.size() ).c_str() );
		return NULL;
	}

	_assetList.insert( std::pair<std::string, ModelAsset*>( sPath.substr(sPath.find_last_of( "/" ), sPath.size() ), asset ) );


	return asset;
}

/*std::vector<std::string> AssetManager::split( std::string sString, std::string sTab )
{
	std::vector<std::string> vResult;
	while( true )
	{
		int pos = sString.find(sTab);
		if(pos == -1)
		{
			vResult.push_back(sString);
			break;
		}
		vResult.push_back(sString.substr(0, pos));
		sString = sString.substr(pos+1, sString.size()-pos-1);
	}
	return vResult;
}

ModelAsset* AssetManager::loadObjFile( std::string sPath )
{
	ModelAsset* asset = new ModelAsset();
	FILE* p_File = fopen( Utils::contentPath( sPath ).c_str(), "rt" );

	if( p_File == NULL )
	{
		printf( "Unable to load .obj file. (Did you type the path correctly?)\n" );
		return NULL;
	}

	char line[255];

	std::vector<glm::vec3> v3Vertices;
	std::vector<glm::vec2> v2TexCoords;
	std::vector<glm::vec3> v3Normals;
	VBO* vboModelData = new VBO();

	int iNumFaces = 0;
	int iAttrBitField = 0;

	while(fgets(line, 255, p_File))
	{
		bool bError = false;

		if( strlen( line ) <= 1 )
			continue;

		std::stringstream ss(line);
		std::string sType;
		ss >> sType;

		if( sType == "#" )
			continue;
		else if( sType == "v" )
		{
			glm::vec3 v3NewVertex;
			int iDim = 0;
			while( iDim < 3 && ss >> v3NewVertex[iDim] )
				iDim++;
			v3Vertices.push_back( v3NewVertex );
			iAttrBitField |= 1;
		}
		else if( sType == "vt" )
		{
			glm::vec2 v2NewCoord;
			int iDim = 0;
			while( iDim < 2 && ss >> v2NewCoord[iDim] )
				iDim++;
			v2TexCoords.push_back( v2NewCoord );
			iAttrBitField |= 2;
		}
		else if( sType == "vn" )
		{
			glm::vec3 v3NewNormal;
			int iDim = 0;
			while( iDim < 3 && ss >> v3NewNormal[iDim] )
				iDim++;
			v3NewNormal = glm::normalize( v3NewNormal );
			v3Normals.push_back( v3NewNormal );
			iAttrBitField |= 4;
		}
		else if( sType == "f" )
		{
			std::string sFaceData;

			while( ss >> sFaceData )
			{
				std::vector<std::string> vData = split( sFaceData, "/" );
				int iVertIndex = -1, iTexCoordIndex = -1, iNormalIndex = -1;

				if( iAttrBitField&1 )
				{
					if( vData[0].size() > 0 )
						sscanf( vData[0].c_str() , "%d", &iVertIndex );
					else
						bError = true;
				}

				if( iAttrBitField&2 && !bError )
				{
					if( vData.size() >= 1 )
					{
						if( vData[1].size() > 0 )
							sscanf( vData[1].c_str(), "%d", &iTexCoordIndex );
						else
							bError = true;
					}
					else
						bError = true;
				}

				if( iAttrBitField&4 && !bError )
				{
					if( vData.size() >= 2 )
					{
						if( vData[2].size() > 0 )
							sscanf( vData[2].c_str(), "%d", &iNormalIndex );
						else
							bError = true;
					}
					else
						bError = true;
				}

				if( bError )
				{
					fclose(p_File);
					printf( "ERROR! Error occured while loading .obj file\n" );
					return NULL;
				}

				if( iVertIndex > 0 && iVertIndex <= v3Vertices.size() )
					vboModelData->addData( &v3Vertices[iVertIndex - 1], sizeof( glm::vec3 ) );
				if( iTexCoordIndex > 0 && iTexCoordIndex <= v2TexCoords.size() )
					vboModelData->addData( &v2TexCoords[iTexCoordIndex - 1], sizeof( glm::vec2 ) );
				if( iNormalIndex > 0 && iNormalIndex <= v3Normals.size() )
					vboModelData->addData( &v3Normals[iNormalIndex - 1], sizeof( glm::vec3 ) );
			}
			iNumFaces++;
		}
		//Shading model
		else if( sType == "s" )
		{

		}
		//Material specified
		else if( sType == "usemtl" )
		{

		}
	}

	fclose( p_File );

	if( iAttrBitField == 0 )
	{
		printf( "ERROR! Error occured while attempting to load .obj file\n" );
		return NULL;
	}

	vboModelData->createVBO();
	vboModelData->bindVBO();
	vboModelData->uploadDataToGPU( GL_STATIC_DRAW );

	asset->vbo = vboModelData;

	glGenVertexArrays( 1, &asset->vao );
	glBindVertexArray( asset->vao );

	int iDataStride = 0;

	if( iAttrBitField&1 )
		iDataStride += sizeof( glm::vec3 );
	if( iAttrBitField&2 )
		iDataStride += sizeof( glm::vec2 );
	if( iAttrBitField&4 )
		iDataStride += sizeof( glm::vec3 );

	if( iAttrBitField&1 )
	{
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, iDataStride, 0 );
	}

	if( iAttrBitField&2 )
	{
		glEnableVertexAttribArray( 1 );
		int iDataOffset = 0;
		if( iAttrBitField&1 )
			iDataOffset += sizeof( glm::vec3 );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, iDataStride, (void*) iDataOffset );
	}

	if( iAttrBitField&4 )
	{
		glEnableVertexAttribArray( 2 );
		int iDataOffset = 0;
		if( iAttrBitField&1 )
			iDataOffset += sizeof( glm::vec3 );
		if( iAttrBitField&2 )
			iDataOffset += sizeof( glm::vec2 );
		glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, iDataStride, (void*) iDataOffset );
	}

	//Load Material
	p_File = fopen( Utils::contentPath( sPath + ".mtl" ).c_str(), "rt" );

	if( p_File == NULL )
	{
		printf( "ERROR! Unable to load .mtl file for path: %s\n", sPath );
		return NULL;
	}

	char line2[255];

	while( fgets( line2, 255, p_File ) )
	{
		std::stringstream ss(line2);
		std::string sType;
		ss >> sType;

		if( sType == "map_Kd" )
		{
			std::string sLine = line2;
			int iFrom = sLine.find("map_Kd") + 6 + 1;
			std::string sTextureName = sLine.substr( iFrom, sLine.size() - iFrom - 1 );

			Texture* ambientTexture = new Texture();
			if( !ambientTexture->loadTexture( sPath.substr( 0, sPath.find_last_of( "/" ) + 1 ) + sTextureName, true ) )
			{
				return NULL;
			}
			
			ambientTexture->setFiltering( TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_NEAREST_MIPMAP );
			asset->texture = ambientTexture;
			break;
		}
	}

	fclose( p_File );

	if( asset->texture == NULL )
	{
		printf( "ERROR! Failed to load texture of object file.\n" );
		return NULL;
	}

	asset->drawStart = 0;
	asset->drawCount = iNumFaces * 3;
	asset->drawType = GL_TRIANGLES;
	asset->shader = ShaderManager::getInstance().loadShader( "diffusetexture" );

	return asset;
}*/

