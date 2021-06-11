#ifndef _CAMERA_H_
#define _CAMERA_H_

#pragma once

#include <glm\glm.hpp>
#include <GLFW/glfw3.h>
class Camera
{
	const GLfloat minFOV = 20.0f, maxFOV = 140.0f;
	GLfloat FOV = 80.0f;
	GLfloat movSpeed = 2.f;
	GLfloat rotSpeed = 0.1f;
	GLfloat dt = 0.0f;
	
	GLfloat defaultFOV = 80.f, defaultYaw = -90.f, defaultPitch = 0.f;
	glm::vec3 defaultCameraPos;

	glm::vec3 cameraPos;
	// +z direction in camera coord system
	glm::vec3 cameraDirection;
	// Right (+x) direction in camera coord system
	glm::vec3 cameraRight;
	// Up direction (+y) in camera coordinate system
	glm::vec3 cameraUp;
	// Cross product of cameraDirection and cameraRight - points to current 'up' direction based on camera pitch
	glm::vec3 cameraUpTemp;
	glm::vec3 direction;
	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;


	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);
	GLuint windowWidth, windowHeight;
	GLfloat nearPlane, farPlane;

	
public:
	enum Movement { UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD };
	//Camera();
	Camera(GLfloat posX = 0.f, GLfloat posY = 0.f, GLfloat posZ = 0.f,
		GLfloat yaw = -90.f, GLfloat pitch = 0.f,
		GLfloat fov = 80.f, GLuint w = 800, GLuint h = 600, GLfloat near = 0.1f, GLfloat far = 1000.f);
	glm::mat4 getWorldToViewMatrix() const;
	void printDebug();
	void moveCamera(Movement m);
	GLfloat getFOV();
	glm::vec3* getCameraPosition();
	void setFOV(GLfloat fov);
	void rotateCamera(GLfloat dx, GLfloat dy);
	void resetCamera();

	void increaseCameraSpeed(GLfloat inc);
	void decreaseCameraSpeed(GLfloat dec);

	void setDeltaTime(GLfloat t);

	void generateProjectionMatrix();
	glm::mat4* getProjectionMatrix();
};

#endif _CAMERA_H_
