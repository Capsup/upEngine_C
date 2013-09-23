#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>

#include "Utils.h"


class Camera
{
public:
	Camera();
	//void setLookAt( glm::mat4 m4LookAt );

	void setOrigin( glm::vec3 v3Origin );
	glm::vec3 getOrigin();
	void setEyePos( glm::vec3 v3EyePos );
	glm::vec3 getEyePos();
	void setUp( glm::vec3 v3Up );
	glm::vec3 getUp();
	void setOrtho2D( glm::mat4 m4Ortho );
	glm::mat4 getOrtho2D();
	void calcOrtho2D();
	void moveForward( float fAmount );
	void moveMouse( GLFWwindow* window);
	void RotateCamera(double Angle, double x, double y, double z);
	void apply();
	void update( GLFWwindow* window );
	glm::mat4 getWorldMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewProjectionMatrix();
private:
	glm::mat4 _m4World;
	glm::mat4 _m4View;
	glm::mat4 _m4Projection;
	glm::mat4 _m4Ortho;
	glm::vec3 _v3Origin;
	glm::vec3 _v3EyePos;
	glm::vec3 _v3Up;
	int iScreenX, iScreenY;
};

