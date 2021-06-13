#pragma once
#include "Cuboid.h"

class Renderer
{
public:
	void static generateVO(GLuint * vao, GLuint * vbo, Cuboid * segment)
	{
		glGenVertexArrays(1, vao);
		glBindVertexArray(*vao);
		glGenBuffers(1, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			segment->getVertexTextureArraySize() * sizeof(GLfloat),
			segment->getVertexTextureArrayPointer(),
			GL_STATIC_DRAW);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		// texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
};