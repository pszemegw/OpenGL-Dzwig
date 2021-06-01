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

using namespace std;

class Cuboid
{
	GLfloat scaleX, scaleY, scaleZ; // skala
	GLfloat posX, posY, posZ; // pozycja/przesuniecie
	GLfloat rotX, rotY, rotZ; // wektor wyznaczajacy os obrotu
	GLfloat rotAngle; // kat obrotu (stopnie)
	glm::mat4 modelMatrix;
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	vector<GLfloat> textureCoord;
	vector<GLfloat> vertexTexture;

	Texture cubeTexture;

	void translate();
	void rotate();
	void scale();
	void generateModelMatrix();

	



public:
	Cuboid(
		GLfloat posX = 0.f, GLfloat posY = 0.f, GLfloat posZ = 0.f, 
		GLfloat scaleX=1.0f, GLfloat scaleY=1.0f, GLfloat scaleZ=1.0f,
		GLfloat rotX=1.f, GLfloat rotY=1.f, GLfloat rotZ=1.f, GLfloat rotAngle = 0.f);
	void generateVertices();

	glm::mat4 getModelMatrix();

	GLfloat* getVertexArrayPointer();
	GLfloat* getVertexTextureArrayPointer();

	GLuint getVertexArraySize();
	GLuint getVertexTextureArraySize();


	void setScale(GLfloat x, GLfloat y, GLfloat z);
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

	std::vector<GLfloat> getScale();
	std::vector<GLfloat> getPosition();
	std::vector<GLfloat> getRotation();

	void setTexture(std::string fname, GLuint type = GL_TEXTURE_2D);
	void setTexture(std::vector<std::string> fnames, GLuint type = GL_TEXTURE_CUBE_MAP);

	void divideTextureCoords(GLfloat div);

	Texture getTexture();


	

};