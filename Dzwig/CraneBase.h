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
class CraneBase
{
	Cuboid* segment;
	GLuint VAO, VBO;
	GLfloat width = 2*glm::sqrt(2);
	GLfloat height = 2 * glm::sqrt(2);
	std::vector<glm::mat4> segmentTrans;

public:
	CraneBase(GLfloat width, GLfloat height, std::string textureFileName);

	void draw(ShaderProgram* s, Camera* c, GLuint w, GLuint h);
};

