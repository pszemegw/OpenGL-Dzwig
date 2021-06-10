#include "Crane.h"

Crane::Crane(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat width, GLfloat length, GLfloat scale, std::string segTex, std::string ropeTex, std::string concTex)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		segment.getVertexTextureArraySize() * sizeof(GLfloat),
		segment.getVertexTextureArrayPointer(),
		GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	posX = x; posY = y; posZ = z; towerHeight = height; towerWidth = width; armLength = length;
	segmentScale = scale;
	segmentTexture = new Texture2D(segTex);
	ropeTexture = new Texture2D(ropeTex);
	concreteTexture = new Texture2D(concTex);

	base = new CraneBase(towerWidth*3.f, towerWidth*0.5f, concreteTexture, posX, posY, posZ, VAO);
	tower = new CraneTower(towerHeight, towerWidth, segmentScale, segmentTexture, posX, posY, posZ, VAO);
	top = new CraneTop(towerWidth, segmentScale, posX, posY + towerHeight, posZ, segmentTexture, ropeTexture, concreteTexture, VAO);
}

void Crane::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	base->draw(s, c, w, h);
	tower->draw(s, c, w, h);
	top->draw(s, c, w, h, rotationAngle);
}

void Crane::rotateCrane(GLfloat angleDeg)
{
	rotationAngle += angleDeg;
}
