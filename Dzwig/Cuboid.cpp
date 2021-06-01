#pragma once
#define GLEW_STATIC
#include "Cuboid.h"



Cuboid::Cuboid(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat rotAngle)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;


	vertices = { 
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f };

	modelMatrix = glm::mat4(1.0f);

	vertexTexture = {
		-1.0f,  -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  -1.0f, -1.0f, 0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,

		 -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
		 -1.0f,  -1.0f,  -1.0f, 0.0f, 1.0f,
		 -1.0f,  -1.0f,  -1.0f, 0.0f, 1.0f,
		 -1.0f,  -1.0f, 1.0f, 0.0f, 0.0f,
		 -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		1.0f, 1.0f,  1.0f, 1.0f, 0.0f,
		1.0f,  1.0f,  -1.0f, 1.0f, 1.0f,
		 1.0f,  -1.0f,  -1.0f, 0.0f, 1.0f,
		 1.0f,  -1.0f,  -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  -1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  -1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  -1.0f,  1.0f, 1.0f, 0.0f,
		 1.0f,  -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  -1.0f, -1.0f, 0.0f, 1.0f,

		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f,
		 -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f
	};

	generateModelMatrix();
}

void Cuboid::generateVertices()
{
	
}

glm::mat4 Cuboid::getModelMatrix()
{
	return modelMatrix;
}

void Cuboid::translate()
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY, posZ));
}

void Cuboid::rotate()
{
	modelMatrix = glm::rotate(modelMatrix,glm::radians(rotAngle),glm::vec3(rotX,rotY,rotZ));
}

void Cuboid::scale()
{
	modelMatrix = glm::scale(modelMatrix,glm::vec3(scaleX,scaleY,scaleZ));
}

void Cuboid::generateModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	
	translate();
	rotate();
	scale();
	
	
}

GLfloat* Cuboid::getVertexArrayPointer()
{
	return &vertices[0];
}

GLfloat * Cuboid::getVertexTextureArrayPointer()
{
	return &vertexTexture[0];
}

GLuint Cuboid::getVertexArraySize()
{
	return vertices.size();
}

GLuint Cuboid::getVertexTextureArraySize()
{
	return vertexTexture.size();
}

void Cuboid::setScale(GLfloat x, GLfloat y, GLfloat z)
{
	scaleX = x; scaleY = y; scaleZ = z;
	//glm::scale(modelMatrix, glm::vec3(x, y, z));
	generateModelMatrix();
}

void Cuboid::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	posX = x; posY = y; posZ = z;
	//glm::translate(modelMatrix, glm::vec3(x, y, z));
	generateModelMatrix();
}

void Cuboid::setRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
{
	rotX = x; rotY = y; rotZ = z; rotAngle = angle;
	//glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
	generateModelMatrix();
}

std::vector<GLfloat> Cuboid::getScale()
{
	return std::vector<GLfloat>{scaleX, scaleY, scaleZ};
}

std::vector<GLfloat> Cuboid::getPosition()
{
	return std::vector<GLfloat>{posX, posY, posZ};
}

std::vector<GLfloat> Cuboid::getRotation()
{
	return std::vector<GLfloat>{rotX,rotY,rotZ,rotAngle};
}

void Cuboid::setTexture(std::string fname, GLuint type)
{
	cubeTexture = Texture2D(fname);
}

void Cuboid::setTexture(std::vector<std::string> fnames, GLuint type)
{
	cubeTexture = CubemapTexture(fnames);
}

void Cuboid::divideTextureCoords(GLfloat div)
{
	int j = 3;
	for (int i = 0; i < vertexTexture.size(); ++i)
	{
		if (i == j)
			vertexTexture[i] /= div;
		if (i == j + 1)
		{
			vertexTexture[i] /= div;
			j += 5;
		}
	}
}

Texture Cuboid::getTexture()
{
	return cubeTexture;
}
