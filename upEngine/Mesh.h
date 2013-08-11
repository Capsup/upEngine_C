#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "AssetManager.h"
#include "Texture.h"
#include "Shader.h"

struct Vertex
{
	glm::vec3 _pos;
    glm::vec2 _tex;
    glm::vec3 _normal;

    Vertex() 
	{

	}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        _pos    = pos;
        _tex    = tex;
        _normal = normal;
    }
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool loadMesh( const std::string& sPath );
	void render(ShaderProgram* pShader);

private:
	void initFromScene( const aiScene* pScene, const std::string& sPath );
	void initMesh( unsigned int uiIndex, const aiMesh* paiMesh );
    void initMaterials( const aiScene* pScene, const std::string& sPath );
    void clear();

	struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void init(const std::vector<Vertex>& vVertices,
                  const std::vector<unsigned int>& vIndices);

        GLuint _uiVBO;
        GLuint _uiEBO;
        unsigned int _numIndices;
        unsigned int _materialIndex;
    };

	std::vector<MeshEntry> _vEntries;
    std::vector<Texture*> _vTextures;

	GLuint _uiVAO;
};
