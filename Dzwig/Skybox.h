#pragma once
#include "CubemapTexture.h"
#include "ShaderProgram.h"
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Skybox
{
	CubemapTexture* skyboxTexture;
	std::vector<GLfloat> vertices;
	GLuint skyboxVAO, skyboxVBO;
	ShaderProgram skyboxShader;
public:
	
	Skybox(std::vector<std::string> fileNames = { "skybox/right.jpg",
			"skybox/left.jpg",
			"skybox/top.jpg",
			"skybox/bottom.jpg",
			"skybox/front.jpg",
			"skybox/back.jpg" });
	void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix);
};

