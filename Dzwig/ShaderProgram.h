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
};