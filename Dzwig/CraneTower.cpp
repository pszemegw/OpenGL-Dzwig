#include "CraneTower.h"

CraneTower::CraneTower(std::string textureFileName)
{
	segment.setTexture(textureFileName);

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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// pionowe belki

	segment.setAll(-width/2, height/2, -width/2, segmentScale * 2, height/2, segmentScale * 2);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setPosition(-width / 2, height / 2, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setPosition(width / 2, height / 2, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setPosition(width / 2, height / 2, -width / 2);
	segmentTrans.push_back(segment.getModelMatrix());

	// poziome belki
	GLfloat h = 0.0f;
	GLfloat rotx = 0.f, roty = 1.f, rotz = 0.f, rotangle = 0.f,
		scalex = width / 2, scaley = segmentScale, scalez = segmentScale,
		posx = 0.f, posy = h, posz = 0.f;

	
	for (int i = 0; i < 4 * (1+(height / width)); ++i)
	{	
		posy = h;
		if (i % 4 == 0)
		{
			posx = 0.f;
			posz = width/2;
			rotangle = 0.f;
		}
		if (i % 4 == 1)
		{
			posx = 0.0f;
			posz = -width/2;
		}
		if (i % 4 == 2)
		{
			posx = width/2;
			posz = 0.f;
			rotangle = 90.f;
		}
		if (i % 4 == 3)
		{
			posx = -width/2;
			posz = 0.f;
			h += width;
		}
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(segment.getModelMatrix());
		
		
	}

	// poprzeczne
	// przod
	h = width/2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 0.f, roty = 0.f, rotz = 1.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = 0.f, posy = h, posz = width/2;
		if (i % 2 == 0)
			rotangle = 45.f;
		if (i % 2 == 1)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(segment.getModelMatrix());
		h += width;
	}

	// tyl

	h = width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 0.f, roty = 0.f, rotz = 1.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = 0.f, posy = h, posz = -width / 2;
		if (i % 2 == 1)
			rotangle = 45.f;
		if (i % 2 == 0)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(segment.getModelMatrix());
		h += width;
	}

	//bok -x

	h = width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 1.f, roty = 0.f, rotz = 0.f, rotangle = 0.f,
			scalex = segmentScale, scaley = segmentScale, scalez = glm::sqrt(2)*width / 2,
			posx = -width/2, posy = h, posz = 0.f;
		if (i % 2 == 0)
			rotangle = 45.f;
		if (i % 2 == 1)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(segment.getModelMatrix());
		h += width;
	}

	// bok +x

	h = width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 1.f, roty = 0.f, rotz = 0.f, rotangle = 0.f,
			scalex = segmentScale, scaley = segmentScale, scalez = glm::sqrt(2)*width / 2,
			posx = width / 2, posy = h, posz = 0.f;
		if (i % 2 == 1)
			rotangle = 45.f;
		if (i % 2 == 0)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(segment.getModelMatrix());
		h += width;
	}

	
	
}

void CraneTower::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	glm::mat4 trans;
	glm::mat4 view = c->getWorldToViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segment.getTexture().getTextureID());

	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		trans = projection * view * segmentTrans[i];
		glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


}
