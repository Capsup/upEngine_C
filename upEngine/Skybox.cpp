#include "Skybox.h"


Skybox::Skybox(void)
{

}


Skybox::~Skybox(void)
{

}

void Skybox::loadSkybox()
{
	_Textures[0].loadTexture( "images/skybox/default/back.jpg" );
	_Textures[1].loadTexture( "images/skybox/default/front.jpg" );
	_Textures[2].loadTexture( "images/skybox/default/left.jpg" );
	_Textures[3].loadTexture( "images/skybox/default/right.jpg" );
	_Textures[4].loadTexture( "images/skybox/default/up.jpg" );
	_Textures[5].loadTexture( "images/skybox/default/down.jpg" );

	for( int i = 0; i < sizeof( _Textures ) / sizeof( Texture ); i++ )
	{
		_Textures[i].setWrapping( TEXTURE_WRAPPING_CLAMP_EDGE, TEXTURE_WRAPPING_CLAMP_EDGE );
	}

	glGenVertexArrays( 1, &_uiVAO );
	glBindVertexArray( _uiVAO );

	glGenBuffers( 1, &_uiVBO );
	glBindBuffer( GL_ARRAY_BUFFER, _uiVBO );

	/*glm::vec3 v3SkyboxVertices[24] = 
	{
		// Front face
		glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f),
		// Back face
		glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f),
		// Left face
		glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f),
		// Right face
		glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f),
		// Top face
		glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(50.0f, 50.0f, 50.0f),
		// Bottom face
		glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f),
	};
	glm::vec2 v3SkyboxTexCoords[4] =
	{
		glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
	};
	*/

	//std::vector<float> SkyboxVertices;
	//50.f, 50.f, 50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f,
	//50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f,

	/*
			50.f, 50.f, 50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, -50.f, 1.f, 0.f, 50.f, -50.f, -50.f, 0.f, 1.f,
		-50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 0.f, 1.f,
		50.f, 50.f, -50.f, 0.f, 0.f, 50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 0.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 1.f, 0.f, 50.f, 50.f, 50.f, 0.f, 1.f,
		50.f, -50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f*/

	//50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f,

	/*
			50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, 50.f, -50.f, -50.f, 1.f, 0.f,
		-50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f, -50.f, 50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f,
		50.f, 50.f, -50.f, 0.f, 1.f, 50.f, -50.f, -50.f, 0.f, 0.f, 50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, 50.f, 50.f, -50.f, 0.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 1.f, 0.f,
		50.f, -50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f
		*/
	//50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f,

	/*
			50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, -50.f, 0.f, 1.f, 50.f, -50.f, -50.f, 0.f, 0.f,
		-50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f,
		50.f, 50.f, -50.f, 1.f, 1.f, 50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 1.f, 1.f, 50.f, 50.f, -50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 0.f, 1.f, 50.f, 50.f, 50.f, 0.f, 0.f,
		50.f, -50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f
		*/

	// 50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f,

	/*
			50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, -50.f, 0.f, 0.f, 50.f, -50.f, -50.f, 0.f, 1.f,
		-50.f, 50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 0.f, 1.f,
		50.f, 50.f, -50.f, 1.f, 0.f, 50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 1.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, 50.f, 50.f, 50.f, 0.f, 1.f,
		50.f, -50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f
		*/

	//50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f,

	/*
			50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, 50.f, -50.f, -50.f, 0.f, 0.f,
		-50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f,
		50.f, 50.f, -50.f, 0.f, 1.f, 50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, 50.f, 50.f, -50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 0.f, 0.f,
		50.f, -50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f
		*/


	/*
				50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, -50.f, 0.f, 1.f, 50.f, -50.f, -50.f, 0.f, 0.f,
		-50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f, -50.f, 50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f,
		50.f, 50.f, -50.f, 1.f, 1.f, 50.f, -50.f, -50.f, 1.f, 0.f, 50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f,
		-50.f, 50.f, -50.f, 1.f, 1.f, 50.f, 50.f, -50.f, 1.f, 0.f, -50.f, 50.f, 50.f, 0.f, 1.f, 50.f, 50.f, 50.f, 0.f, 0.f,
		50.f, -50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f
		*/

	/*
				50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, -50.f, 0.f, 0.f, 50.f, -50.f, -50.f, 0.f, 1.f,
		-50.f, 50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f, -50.f, 50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 0.f, 1.f,
		50.f, 50.f, -50.f, 1.f, 0.f, 50.f, -50.f, -50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f,
		-50.f, 50.f, -50.f, 1.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, -50.f, 50.f, 50.f, 0.f, 0.f, 50.f, 50.f, 50.f, 0.f, 1.f,
		50.f, -50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f
		*/

	/*
	Old working:
				50.f, 50.f, 50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 0.f, 1.f, -50.f, 50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f,
		-50.f, 50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 0.f, 1.f, 50.f, 50.f, -50.f, 1.f, 0.f, 50.f, -50.f, -50.f, 1.f, 1.f,
		-50.f, 50.f, 50.f, 0.f, 0.f, -50.f, -50.f, 50.f, 0.f, 1.f, -50.f, 50.f, -50.f, 1.f, 0.f, -50.f, -50.f, -50.f, 1.f, 1.f,
		50.f, 50.f, -50.f, 0.f, 0.f, 50.f, -50.f, -50.f, 0.f, 1.f, 50.f, 50.f, 50.f, 1.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f,
		-50.f, 50.f, -50.f, 0.f, 0.f, 50.f, 50.f, -50.f, 0.f, 1.f, -50.f, 50.f, 50.f, 1.f, 0.f, 50.f, 50.f, 50.f, 1.f, 1.f,
		50.f, -50.f, -50.f, 0.f, 0.f, -50.f, -50.f, -50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f, -50.f, -50.f, 50.f, 1.f, 1.f*/

	float SkyboxVertices[120] = 
	{
			50.f, 50.f, 50.f, 0.f, 1.f, 50.f, -50.f, 50.f, 0.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f, 50.f, 50.f, -50.f, 1.f, 1.f, 50.f, -50.f, -50.f, 1.f, 0.f,
		-50.f, 50.f, 50.f, 0.f, 1.f, -50.f, -50.f, 50.f, 0.f, 0.f, -50.f, 50.f, -50.f, 1.f, 1.f, -50.f, -50.f, -50.f, 1.f, 0.f,
		50.f, 50.f, -50.f, 0.f, 1.f, 50.f, -50.f, -50.f, 0.f, 0.f, 50.f, 50.f, 50.f, 1.f, 1.f, 50.f, -50.f, 50.f, 1.f, 0.f,
		-50.f, 50.f, -50.f, 0.f, 1.f, 50.f, 50.f, -50.f, 0.f, 0.f, -50.f, 50.f, 50.f, 1.f, 1.f, 50.f, 50.f, 50.f, 1.f, 0.f,
		50.f, -50.f, -50.f, 0.f, 1.f, -50.f, -50.f, -50.f, 0.f, 0.f, 50.f, -50.f, 50.f, 1.f, 1.f, -50.f, -50.f, 50.f, 1.f, 0.f
	};

	glBufferData( GL_ARRAY_BUFFER, sizeof( SkyboxVertices ), SkyboxVertices, GL_STATIC_DRAW );

	_skyboxShader = ShaderManager::getInstance().loadShader( "skybox" );

	GLint posAttrib3 = glGetAttribLocation( _skyboxShader->getProgramID(), "position" );
	glEnableVertexAttribArray( posAttrib3 );
	glVertexAttribPointer( posAttrib3, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0 );

	GLint texAttrib2 = glGetAttribLocation( _skyboxShader->getProgramID(), "texCoords" );
	glEnableVertexAttribArray( texAttrib2 );
	glVertexAttribPointer( texAttrib2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)) );

	glBindVertexArray( 0 );
}

void Skybox::render( Camera* cam )
{
	glBindVertexArray( _uiVAO );
	_skyboxShader->use();

	glm::mat4 mvp = cam->getProjectionMatrix() * ( glm::translate( cam->getLookAt(), cam->getEyePos() ) ) * glm::mat4(1.f);
	_skyboxShader->setUniform( "mvpMatrix", mvp );

	glDisable( GL_DEPTH_TEST );
	for( int i = 0; i < 6; i++ )
	{
		_Textures[i].bindTexture();
		glDrawArrays( GL_TRIANGLE_STRIP, i * 4, 4 );
	}
	glEnable( GL_DEPTH_TEST );

	glUseProgram( 0 );
	glBindVertexArray( 0 );
}