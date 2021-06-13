#ifndef _CRANETOP_H_
#define _CRANETOP_H_

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
#include "Renderer.h"

class CraneTop
{
	Cuboid segment;
	GLuint VAO, VBO;
	GLuint VAOs[20], VBOs[20];
	GLuint index[20];
	GLuint j=0;
	GLfloat hookLength = 1.0f;
	std::vector<glm::mat4> segmentTrans;
	Texture2D* segmentTexture;
	Texture2D* ropeTexture;
	Texture2D* concreteTexture;

	GLfloat length = 15.0f;
	GLfloat posX = 0.f, posY = 30.0f, posZ = 0.f;
	GLfloat width = 1.0f;
	GLfloat segmentScale = 0.03f;

	GLfloat hookPosX;

	void arm();
	void lines();
	

public:

	CraneTop(GLfloat w = 1.0f, GLfloat scale = 0.03f, GLfloat l = 30.f,
		GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f,
		Texture2D* texSeg = nullptr, Texture2D* texRope = nullptr, Texture2D* texConcrete = nullptr, GLuint vao = 0);

	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h, GLfloat rot);
	void generateVO(GLuint * vao, GLuint * vbo, Cuboid * segment);
	void moveHookX(GLfloat dx);

	void moveHookY(GLfloat dy);



};

#endif