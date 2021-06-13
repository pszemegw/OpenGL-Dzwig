#include "CraneTower.h"

CraneTower::CraneTower(
	GLfloat h, 
	GLfloat w, 
	GLfloat scale, 
	Texture2D* tex , 
	GLfloat x , GLfloat y , GLfloat z, GLuint vao)
{
	height = h; width = w; segmentScale = scale; segmentTexture = tex;
	posX = x; posY = y; posZ = z; VAO = vao;

	glGenBuffers(4, VBOs);
	glGenVertexArrays(4, VAOs);

	GLuint j = 0;
	index[0] = j;

	segment.setAll(posX, posY, posZ, width/4, segmentScale, 3*width, 0, 1, 0, 45);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setAll(posX, posY, posZ, width/4, segmentScale, 3*width, 0, 1, 0, 135);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();

	j += 2;
	index[1] = j;

	generateVO(&VAOs[0], &VBOs[0], &segment);

	// pionowe belki

	segment.setAll(posX-width/2, posY + height/2, posZ-width/2, segmentScale * 2, height/2, segmentScale * 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setPosition(posX -width / 2, posY +height / 2, posZ+ width / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setPosition(posX+width / 2, posY + height / 2, posZ + width / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setPosition(posX+width / 2, posY+ height / 2, posZ -width / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();

	j += 4;
	index[2] = j;

	generateVO(&VAOs[1], &VBOs[1], &segment);

	// poziome belki
	GLfloat hh = posY;
	GLfloat rotx = 0.f, roty = 1.f, rotz = 0.f, rotangle = 0.f,
		scalex = width / 2, scaley = segmentScale, scalez = segmentScale,
		posx = posX, posy = h, posz = posZ;

	
	for (int i = 0; i < 4 * (1+(height / width)); ++i, ++j)
	{	
		posy = hh;
		if (i % 4 == 0)
		{
			posx = posX;
			posz = posZ + width/2;
			rotangle = 0.f;
		}
		if (i % 4 == 1)
		{
			posx = posX;
			posz = posZ -width/2;
		}
		if (i % 4 == 2)
		{
			posx = posX + width/2;
			posz = posZ;
			rotangle = 90.f;
		}
		if (i % 4 == 3)
		{
			posx = posX-width/2;
			posz = posZ;
			hh += width;
		}
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}

	index[3] = j+1;
	segment.generateVertices();
	generateVO(&VAOs[2], &VBOs[2], &segment);

	// poprzeczne
	// przod
	hh = posY + width/2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 0.f, roty = 0.f, rotz = 1.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = posX, posy = hh, posz = posZ + width/2;
		if (i % 2 == 0)
			rotangle = 45.f;
		if (i % 2 == 1)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segmentTrans.push_back(*(segment.getModelMatrix()));
		hh += width;
	}

	// tyl

	hh = posY + width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 0.f, roty = 0.f, rotz = 1.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = posX, posy = hh, posz = posZ-width / 2;
		if (i % 2 == 1)
			rotangle = 45.f;
		if (i % 2 == 0)			
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);

		segmentTrans.push_back(*(segment.getModelMatrix()));
		hh += width;
	}

	//bok -x

	hh = posY + width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 1.f, roty = 0.f, rotz = 0.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = posX-width/2, posy = hh, posz = posZ;
		if (i % 2 == 0)
			rotangle = 45.f;
		if (i % 2 == 1)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segment.setRotation2(0, 1, 0, 90);
		segmentTrans.push_back(*(segment.getModelMatrix()));
		hh += width;
	}

	// bok +x

	hh = posY + width / 2;
	for (int i = 0; i < height / width; ++i)
	{
		rotx = 1.f, roty = 0.f, rotz = 0.f, rotangle = 0.f,
			scalex = glm::sqrt(2)*width / 2, scaley = segmentScale, scalez = segmentScale,
			posx = posX + width / 2, posy = hh, posz = posZ;
		if (i % 2 == 1)
			rotangle = 45.f;
		if (i % 2 == 0)
			rotangle = 135.f;
		segment.setAll(posx, posy, posz, scalex, scaley, scalez, rotx, roty, rotz, rotangle);
		segment.setRotation2(0, 1, 0, -90);
		segmentTrans.push_back(*(segment.getModelMatrix()));
		hh += width;
	}

	segment.generateVertices();

	generateVO(&VAOs[3], &VBOs[3], &segment);

}

void CraneTower::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	glm::mat4 trans;
	glm::mat4 projection = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segmentTexture->getTextureID());

	s->setMat4("projection", *(c->getProjectionMatrix()));
	s->setMat4("view", c->getWorldToViewMatrix());
	//s->setFloat("material.shininess", 256.0f);
	glBindVertexArray(VAOs[0]);
	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		if (i == 2) glBindVertexArray(VAOs[1]);
		if (i == 6) glBindVertexArray(VAOs[2]);
		if (i >= index[3]) glBindVertexArray(VAOs[3]);
		s->setMat4("model", segmentTrans[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void CraneTower::generateVO(GLuint* vao, GLuint* vbo, Cuboid* segment)
{
	Renderer::generateVO(vao, vbo, segment);
}
