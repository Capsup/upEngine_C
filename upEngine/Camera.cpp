#include "Camera.h"


Camera::Camera()
{
	_v3Origin = glm::vec3( 0.f, 0.f, 0.f );
	_v3EyePos = glm::vec3( 0.f, 0.f, -1.f );
	_v3Up = glm::vec3( 0.f, 1.f, 0.f );
	_m4LookAt = glm::lookAt( _v3Origin, _v3EyePos, _v3Up );
}

void Camera::setLookAt( glm::mat4 m4LookAt )
{
	_m4LookAt = m4LookAt;
}

glm::mat4 Camera::getLookAt()
{
	return _m4LookAt;
}

void Camera::setOrigin( glm::vec3 v3Origin )
{
	_v3Origin = v3Origin;
}

glm::vec3 Camera::getOrigin()
{
	//TODO: Not sure if it's necessary to minus out the .z component?
	return _v3Origin;
}

void Camera::setEyePos( glm::vec3 v3EyePos )
{
	_v3EyePos = v3EyePos;
}

glm::vec3 Camera::getEyePos()
{
	return _v3EyePos;
}

void Camera::setUp( glm::vec3 v3Up )
{
	_v3Up = v3Up;
}

glm::vec3 Camera::getUp()
{
	return _v3Up;
}

void Camera::setOrtho2D( glm::mat4 m4Ortho )
{
	_m4Ortho = m4Ortho;
}

glm::mat4 Camera::getOrtho2D()
{
	return _m4Ortho;
}

void Camera::calcOrtho2D()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	iScreenX = viewport[2] / 2; iScreenY = viewport[3] / 2;

	_m4Ortho = glm::ortho( 0.f, float( iScreenX ), 0.f, float( iScreenY ) );
}

void Camera::moveForward( float fAmount )
{
	glm::vec3 v3Vector = _v3EyePos - _v3Origin;

	_v3Origin.x = _v3Origin.x + v3Vector.x * fAmount;
	_v3Origin.y = _v3Origin.y + v3Vector.y * fAmount;
	_v3Origin.z = _v3Origin.z + v3Vector.z * fAmount;
	_v3EyePos.x = _v3EyePos.x + v3Vector.x * fAmount;
	_v3EyePos.y = _v3EyePos.y + v3Vector.y * fAmount;
	_v3EyePos.z = _v3EyePos.z + v3Vector.z * fAmount;

	apply();
}

void Camera::moveMouse( GLFWwindow* window)
{
	double dMouseX = 0, dMouseY = 0;
	glfwGetCursorPos( window, &dMouseX, &dMouseY );

	glfwSetCursorPos( window, iScreenX, iScreenY );

	float fDeltaX = (float) ( iScreenX - dMouseX ) * 0.1f;
	float fDeltaY = (float) ( iScreenY - dMouseY ) * 0.1f;

	if( fDeltaX != 0.f )
	{
		_v3EyePos -= _v3Origin;
		_v3EyePos = glm::rotate( _v3EyePos, fDeltaX, glm::vec3( 0.f, 1.f, 0.f ) );
		_v3EyePos += _v3Origin;
	}

	if( fDeltaY != 0.f )
	{
		glm::vec3 v3Axis = glm::normalize( glm::cross( _v3EyePos - _v3Origin, _v3Up ) );
		glm::vec3 v3Dir = glm::normalize( _v3EyePos - _v3Origin );
		glm::vec3 v3Dir2 = glm::normalize( glm::vec3( v3Dir.x, 0.f, v3Dir.z ) );
		float fAngle = glm::acos( glm::dot( v3Dir2, v3Dir ) ) * ( 180.f / PI );

		if( v3Dir.y < 0 )
			fAngle *= -1.f;

		fAngle += fDeltaY;
		if( fAngle > -89.80f && fAngle < 89.80f)
		{
			_v3EyePos -= _v3Origin;
			_v3EyePos = glm::rotate( _v3EyePos, fDeltaY, v3Axis );
			_v3EyePos += _v3Origin;
		}
	}

	apply();
}

void Camera::apply()
{
	_m4LookAt = glm::lookAt( _v3Origin, _v3EyePos, _v3Up );
}

void Camera::update( GLFWwindow* window)
{
	//TODO: Make sure to reset mouse back to center when this CHANGES from false to true.
	if( glfwGetWindowAttrib( window, GLFW_FOCUSED ) != GL_TRUE )
		return;

	moveMouse( window );

	float fMultiplier = 10.f;

	if( glfwGetKey( window, GLFW_KEY_LEFT_CONTROL ) )
		fMultiplier = 1.f;

	glm::vec3 v3Forward = glm::normalize( _v3EyePos - _v3Origin ) * fMultiplier;
	glm::vec3 v3Strafe = glm::normalize( glm::cross( _v3EyePos - _v3Origin, _v3Up ) ) * fMultiplier;
	glm::vec3 v3Move;

	static float fTime = (float) ( glfwGetTime() ) - fTime;
	if( glfwGetKey( window, 'W' ) )
		v3Move += ( v3Forward  );
	if( glfwGetKey( window, 'S' ) )
		v3Move -= ( v3Forward  );
	if( glfwGetKey( window, 'A' ) )
		v3Move -= ( v3Strafe  );
	if( glfwGetKey( window, 'D' ) )
		v3Move += ( v3Strafe  );

	_v3EyePos += v3Move;
	_v3Origin += v3Move;

	apply();
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective( 45.0f, 800.f / 600.f, 0.1f, 100000.f );
}

glm::mat4 Camera::getViewProjectionMatrix()
{
	return glm::perspective( 45.0f, 800.f / 600.f, 0.1f, 100000.f ) * getLookAt();
}