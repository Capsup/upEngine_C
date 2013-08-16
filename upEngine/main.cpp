#define GLEW_STATIC

/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <list>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <GL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Texture.h"
#include "Skybox.h"
#include "FreeTypeFont.h"
#include "Terrain.h"
#include "AssetManager.h"
#include "Mesh.h"

struct ModelInstance
{
	ModelAsset* asset;
	glm::mat4 transform;
};

Camera cam;
GLint viewport[4];
std::list<ModelInstance> g_Instances;



void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if( key == GLFW_KEY_F1 && action == GLFW_PRESS )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else if( key == GLFW_KEY_F2 && action == GLFW_PRESS )
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else if( key == GLFW_KEY_F3 && action == GLFW_PRESS )
	{
		glm::vec3 v3Normal = glm::normalize( cam.getEyePos() - cam.getOrigin() );
		printf( "Direction: '%f, %f, %f' \n", v3Normal.x, v3Normal.y, -v3Normal.z );
	}
}

void RenderInstance( const ModelInstance& instance )
{
	ModelAsset* asset = instance.asset;
	if( asset == NULL )
	{
		printf( "ERROR! Tried to render instance with nil asset\n" );
		return;
	}
	ShaderProgram* shader = asset->shader;

	if( shader == NULL )
	{
		printf( "ERROR! Attempted to bind to nil shader\n" );
		return;
	}

	shader->use();
	shader->setUniform( "g_mvpMatrix", cam.getViewProjectionMatrix() * instance.transform );
	shader->setUniform( "g_Sampler", 0 );
	shader->setUniform( "g_viewMatrix", cam.getProjectionMatrix() );
	DirectionalLight light;
	light.fAmbientIntensity = 0.1f;
	light.fDiffuseIntensity = 0.6f;
	light.v3Color = glm::vec3( 1.f, 1.f, 204.f / 255.f );
	light.v3Direction = glm::vec3( -0.659189, -0.534744, -0.528695 );
	shader->setUniform( "g_DirectionalLight", light );

	if( asset->mesh != NULL )
		asset->mesh->render(shader);

	glBindTexture( GL_TEXTURE_2D, NULL );
	shader->stopUsing();

	/*asset->texture->bindTexture();

	glBindVertexArray( asset->vao );
	glDrawArrays( asset->drawType, asset->drawStart, asset->drawCount );

	glBindVertexArray( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	shader->stopUsing();*/
}

int main( void )
{

	int running = GL_TRUE;

	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	GLFWwindow* window = glfwCreateWindow( 800, 600, "OpenGL", NULL, NULL );
	if( window == NULL )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glfwMakeContextCurrent( window );
	glfwSetKeyCallback( window, keyCallback );
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );

	//VSYNC?:
	glfwSwapInterval( 1 ); // 0 for off, 1 for 60fps


	glewExperimental = GL_TRUE;
	if( glewInit() )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}



	cam.calcOrtho2D();


	/*Terrain terrain;

	terrain.loadHeightMap( "images/terrain2.bmp" );*/

	//terrain.loadHeightMap( "/content/images/terrain3.png" );

	ShaderManager sm = ShaderManager::getInstance();

	/*GLuint vao3;
	glGenVertexArrays( 1, &vao3 );
	glBindVertexArray( vao3 );

	GLuint vbo3;
	glGenBuffers( 1, &vbo3 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo3 );*/


	/*Skybox skybox;
	skybox.loadSkybox();*/

	/*ModelInstance box;
	box.asset = AssetManager::getInstance().loadBoxAsset();
	box.transform = glm::mat4();
	//g_Instances.push_back( box );*/

	/*ModelInstance testModel;
	testModel.asset = AssetManager::getInstance().loadFile( "models/trees/oak/tree_oak.obj" );//"/models/thor/thor.obj" );//"models/chair/chair.obj" );// ////"models/trees/broad leaf/Broad Leaf Straight Trunk.obj" ); //
	testModel.transform = glm::mat4();
	g_Instances.push_back( testModel );*/

	ShaderProgram* fontshader = sm.loadShader( "ortho2d" );

	FreeTypeFont font;
	font.loadFont( "verdana.ttf", 32 );
	font.setShader( fontshader );

	double oldTime = glfwGetTime();
	while( running )
	{
		double curTime = glfwGetTime();
		double frameTime = curTime - oldTime;
		oldTime = curTime;

		glClearColor( 0.f, 0.f, 0.f, 1.f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		cam.update( window );

		//skybox.render( &cam );

		//terrain.render( &cam );

		glEnable( GL_DEPTH_TEST );

		/*std::list<ModelInstance>::const_iterator it;
		for(it = g_Instances.begin(); it != g_Instances.end(); ++it)
		{
		    RenderInstance(*it);
		}*/

		glDisable( GL_DEPTH_TEST );

		//TEXT ALWAYS LAST!
		fontshader->use();
		fontshader->setUniform( "pMatrix", cam.getOrtho2D() );
		font.printf( 10, 285, 8, "FPS: %f", 1 / frameTime );
		//font.printf( 10, 250, 24, "FPS: %f", 1 / trueTime );

		glEnable( GL_DEPTH_TEST );
		
		
		glfwSwapBuffers( window );
		glfwPollEvents();
		running = !glfwGetKey( window, GLFW_KEY_ESCAPE ) && glfwWindowShouldClose( window ) == false;
	}

	glfwTerminate();
	
	exit( EXIT_SUCCESS );
}
