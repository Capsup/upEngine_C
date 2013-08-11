#include "Shader.h"


Shader::Shader()
{

}

Shader::Shader( char* p_cPath, unsigned int uiType )
{
	loadShader( p_cPath, uiType );
}

bool Shader::loadShader( char* p_cPath, unsigned int uiType )
{
	return( Shader::loadShader( std::string( p_cPath ), uiType ) );
}

bool Shader::loadShader( std::string sPath, unsigned int uiType )
{
	loadSource( sPath.c_str(), uiType );

	int iCompileStatus;
	glGetShaderiv( _uiShaderID, GL_COMPILE_STATUS, &iCompileStatus );

	if( iCompileStatus == GL_FALSE )
	{
		char a_cBuffer[513];
		glGetShaderInfoLog( _uiShaderID, 512, NULL, a_cBuffer ); 

		printf( "ERROR! %s\n", a_cBuffer );

		return false;
	}

	_uiShaderType = uiType;
	_bIsLoaded = true;

	return true;
}

bool Shader::loadSource( const char* p_cPath, unsigned int uiType )
{
	FILE* file;
	long int size;
	char* content;
 
	fopen_s( &file, p_cPath, "r" );

	if( file == NULL )
		return NULL;

	fseek( file, 0, SEEK_END );
	size = ftell( file );
	rewind( file );

	content = (char*) calloc( size + 1, 1 );
	fread( content, 1, size, file );

	_uiShaderID = glCreateShader( uiType );

	const char* content2 = content;

	glShaderSource( _uiShaderID, 1, &content2, NULL );
	glCompileShader( _uiShaderID );

	fclose( file );
	delete[] content;
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

	_bIsLinked = iLinkStatus;
}

void ShaderProgram::deleteProgram()
{
	if( !_bIsLinked )
		return;

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

void ShaderProgram::setUniform( std::string sName, const glm::mat4 m4Matrix )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniformMatrix4fv( iLoc, 1, GL_FALSE, (GLfloat*) &m4Matrix );
}

void ShaderProgram::setUniform( std::string sName, const int iInteger )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, sName.c_str() );
	glUniform1i( iLoc, iInteger );
}

void ShaderProgram::setUniform( std::string sName, const DirectionalLight& Light )
{
	GLint iLoc = glGetUniformLocation( _uiProgramID, "g_DirectionalLight.v3Color" );
	glUniform3f( iLoc, Light.v3Color.r, Light.v3Color.g, Light.v3Color.b );
	iLoc = glGetUniformLocation( _uiProgramID, "g_DirectionalLight.fAmbientIntensity" );
	glUniform1f( iLoc, Light.fAmbientIntensity );
	iLoc = glGetUniformLocation( _uiProgramID, "g_DirectionalLight.fDiffuseIntensity" );
	glUniform1f( iLoc, Light.fDiffuseIntensity );
	iLoc = glGetUniformLocation( _uiProgramID, "g_DirectionalLight.v3Direction" );
	glm::vec3 v3LightNormal = glm::normalize( Light.v3Direction );
	
	glUniform3f( iLoc, v3LightNormal.x, v3LightNormal.y, v3LightNormal.z );
}