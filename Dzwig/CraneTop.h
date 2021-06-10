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
	Texture2D* ropeTexture;
	Texture2D* concreteTexture;

	GLfloat length = 15.0f;
	GLfloat posy = 30.0f;
	GLfloat width = 1.0f;
	GLfloat segmentScale = 0.03f;

public:

	CraneTop(std::string textureFileName);

	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h);
};

