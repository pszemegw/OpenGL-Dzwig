#ifndef _CRANETOWER_H_
#define _CRANETOWER_H_

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
#include "Camera.h"

class CraneTower
{
	Cuboid segment;
	GLuint VAO, VBO;
	std::vector<glm::mat4> segmentTrans;
	Texture2D* segmentTexture;

	GLuint VBO1, VBO2, VBO3, VBO4;

	GLuint VBOs[4];
	GLuint VAOs[4];
	GLuint index[4];

	GLfloat height = 30.0f;
	GLfloat width = 1.0f;
	GLfloat segmentScale = 0.03f;

	GLfloat posX, posY, posZ;

public:

	CraneTower(GLfloat h = 30.f, GLfloat w = 1.0f, GLfloat scale = 0.03f, Texture2D* tex = nullptr, GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f, GLuint vao=0);
	
	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h);

	void generateVO(GLuint* vao, GLuint* vbo, Cuboid* segment);

};

#endif