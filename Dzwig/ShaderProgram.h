#ifndef _SHADERP_H_
#define _SHADERP_H_
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#pragma once

class ShaderProgram
{
	GLuint program_id; 	// The program ID
	GLchar* vertexPath, *fragmentPath;
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	ShaderProgram();

	void compileShader();
	void setShaderPaths(GLchar* v, GLchar* f);

	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;

	void setFloat(const std::string & name, float value) const;

	void setVec2(const std::string & name, float x, float y) const;
	void setVec2(const std::string & name, const glm::vec2 & value) const;

	void setVec3(const std::string & name, const glm::vec3 & value) const;

	void setVec3(const std::string & name, float x, float y, float z) const;

	void setVec4(const std::string & name, const glm::vec4 & value) const;

	void setVec4(const std::string & name, float x, float y, float z, float w);

	void setMat2(const std::string & name, const glm::mat2 & mat) const;

	void setMat3(const std::string & name, const glm::mat3 & mat) const;

	void setMat4(const std::string & name, const glm::mat4 & mat) const;






};

#endif