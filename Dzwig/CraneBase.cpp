#include "CraneBase.h"

CraneBase::CraneBase(
	GLfloat w, 
	GLfloat h, 
	Texture2D* tex, 
	GLfloat x, 
	GLfloat y, 
	GLfloat z,
	GLuint vao) : width(w), height(h), posX(x), posY(y), posZ(z), VAO(vao)
{
	segment = new Cuboid(posX, posY+height, posZ, width/2, height, width/2);
	texture = tex;
	segmentTrans.push_back(segment->getModelMatrix());
}

void CraneBase::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	s->setMat4("projection", *(c->getProjectionMatrix()));
	s->setMat4("view", c->getWorldToViewMatrix());

	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		s->setMat4("model", segmentTrans[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}
