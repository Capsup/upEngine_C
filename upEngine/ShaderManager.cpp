#include "ShaderManager.h"


ShaderManager::ShaderManager()
{

}

/*ShaderManager& ShaderManager::getInstance()
{
	static ShaderManager instance;
	return instance;
}*/

ShaderProgram* ShaderManager::loadShader( std::string sShaderName )
{
	ShaderProgram* program = new ShaderProgram();
	Shader shaderVertex;
	Shader shaderFragment;

	shaderVertex.loadShader( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".vert" ) ), GL_VERTEX_SHADER );
	shaderFragment.loadShader( Utils::contentPath( std::string( "shaders/" + sShaderName + "/" + sShaderName + ".frag" ) ), GL_FRAGMENT_SHADER );

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

/*GLuint ShaderManager::loadShader( char* p_cName )
{
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	const char* vertexSource = loadSource( 
		Utils::fixPath( 
		std::string( 
		std::string( "/content/shaders/" ) 
		+ std::string( p_cName ) 
		+ std::string( "/" ) 
		+ std::string( p_cName ) 
		+ std::string( ".vert" )
		) 
		).c_str()
		);
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	const char* fragmentSource = loadSource( Utils::fixPath( std::string( std::string( "/content/shaders/" ) + std::string( p_cName ) + std::string( "/" ) + std::string( p_cName ) + std::string( ".frag" ) ) ).c_str() );

	
	glShaderSource( vertexShader, 1, &vertexSource, NULL );
	glShaderSource( fragmentShader, 1, &fragmentSource, NULL );

	glCompileShader( vertexShader );
	
	GLint status;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &status ); 
	printf( "%u\n", status );

	char buffer[513];
	glGetShaderInfoLog( vertexShader, 512, NULL, buffer ); 

	printf( "%s\n", buffer );

	glCompileShader( fragmentShader );

	GLuint shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );

	

	

	return shaderProgram;
}

GLuint ShaderManager::linkShader( unsigned int uiProgram )
{
	glLinkProgram( uiProgram );
	return uiProgram;
}

const char* ShaderManager::loadSource( const char* pcPath )
{
        FILE *file;
        long int size;
        char *content;
 
        fopen_s(&file, pcPath, "r");
 
        if (file == NULL)
                return NULL;
 
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
 
        content = (char *)calloc(size + 1, 1);
        fread(content, 1, size, file);
 
        return content;
}*/

/*std::string ShaderManager::loadSource( std::string pcPath )
{
        FILE *file;
        long int size;
        char *content;
 
        // Open the file for reading
		fopen_s(&file, pcPath.c_str(), "r");
 
        if (file == NULL)
                return NULL;
 
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
 
        // Read the contents of the file
        content = (char *)calloc(size + 1, 1);
        fread(content, 1, size, file);
 
        return content;
}*/