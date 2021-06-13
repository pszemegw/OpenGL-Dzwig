#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>


Camera::Camera(GLfloat posX , GLfloat posY, GLfloat posZ,
	GLfloat yaw, GLfloat pitch,
	GLfloat fov, GLuint w, GLuint h, GLfloat near, GLfloat far)
{
	cameraPos = glm::vec3(posX, posY, posZ);
	defaultCameraPos = cameraPos;
	this->yaw = yaw; this->pitch = pitch;
	defaultYaw = yaw; defaultFOV = fov; defaultPitch = pitch;
	FOV = fov;
	windowHeight = h; windowWidth = w;
	nearPlane = near; farPlane = far;

	resetCamera();
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
}

void Camera::printDebug()
{
	std::cout << "yaw: " << yaw << std::endl;
	std::cout << "pitch: " << pitch << std::endl;
	std::cout << "cameraDirection: " << cameraDirection.x << " " << cameraDirection.y << " " << cameraDirection.z << std::endl;
	std::cout << "cameraPos: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
	std::cout << "cameraRight: " << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
	std::cout << "cameraUp: " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
}

void Camera::moveCamera(Movement m)
{
	//GLfloat movSpeed = this->movSpeed * dt;
	switch (m) 
	{
	case UP:
		cameraPos += movSpeed *dt* cameraUpTemp;
		break;
	case DOWN:
		cameraPos -= movSpeed *dt* cameraUpTemp;
		break;
	case LEFT:
		cameraPos += movSpeed *dt* cameraRight;//glm::cross(glm::normalize(cameraDirection), glm::normalize(cameraUp));
		break;
	case RIGHT:
		cameraPos -= movSpeed *dt* cameraRight;//glm::cross(cameraDirection/glm::length(cameraDirection), cameraUp / glm::length(cameraUp));
		break;
	case FORWARD:
		cameraPos += movSpeed *dt* cameraDirection;
		break;
	case BACKWARD:
		cameraPos -= movSpeed *dt* cameraDirection;
		break;

	case Y_PLUS:
		cameraPos += movSpeed * dt* cameraUp;
		break;

	case Y_MINUS:
		cameraPos -= movSpeed * dt* cameraUp;
		break;
	}

}

GLfloat Camera::getFOV()
{
	return FOV;
}

glm::vec3 * Camera::getCameraPosition()
{
	return &cameraPos;
}

void Camera::setFOV(GLfloat fov)
{
	if (fov < minFOV) 
	{
		fov = minFOV;
		return;
	}
	if (fov > maxFOV)
	{
		fov = maxFOV;
		return;
	}

	FOV = fov;
	generateProjectionMatrix();
}

void Camera::rotateCamera(GLfloat dx, GLfloat dy)
{
	yaw -= dx * rotSpeed;
	pitch += dy * rotSpeed;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));
	cameraDirection = glm::normalize(front);
	cameraUpTemp = glm::cross(cameraDirection, cameraRight);
}

void Camera::resetCamera()
{
	glm::vec3 front;
	yaw = defaultYaw;
	pitch = defaultPitch;
	cameraPos = defaultCameraPos;
	FOV = defaultFOV;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
	cameraUpTemp = cameraUp;

	generateProjectionMatrix();

}

void Camera::increaseCameraSpeed(GLfloat inc)
{
	movSpeed = movSpeed + inc > 30.f ? 30.f : movSpeed + inc;
}

void Camera::decreaseCameraSpeed(GLfloat dec)
{
	movSpeed = movSpeed - dec < 0.1f ? 0.1f : movSpeed - dec;
}

void Camera::setDeltaTime(GLfloat t)
{
	dt = t;
}

void Camera::generateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(FOV), windowWidth*1.0f / windowHeight, nearPlane, farPlane);
}

glm::mat4 * Camera::getProjectionMatrix()
{
	return &projectionMatrix;
}

glm::vec3 Camera::getCameraFront()
{
	return glm::vec3
	(
		cos(glm::radians(yaw)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);
}
