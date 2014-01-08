#include "Shader.h"


Shader::Shader()
{

}

Shader::Shader( const char* p_cPath, const unsigned int uiType )
{
	loadShader( p_cPath, uiType );
}

bool Shader::loadShader( const char* p_cPath, const unsigned int uiType )
{
	return( Shader::loadShader( std::string( p_cPath ), uiType ) );
}

bool Shader::loadShader( const std::string sPath, const unsigned int uiType )
{
	if( !loadSource( sPath.c_str(), uiType ) )
	{
		printf( "ERROR! Failed to load source of shader from file: %s\n", sPath );	
	}

	int iCompileStatus;
	glGetShaderiv( _uiShaderID, GL_COMPILE_STATUS, &iCompileStatus );

	if( iCompileStatus == GL_FALSE )
	{
		char a_cBuffer[513];
		glGetShaderInfoLog( _uiShaderID, 512, NULL, a_cBuffer ); 

		printf( "ERROR! Shader failed to compile: %s\n", a_cBuffer );

		return false;
	}

	_uiShaderType = uiType;
	_bIsLoaded = true;

	return true;
}

bool Shader::loadSource( const char* p_cPath, const unsigned int uiType )
{
	FILE* file;
	long int size;
	char* content;
 
	file = fopen( p_cPath, "r" );

	if( file == NULL )
		return false;

	fseek( file, 0, SEEK_END );
	size = ftell( file );
	rewind( file );

	//TODO: This uses c-style allocation. Why not use the fancy new c++ stuff?
	content = (char*) calloc( size + 1, 1 );
	fread( content, 1, size, file );

	_uiShaderID = glCreateShader( uiType );

	const char* content2 = content;

	glShaderSource( _uiShaderID, 1, &content2, NULL );
	glCompileShader( _uiShaderID );

	fclose( file );
	delete[] content;

	return true;
}

void Shader::deleteShader()
{
	if( !_bIsLoaded )
		return;

	_bIsLoaded = false;
	glDeleteShader( _uiShaderID );
}

GLuint Shader::getShaderID()
{
	return _uiShaderID;
}

bool Shader::isLoaded()
{
	return _bIsLoaded;
}




ShaderProgram::ShaderProgram()
{
	_uiProgramID = glCreateProgram();
}

bool ShaderProgram::attachShader( Shader* p_Shader )
{
	if( !p_Shader->isLoaded() )
	{
		printf( "ERROR! ShaderID: %i is not loaded.\n", p_Shader->getShaderID() );

		return false;
	}

	glAttachShader( _uiProgramID, p_Shader->getShaderID() );
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram( _uiProgramID );

	int iLinkStatus;
	glGetProgramiv( _uiProgramID, GL_LINK_STATUS, &iLinkStatus );
	
	if( !iLinkStatus == GL_TRUE )
	{
		char a_cBuffer[513];
		glGetProgramInfoLog( _uiProgramID, 512, NULL, a_cBuffer );

		printf( "ERROR! %s\n", a_cBuffer );

		return false;
	}

	GLsizei count;
	GLuint shaders[3];

	glGetAttachedShaders( _uiProgramID, 3, &count, shaders );

	for( int i = 0; i < count; i++ )
	{
		glDeleteShader( shaders[i] );
	}

	_bIsLinked = iLinkStatus;
}

void ShaderProgram::deleteProgram()
{
	if( !_bIsLinked )
	{
		printf( "ERROR! Attempted to delete unloaded shader.\n" );
		return;
	}

	_bIsLinked = false;
	glDeleteProgram( _uiProgramID );
}

void ShaderProgram::use()
{
	if( _bIsLinked )
		glUseProgram( _uiProgramID );
	else
		printf( "ERROR! Attempted to bind to unlinked shader.\n" );
}

void ShaderProgram::stopUsing()
{
	glUseProgram( 0 );
}

GLuint ShaderProgram::getProgramID()
{
	return _uiProgramID;
}

void ShaderProgram::setUniform( const std::string sName, const glm::vec2 v2Vector )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform2f( iLoc, v2Vector.x, v2Vector.y );
}

void ShaderProgram::setUniform( const std::string sName, const glm::vec3 v3Vector )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform3f( iLoc, v3Vector.x, v3Vector.y, v3Vector.z );
}

void ShaderProgram::setUniform( const std::string sName, const glm::vec4 v4Vector )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform4f( iLoc, v4Vector.x, v4Vector.y, v4Vector.z, v4Vector.w );
}

void ShaderProgram::setUniform( const std::string sName, const glm::mat4 m4Matrix )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniformMatrix4fv( iLoc, 1, GL_FALSE, (GLfloat*) &m4Matrix );
}

void ShaderProgram::setUniform( const std::string sName, const int iInteger )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform1i( iLoc, iInteger );
}

void ShaderProgram::setUniform( const std::string sName, const GLfloat fFloat )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform1f( iLoc, fFloat );
}

void ShaderProgram::setUniform( const std::string sName, const DirectionalLight& Light )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, "dirLight.Color" );
	glUniform3f( iLoc, Light.v3Color.r, Light.v3Color.g, Light.v3Color.b );
	iLoc = glGetUniformLocation( _uiProgramID, "dirLight.AmbientIntensity" );
	glUniform1f( iLoc, Light.fAmbientIntensity );
	iLoc = glGetUniformLocation( _uiProgramID, "dirLight.DiffuseIntensity" );
	glUniform1f( iLoc, Light.fDiffuseIntensity );
	iLoc = glGetUniformLocation( _uiProgramID, "dirLight.Direction" );
	glm::vec3 v3LightNormal = glm::normalize( Light.v3Direction );
	
	glUniform3f( iLoc, v3LightNormal.x, v3LightNormal.y, v3LightNormal.z );
}