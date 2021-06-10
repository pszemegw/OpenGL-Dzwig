#include "CraneTop.h"

void CraneTop::arm()
{
	GLfloat length2 = length - width / 2;

	segment.setAll(posX - length, posY, posZ - width / 2, length /*+ width/2*/, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(posX - length, posY, posZ + width / 2, length /*+ width / 2*/, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(posX - length2, posY + width * glm::sqrt(3) / 2, posZ, length2, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());

	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY, posZ, segmentScale, segmentScale, width / 2);
		segmentTrans.push_back(segment.getModelMatrix());
	}
	segment.setAll(posX - 2 * length, posY, posZ, segmentScale, segmentScale, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());

	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY + width * sqrt(3) / 4, posZ + width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 60);
		segmentTrans.push_back(segment.getModelMatrix());
	}
	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY + width * sqrt(3) / 4, posZ - width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 120);
		segmentTrans.push_back(segment.getModelMatrix());
	}


	for (int i = 1; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - i * width, posY + width*sqrt(3)/4, posZ, width*sqrt(7) / 4, segmentScale, segmentScale,0,0,1,-glm::degrees(glm::atan(sqrt(3)/2)));
		if (i % 2) segment.setRotation(0, 0, 1, glm::degrees(glm::atan(sqrt(3) / 2)));
		segmentTrans.push_back(segment.getModelMatrix());
	}

	segment.setAll(posX - 2 * length + width / 2, posY + width * sqrt(3) / 4, posZ - width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 120);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(posX - 2 * length + width / 2, posY + width * sqrt(3) / 4, posZ + width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 60);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setRotation2(0, 1, 0, 0);


	GLfloat h = sqrt(2)* width * glm::tan(glm::radians(75.f)) / 2;
	GLfloat h2 = h - width * sqrt(3) / 2;
	GLfloat lineLength = glm::sqrt(h2*h2 + length * length);


	segment.setAll(posX, posY + h / 2, posZ, segmentScale, h / 2, segmentScale, 0, 0, 1,/*glm::degrees(glm::atan(h2/2*(length-width)))*/0);
	segmentTrans.push_back(segment.getModelMatrix());


	// zwienczenie
	GLfloat alpha = glm::radians(75.f);
	segment.setAll(posX - width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ + width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 45);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(posX + width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ + width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 135);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(posX + width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ - width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 225);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(posX - width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ - width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 315);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setRotation2(0, 1, 0, 0);

	//tyl

	segment.setAll(posX + length / 2 - width / 2, posY, posZ, length / 2, segmentScale, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());
}

void CraneTop::lines()
{
	GLfloat h = sqrt(2)* width * glm::tan(glm::radians(75.f)) / 2;
	GLfloat h2 = h - width * sqrt(3) / 2;
	GLfloat lineLength = glm::sqrt(h2*h2 + length * length);
	GLfloat length2 = length - width / 2;
	//liny

	GLfloat x = glm::degrees(glm::atan(h2 / (2 * length2 + width / 2)));
	segment.setAll(
		posX - length2, posY + width * sqrt(3) / 2 + h2 / 2, posZ,
		length2, segmentScale / 5, segmentScale / 5,
		0, 0, 1, x
	);
	segmentTrans.push_back(segment.getModelMatrix());

	lineLength = glm::sqrt(h*h + (length - width / 2) / 2 * (length - width / 2) / 2);
	x = -glm::degrees(glm::atan(h / (length - width / 2)));
	segment.setAll(
		posX + length / 2, posY + h / 2, posZ,
		lineLength, segmentScale / 5, segmentScale / 5,
		0, 0, 1, x
	);
	segmentTrans.push_back(segment.getModelMatrix());

}

CraneTop::CraneTop(GLfloat w, GLfloat scale, GLfloat x, GLfloat y, GLfloat z, Texture2D * texSeg, Texture2D * texRope, Texture2D * texConcrete, GLuint vao)
{
	width = w; segmentScale = scale; posX = x; posY = y; posZ = z;
	segmentTexture = texSeg; ropeTexture = texRope; concreteTexture = texConcrete; VAO = vao;
	arm();
	lines();
	
	// obciazenie

	segment.setAll(posX + length / 2 - width / 2, posY, posZ, 2 * width, width*sqrt(3) / 2, width / 4);
	segmentTrans.push_back(segment.getModelMatrix());
}

void CraneTop::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h, GLfloat rot)
{
	glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 1, 0));
	glm::mat4 trans;
	glm::mat4 view = c->getWorldToViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segmentTexture->getTextureID());

	for (int i = 0; i < segmentTrans.size()-3; ++i)
	{
		trans = projection * view * rotMat * segmentTrans[i];
		glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindTexture(GL_TEXTURE_2D, ropeTexture->getTextureID());
	trans = projection * view * rotMat * segmentTrans[segmentTrans.size()-3];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	trans = projection * view * rotMat * segmentTrans[segmentTrans.size() - 2];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, concreteTexture->getTextureID());
	trans = projection * view * rotMat * segmentTrans[segmentTrans.size() - 1];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}


