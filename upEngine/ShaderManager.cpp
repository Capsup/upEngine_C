#include "ShaderManager.h"


ShaderManager::ShaderManager()
{

}

ShaderProgram* ShaderManager::loadShader( std::string sShaderName )
{
	ShaderProgram* program = new ShaderProgram();
	Shader shaderVertex;
	Shader shaderFragment;
	if( !shaderVertex.loadShader( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".vert" ) ), GL_VERTEX_SHADER )
		|| !shaderFragment.loadShader( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".frag" ) ), GL_FRAGMENT_SHADER ) )
	{
		return NULL;
	}

	FILE* file;

	file = fopen( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".geom" ) ).c_str(), "r" );
	if( file != NULL )
	{
		Shader shaderGeometry;
		if( !shaderGeometry.loadShader( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".geom" ) ), GL_GEOMETRY_SHADER ) )
			return NULL;
		program->attachShader( &shaderGeometry );
	}


	program->attachShader( &shaderVertex );
	program->attachShader( &shaderFragment );

	if( sShaderName == "diffusetexture" )
		glBindFragDataLocation( program->getProgramID(), 0, "FragColor" );
	else
		glBindFragDataLocation( program->getProgramID(), 0, "outColor" );

	program->linkProgram();

	program->sName = sShaderName;
	
	_vecShaders.push_back( program );

	return( program );
}

void ShaderManager::useProgram( GLuint uiProgramID )
{
	for( std::vector<ShaderProgram*>::iterator it = _vecShaders.begin(); it < _vecShaders.end(); it++ )
	{
		if( (*it)->getProgramID() == uiProgramID )
			glUseProgram( uiProgramID );
	}
}
