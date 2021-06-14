#ifndef _CRANE_H_
#define _CRANE_H_
#pragma once
#include "CraneBase.h"
#include "CraneTop.h"
#include "CraneTower.h"
#include "Light.h"
class Crane
{
	Cuboid segment;

	Light* lights;

	CraneBase* base;
	CraneTower* tower;
	CraneTop* top;

	Texture2D* segmentTexture;
	Texture2D* ropeTexture;
	Texture2D* concreteTexture;

	GLfloat posX, posY, posZ;
	GLfloat towerHeight, towerWidth, armLength;
	GLfloat segmentScale;

	std::vector<glm::mat4> segmentTrans;

	GLfloat rotationAngle = 0.f;

	GLuint VAO, VBO;

	GLuint topLightsFirstIndex;
	GLuint topLightNum;
	
	GLboolean isLampOn[4];

	void addLights();

	void addLamps();

public:
	Crane(GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f, GLfloat height = 30.f, GLfloat width = 1.f, GLfloat length = 15.f, GLfloat scale = .03f,
		std::string segTex = "metal2.png", std::string ropeTex = "c.png", std::string concTex = "concrete.jpg");

	void draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h);

	

	void rotateCrane(GLfloat angleDeg);
	void moveHookX(GLfloat dx);
	void moveHookY(GLfloat dy);

	void setLights(Light* l);
	void toggleLamp(GLuint i);
 
};

#endif