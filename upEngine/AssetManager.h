#pragma once

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <map>
#include <stdio.h>
#include <sstream>


#include "ShaderManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"
#include "VBO.h"
#include "Mesh.h"

class Mesh;

struct ModelAsset 
{
	//
	ShaderProgram* shader;
	Mesh* mesh;
	/*Texture* texture;
	VBO* vbo;
	//GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLenum drawType;
	GLint drawStart;
	GLint drawCount;*/
};

class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}
	ModelAsset* loadFile( std::string sPath );

	//ModelAsset* loadBoxAsset();
	
private:
	AssetManager();
	
	void operator=( AssetManager const& );

	std::map<std::string, ModelAsset*> _assetList;
};

