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

class CraneTower
{
	Cuboid segment;
	GLuint VAO, VBO;
	std::vector<glm::mat4> segmentTrans;

	GLfloat height = 30.0f;
	GLfloat width = 1.0f;
	GLfloat segmentScale = 0.03f;

public:

	CraneTower(std::string textureFileName);
	
	void draw(ShaderProgram* s, Camera* c);

};

