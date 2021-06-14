#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Texture2D.h"
#include "CubemapTexture.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include<vector>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Light
{
	struct PointLight
	{
		glm::vec3 position;

		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	ShaderProgram* shader;

	GLboolean isCameraLightEnabled = true;

	std::vector<GLboolean> isEnabled;

	std::vector<PointLight> lights;
	PointLight cameraLight;

	glm::vec3 dirLight_direction, dirLight_ambient, dirLight_diffuse, dirLight_specular;
	int material_diffuse;
	GLfloat material_shininess;
	glm::vec3 material_specular;

public:
	Light(ShaderProgram* s, glm::vec3 dirl_dir = glm::vec3(0.f, -1.f, 0.f), glm::vec3 dirl_amb = glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3 dirl_dif = glm::vec3(0.1f, 0.1f, 0.4f), glm::vec3 dirl_spec = glm::vec3(0.5f, 0.5f, 0.5f),
		int m_dif = 0, GLfloat m_shine = 32.f, glm::vec3 m_spec = glm::vec3(0.1f, 0.1f, 0.1f));

	void setShaderParams();

	void addLight(glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat quadratic,
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	void setCameraLight(glm::vec3 *position, GLfloat constant, GLfloat linear, GLfloat quadratic,
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void cameraLightIntensityInc(GLfloat di);
	void updateCameraPosition(glm::vec3 * pos);

	void toggleCameraLight();

	void toggleLight(GLuint i);

	GLuint getNumberOfPointLights();

	glm::vec3 getPointLightPos(GLuint index);
	void updatePointLightPos(GLuint index, glm::vec3 pos);
};

