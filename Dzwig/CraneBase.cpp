#include "CraneBase.h"

CraneBase::CraneBase(
	GLfloat w, 
	GLfloat h, 
	Texture2D* tex, 
	GLfloat x, 
	GLfloat y, 
	GLfloat z,
	GLfloat segmentScale,
	GLuint vao) : width(w), height(h), posX(x), posY(y), posZ(z), VAO(vao)
{
	segment = new Cuboid(posX, posY+height, posZ, width/2, height, width/2);
	texture = tex;


	segment->setAll(posX, posY + segmentScale + height / 3, posZ - width * 1.3f, width / 2, height / 3, width * 2, 0, 1, 0, 90);
	segment->generateVertices();
	
	segmentTrans.push_back(segment->getModelMatrix());

	segment->setAll(posX, posY + segmentScale + height / 3, posZ + width * 1.3f, width / 2, height / 3, width * 2, 0, 1, 0, 90);
	segmentTrans.push_back(segment->getModelMatrix());


	segment->setAll(posX + width * 1.3f, posY + segmentScale + height, posZ, width / 2, height / 3, width * 2);
	segmentTrans.push_back(segment->getModelMatrix());
	segment->setAll(posX + width * 1.3f, posY + segmentScale + 5*height/3 + segmentScale, posZ, width / 2, height / 3, width * 2);
	segmentTrans.push_back(segment->getModelMatrix());
	segment->setAll(posX - width*1.3f, posY + segmentScale + height, posZ, width / 2, height/3, width * 2);
	segmentTrans.push_back(segment->getModelMatrix());
	segment->setAll(posX - width * 1.3f, posY + segmentScale + 5*height/3 + segmentScale, posZ, width / 2, height / 3, width * 2);
	segmentTrans.push_back(segment->getModelMatrix());

	generateVO(&VAO0, &VBO0, segment);
}

void CraneBase::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	//ShaderProgram shader("instance.vert","gl_05.frag");
	//shader.Use();
	glBindVertexArray(VAO0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	s->setMat4("projection", *(c->getProjectionMatrix()));
	s->setMat4("view", c->getWorldToViewMatrix());
	//shader.setMat4("projection", *(c->getProjectionMatrix()));
	//shader.setMat4("view", c->getWorldToViewMatrix());
	

	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		//shader.setMat4(("model[" + std::to_string(i) + "]"), segmentTrans[i]);
		s->setMat4("model", segmentTrans[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, segmentTrans.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//s->Use();

}



void CraneBase::generateVO(GLuint* vao, GLuint* vbo, Cuboid* segment)
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
