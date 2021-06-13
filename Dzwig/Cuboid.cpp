#pragma once
#define GLEW_STATIC
#include "Cuboid.h"



Cuboid::Cuboid(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat rotAngle)
{
	setAll(posX,posY,posZ,scaleX,scaleY,scaleZ,rotX,rotY,rotZ,rotAngle);

	modelMatrix = glm::mat4(1.0f);

	vertexTexture = {
		// back face (CCW winding)
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		-1.0f, -1.0f, -1.0f,  1.0f*scaleX, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  1.0f*scaleX, 1.0f*scaleY, // top-right
		-1.0f,  1.0f, -1.0f,  1.0f*scaleX, 1.0f*scaleY, // top-right
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f*scaleY, // top-left
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		// front face (CCW winding)
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  1.0f*scaleX, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  1.0f*scaleX, 1.0f*scaleY, // top-right
		 1.0f,  1.0f,  1.0f,  1.0f*scaleX, 1.0f*scaleY, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f*scaleY, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		// left face (CCW)
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  1.0f*scaleZ, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f,  1.0f*scaleZ, 1.0f*scaleY, // top-right
		-1.0f,  1.0f,  1.0f,  1.0f*scaleZ, 1.0f*scaleY, // top-right
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f*scaleY, // top-left
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		// right face (CCW)
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f, -1.0f,  1.0f*scaleZ, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f*scaleZ, 1.0f*scaleY, // top-right
		 1.0f,  1.0f, -1.0f,  1.0f*scaleZ, 1.0f*scaleY, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f*scaleY, // top-left
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		// bottom face (CCW)      
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f, -1.0f,  1.0f*scaleX, 0.0f, // bottom-right
		 1.0f, -1.0f,  1.0f,  1.0f*scaleX, 1.0f*scaleZ, // top-right
		 1.0f, -1.0f,  1.0f,  1.0f*scaleX, 1.0f*scaleZ, // top-right
		-1.0f, -1.0f,  1.0f,  0.0f, 1.0f*scaleZ, // top-left
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		// top face (CCW)
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		 1.0f,  1.0f,  1.0f,  1.0f*scaleX, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f*scaleX, 1.0f*scaleZ, // top-right
		 1.0f,  1.0f, -1.0f,  1.0f*scaleX, 1.0f*scaleZ, // top-right
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f*scaleZ, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
	};

	
	generateVertices();
	generateModelMatrix();
}

void Cuboid::generateVertices()
{
	//GLfloat scaleX, scaleY, scaleZ;
	//scaleX = this->scaleX < 1.0f ? 1.0f : this->scaleX;
	//scaleY = this->scaleY < 1.0f ? 1.0f : this->scaleY;
	//scaleZ = this->scaleZ < 1.0f ? 1.0f : this->scaleZ;
	//scaleX = glm::ceil(this->scaleX);
	//scaleY = glm::ceil(this->scaleY);
	//scaleZ = glm::ceil(this->scaleZ);
	//scaleX = this->scaleX < 1.0f ? 1/this->scaleX : this->scaleX;
	//scaleY = this->scaleY < 1.0f ? 1/this->scaleY : this->scaleY;
	//scaleZ = this->scaleZ < 1.0f ? 1/this->scaleZ : this->scaleZ;

	//if (scaleX > scaleY && scaleX > scaleZ) { scaleY = scaleX; scaleZ = scaleX; }
	//if (scaleY > scaleX && scaleY > scaleZ) { scaleX = scaleY; scaleZ = scaleY; }
	//if (scaleZ > scaleX && scaleZ > scaleY) { scaleY = scaleZ; scaleX = scaleZ; }

	vertexTextureNormal = {
		// back face (CCW winding)
		 1.0f, -1.0f, -1.0f,					  0.0f, 0.0f, /* bottom-left			*/			0.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,					  1.0f*scaleX, 0.0f, /* bottom-right	*/			0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,					  1.0f*scaleX, 1.0f*scaleY, /* top-right*/			0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,					  1.0f*scaleX, 1.0f*scaleY, /*top-right	*/			0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,					  0.0f, 1.0f*scaleY, /* top-left	*/				0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,					  0.0f, 0.0f, /* bottom-left	*/					0.0f, 0.0f, -1.0f,
		 // front face (CCW winding)
		 -1.0f, -1.0f,  1.0f,					  0.0f, 0.0f,										0.0f, 0.0f, 1.0f,
		  1.0f, -1.0f,  1.0f,					  1.0f*scaleX, 0.0f,								0.0f, 0.0f, 1.0f,
		  1.0f,  1.0f,  1.0f,					  1.0f*scaleX, 1.0f*scaleY,							0.0f, 0.0f, 1.0f,
		  1.0f,  1.0f,  1.0f,					  1.0f*scaleX, 1.0f*scaleY,							0.0f, 0.0f, 1.0f,
		 -1.0f,  1.0f,  1.0f,					  0.0f, 1.0f*scaleY,								0.0f, 0.0f, 1.0f,
		 -1.0f, -1.0f,  1.0f,					  0.0f, 0.0f,										0.0f, 0.0f, 1.0f,
		 // left face (CCW)
		 -1.0f, -1.0f, -1.0f,					  0.0f, 0.0f,										-1.0f, 0.0f, 0.0f,
		 -1.0f, -1.0f,  1.0f,					  1.0f*scaleZ, 0.0f,								-1.0f, 0.0f, 0.0f,
		 -1.0f,  1.0f,  1.0f,					  1.0f*scaleZ, 1.0f*scaleY,							-1.0f, 0.0f, 0.0f,
		 -1.0f,  1.0f,  1.0f,					  1.0f*scaleZ, 1.0f*scaleY,							-1.0f, 0.0f, 0.0f,
		 -1.0f,  1.0f, -1.0f,					  0.0f, 1.0f*scaleY,								-1.0f, 0.0f, 0.0f,
		 -1.0f, -1.0f, -1.0f,					  0.0f, 0.0f,										-1.0f, 0.0f, 0.0f,
		 // right face (CCW)
		  1.0f, -1.0f,  1.0f,					  0.0f, 0.0f,										1.0f, 0.0f, 0.0f,
		  1.0f, -1.0f, -1.0f,					  1.0f*scaleZ, 0.0f, 								1.0f, 0.0f, 0.0f,
		  1.0f,  1.0f, -1.0f,					  1.0f*scaleZ, 1.0f*scaleY,							1.0f, 0.0f, 0.0f,
		  1.0f,  1.0f, -1.0f,					  1.0f*scaleZ, 1.0f*scaleY,							1.0f, 0.0f, 0.0f,
		  1.0f,  1.0f,  1.0f,					  0.0f, 1.0f*scaleY, 								1.0f, 0.0f, 0.0f,
		  1.0f, -1.0f,  1.0f,					  0.0f, 0.0f, 										1.0f, 0.0f, 0.0f,
		  // bottom face (CCW)					      
		  -1.0f, -1.0f, -1.0f,					  0.0f, 0.0f,										0.0f, -1.0f, 0.0f,
		   1.0f, -1.0f, -1.0f,					  1.0f*scaleX, 0.0f, 								0.0f, -1.0f, 0.0f,
		   1.0f, -1.0f,  1.0f,					  1.0f*scaleX, 1.0f*scaleZ, 						0.0f, -1.0f, 0.0f,
		   1.0f, -1.0f,  1.0f,					  1.0f*scaleX, 1.0f*scaleZ, 						0.0f, -1.0f, 0.0f,
		  -1.0f, -1.0f,  1.0f,					  0.0f, 1.0f*scaleZ, 								0.0f, -1.0f, 0.0f,
		  -1.0f, -1.0f, -1.0f,					  0.0f, 0.0f,										0.0f, -1.0f, 0.0f,
		  // top face (CCW)
		  -1.0f,  1.0f,  1.0f,					  0.0f, 0.0f,										0.0f, 1.0f, 0.0f,
		   1.0f,  1.0f,  1.0f,					  1.0f*scaleX, 0.0f,								0.0f, 1.0f, 0.0f,
		   1.0f,  1.0f, -1.0f,					  1.0f*scaleX, 1.0f*scaleZ,							0.0f, 1.0f, 0.0f,
		   1.0f,  1.0f, -1.0f,					  1.0f*scaleX, 1.0f*scaleZ,							0.0f, 1.0f, 0.0f,
		  -1.0f,  1.0f, -1.0f,					  0.0f, 1.0f*scaleZ, 								0.0f, 1.0f, 0.0f,
		  -1.0f,  1.0f,  1.0f,					  0.0f, 0.0f,										0.0f, 1.0f, 0.0f
	};
}

glm::mat4* Cuboid::getModelMatrix()
{
	//generateModelMatrix();
	return &modelMatrix;
}

void Cuboid::translate()
{
	//if (posX == 0.f && posY == 0.f && posZ == 0.f) return;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY, posZ));
}

void Cuboid::rotate()
{
	//if (rotAngle == 0.f) return;
	modelMatrix = glm::rotate(modelMatrix,glm::radians(rotAngle),glm::vec3(rotX,rotY,rotZ));
}

void Cuboid::rotate2()
{
	//if (rotAngle2 == 0.f) return;
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotAngle2), glm::vec3(rotX2, rotY2, rotZ2));
}

void Cuboid::scale()
{
	if (scaleX == 1.f && scaleY == 1.f && scaleZ == 1.f) return;
	modelMatrix = glm::scale(modelMatrix,glm::vec3(scaleX,scaleY,scaleZ));
}

void Cuboid::generateModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	translate();
	rotate();
	rotate2();
	scale();
	
	
}

GLfloat * Cuboid::getVertexTextureArrayPointer()
{
	return &vertexTextureNormal[0];
}


GLuint Cuboid::getVertexTextureArraySize()
{
	return vertexTextureNormal.size();
}

void Cuboid::setScale(GLfloat x, GLfloat y, GLfloat z)
{
	if (x == scaleX && y == scaleY && z == scaleZ) return;
	scaleX = x; scaleY = y; scaleZ = z;
	//glm::scale(modelMatrix, glm::vec3(x, y, z));
	generateModelMatrix();
}

void Cuboid::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	if (x == posX && y == posY && z == posZ) return;
	posX = x; posY = y; posZ = z;
	//glm::translate(modelMatrix, glm::vec3(x, y, z));
	generateModelMatrix();
}

void Cuboid::setRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
{
	if (x == rotX && y == rotY && z == rotZ && rotAngle == angle) return;
	rotX = x; rotY = y; rotZ = z; rotAngle = angle;
	//glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
	generateModelMatrix();
}

void Cuboid::setRotation2(GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
{
	if (rotX2 == x && rotY2 == y && rotZ2 == z && rotAngle2 == angle) return;
	rotX2 = x; rotY2 = y; rotZ2 = z; rotAngle2 = angle;
	generateModelMatrix();
}

void Cuboid::setAll(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat rotAngle)
{
	/*if (this->posX == posX && this->posY == posY && this->posZ == posZ
		&& this->scaleX == scaleX && this->scaleY == scaleY && this->scaleZ == scaleZ
		&& this->rotX == rotX && this->rotY == rotY && this->rotZ == rotZ && this->rotAngle == rotAngle) return;
	*/
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->rotAngle = rotAngle;

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
	cubeTexture = new Texture2D(fname);
}

void Cuboid::setTexture(std::vector<std::string> fnames, GLuint type)
{
	cubeTexture = new CubemapTexture(fnames);
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
	return *cubeTexture;
}
