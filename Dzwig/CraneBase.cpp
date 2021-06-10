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
	//segment->setTexture(textureFileName);
	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		segment->getVertexTextureArraySize() * sizeof(GLfloat),
		segment->getVertexTextureArrayPointer(),
		GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);*/


	segmentTrans.push_back(segment->getModelMatrix());
	//segment->setPosition(0, segment->getPosition()[1] + height/2, 0);
	//segmentTrans.push_back(segment->getModelMatrix());
	//segment->setPosition(0, segment->getPosition()[1] + height/2, 0);
	//segmentTrans.push_back(segment->getModelMatrix());
}

void CraneBase::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	glm::mat4 trans;
	glm::mat4 view = c->getWorldToViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		trans = projection * view * segmentTrans[i];
		glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}
