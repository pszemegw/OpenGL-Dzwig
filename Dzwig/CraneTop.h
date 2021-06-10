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
#include "Window.h"
#include "Camera.h"

class CraneTop
{
	Cuboid segment;
	GLuint VAO, VBO;
	std::vector<glm::mat4> segmentTrans;
	Texture2D* segmentTexture;
	Texture2D* ropeTexture;
	Texture2D* concreteTexture;

	GLfloat length = 15.0f;
	GLfloat posX = 0.f, posY = 30.0f, posZ = 0.f;
	GLfloat width = 1.0f;
	GLfloat segmentScale = 0.03f;

	void arm();
	void lines();
	//void weight();

public:

	//CraneTop(std::string textureFileName);
	CraneTop(GLfloat w = 1.0f, GLfloat scale = 0.03f,
		GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f,
		Texture2D* texSeg = nullptr, Texture2D* texRope = nullptr, Texture2D* texConcrete = nullptr, GLuint vao = 0);

	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h);
};

