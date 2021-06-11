#ifndef _CRANEBASE_H_
#define _CRANEBASE_H_

#pragma once
#include "Cuboid.h"
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "Window.h"
#include "Camera.h"
class CraneBase
{
	Cuboid* segment;
	GLuint VAO, VBO;
	GLfloat width = 2*glm::sqrt(2);
	GLfloat height = 2 * glm::sqrt(2);
	GLfloat posX, posY, posZ;
	std::vector<glm::mat4> segmentTrans;
	Texture2D* texture;

public:
	CraneBase(GLfloat w = 2 * glm::sqrt(2), GLfloat h = 2 * glm::sqrt(2), Texture2D* tex = nullptr, GLfloat x=0.f, GLfloat y=0.f, GLfloat z=0.f, GLuint vao=0);
	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h);
};

#endif