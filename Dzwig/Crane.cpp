#include "Crane.h"

void Crane::drawLights()
{
	

	for (GLfloat h = towerWidth; h <= towerHeight; h += towerWidth * 6)
		lights->addLight(glm::vec3(posX, h, posZ), 1.f, 0.1f, 0.9f,
			glm::vec3(1.0f, 0.f, 0.f), glm::vec3(.8f, .8f, .8f), glm::vec3(1.f, 1.f, 1.f));

	lights->addLight(glm::vec3(posX, towerHeight + segmentScale + towerWidth * glm::sqrt(2)*glm::tan(glm::radians(75.f)), posZ), 1.f, 0.1f, 0.9f,
		glm::vec3(1.0f, 0.f, 0.f), glm::vec3(.8f, .8f, .8f), glm::vec3(1.f, 1.f, 1.f));


	topLightsFirstIndex = lights->getNumberOfPointLights();

	lights->addLight(glm::vec3(posX + towerWidth / 2 + towerHeight / 2, towerHeight + posY, posZ), 1.f, 0.1f, 0.9f,
		glm::vec3(1.0f, 0.f, 0.f), glm::vec3(.8f, .8f, .8f), glm::vec3(1.f, 1.f, 1.f));

	for (GLfloat x = posX; x >= posX - towerHeight; x -= towerWidth*6)
		lights->addLight(glm::vec3(x, towerHeight + posY + towerWidth*sqrt(3)/2, posZ), 1.f, 0.1f, 0.9f,
			glm::vec3(1.0f, 0.f, 0.f), glm::vec3(.8f, .8f, .8f), glm::vec3(1.f, 1.f, 1.f));

	topLightNum = lights->getNumberOfPointLights() - topLightsFirstIndex;
}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	posX = x; posY = y; posZ = z; towerHeight = height; towerWidth = width; armLength = length;
	segmentScale = scale;
	segmentTexture = new Texture2D(segTex);
	ropeTexture = new Texture2D(ropeTex);
	concreteTexture = new Texture2D(concTex);

	base = new CraneBase(towerWidth, towerWidth*0.5f, concreteTexture, posX, posY, posZ, segmentScale, VAO);
	tower = new CraneTower(towerHeight, towerWidth, segmentScale, segmentTexture, posX, posY, posZ, VAO);
	top = new CraneTop(towerWidth, segmentScale, towerHeight/2, posX, posY + towerHeight + towerWidth, posZ, segmentTexture, ropeTexture, concreteTexture, VAO);

	segment.setAll(posX - towerWidth, posY + towerHeight, posZ, towerWidth*2, towerWidth , towerWidth);
	
}

void Crane::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	base->draw(s, c, w, h);
	tower->draw(s, c, w, h);
	top->draw(s, c, w, h, rotationAngle);

	s->setMat4("projection", *(c->getProjectionMatrix()));
	s->setMat4("view", c->getWorldToViewMatrix());
	s->setMat4("model", *(segment.getModelMatrix()));
	glBindTexture(GL_TEXTURE_2D, ropeTexture->getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Crane::rotateCrane(GLfloat angleDeg)
{
	rotationAngle += angleDeg;

	glm::vec3 a;
	for (int i = topLightsFirstIndex; i < topLightsFirstIndex + topLightNum + 1; ++i)
	{
		a = lights->getPointLightPos(i);
		a.x -= posX;
		a.z -= posZ;
		GLfloat r = glm::sqrt(a.x*a.x + a.z*a.z);
		GLfloat angle = -rotationAngle;
		if (a.x < 0) angle += 180;

		glm::vec3 b(
			r*glm::cos(glm::radians(angle)),
			a.y,
			r*sin(glm::radians(angle))
			);
		b.x += posX;
		b.z += posZ;
		lights->updatePointLightPos(i, b);
	}
}

void Crane::moveHookX(GLfloat dx)
{
	top->moveHookX(dx);
}

void Crane::moveHookY(GLfloat dy)
{
	top->moveHookY(dy);
}

void Crane::setLights(Light * l)
{
	lights = l;
	drawLights();
}




