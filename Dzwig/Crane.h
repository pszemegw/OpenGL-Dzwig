#pragma once
#include "CraneBase.h"
#include "CraneTop.h"
#include "CraneTower.h"
class Crane
{
	Cuboid segment;

	CraneBase* base;
	CraneTower* tower;
	CraneTop* top;

	Texture2D* segmentTexture;
	Texture2D* ropeTexture;
	Texture2D* concreteTexture;

	GLfloat posX, posY, posZ;
	GLfloat towerHeight, towerWidth, armLength;
	GLfloat segmentScale;

	GLuint VAO, VBO;

public:
	Crane(GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f, GLfloat height = 30.f, GLfloat width = 1.f, GLfloat length = 15.f, GLfloat scale = .03f,
		std::string segTex = "metal.png", std::string ropeTex = "black.png", std::string concTex = "concrete.jpg");

	void draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h);


};

