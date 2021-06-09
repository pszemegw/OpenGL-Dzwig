#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>


Camera::Camera() :
cameraPos(0.0f, 0.0f, 0.0f)
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
	cameraUpTemp = cameraUp;
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
	switch (m) 
	{
	case UP:
		cameraPos += movSpeed * cameraUpTemp;
		break;
	case DOWN:
		cameraPos -= movSpeed * cameraUpTemp;
		break;
	case LEFT:
		cameraPos += movSpeed * cameraRight;//glm::cross(glm::normalize(cameraDirection), glm::normalize(cameraUp));
		break;
	case RIGHT:
		cameraPos -= movSpeed * cameraRight;//glm::cross(cameraDirection/glm::length(cameraDirection), cameraUp / glm::length(cameraUp));
		break;
	case FORWARD:
		cameraPos += movSpeed * cameraDirection;
		break;
	case BACKWARD:
		cameraPos -= movSpeed * cameraDirection;
		break;
	}

}

GLfloat Camera::getFOV()
{
	return FOV;
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
	//todo
}

void Camera::increaseCameraSpeed(GLfloat inc)
{
	movSpeed = movSpeed + inc > 10.f ? 10.f : movSpeed + inc;
}

void Camera::decreaseCameraSpeed(GLfloat dec)
{
	movSpeed = movSpeed - dec < 0.1f ? 0.1f : movSpeed - dec;
}
