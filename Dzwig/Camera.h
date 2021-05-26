#pragma once
#include <glm\glm.hpp>
#include <GLFW/glfw3.h>
class Camera
{
	const GLfloat minFOV = 20.0f, maxFOV = 140.0f;
	GLfloat FOV = 80.0f;
	GLfloat movSpeed = 0.1f;
	GLfloat rotSpeed = 0.1f;
	
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


	
public:
	enum Movement { UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD };
	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	void printDebug();
	void moveCamera(Movement m);
	GLfloat getFOV();
	void setFOV(GLfloat fov);
	void rotateCamera(GLfloat dx, GLfloat dy);
	void resetCamera();
};

