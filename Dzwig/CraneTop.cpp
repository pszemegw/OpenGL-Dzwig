#include "CraneTop.h"

void CraneTop::arm()
{
	index[0] = j;
	GLfloat length2 = length - width / 2;

	segment.setAll(posX - length, posY, posZ - width / 2, length /*+ width/2*/, segmentScale, segmentScale);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setAll(posX - length, posY, posZ + width / 2, length /*+ width / 2*/, segmentScale, segmentScale);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[0], &VBOs[0], &segment);
	j += 2; index[1] = j;

	segment.setAll(posX - length2, posY + width * glm::sqrt(3) / 2, posZ, length2, segmentScale, segmentScale);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.generateVertices();

	generateVO(&VAOs[1], &VBOs[1], &segment);
	j += 1; index[2] = j;

	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY, posZ, segmentScale, segmentScale, width / 2);
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}
	segment.setAll(posX - 2 * length, posY, posZ, segmentScale, segmentScale, width / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	

	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY + width * sqrt(3) / 4, posZ + width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 60);
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}
	for (int i = 0; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - width / 2 - i * width, posY + width * sqrt(3) / 4, posZ - width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 120);
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}
	segment.generateVertices();

	generateVO(&VAOs[2], &VBOs[2], &segment);
	j += 6 * length / width - 2; index[3] = j;

	for (int i = 1; i < 2 * length / width - 1; ++i)
	{
		segment.setAll(posX - i * width, posY + width*sqrt(3)/4, posZ, width*sqrt(7) / 4, segmentScale, segmentScale,0,0,1,-glm::degrees(glm::atan(sqrt(3)/2)));
		if (i % 2) segment.setRotation(0, 0, 1, glm::degrees(glm::atan(sqrt(3) / 2)));
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}
	segment.generateVertices();

	generateVO(&VAOs[3], &VBOs[3], &segment);
	j += 2*length/width - 2; index[4] = j;

	segment.setAll(posX - 2 * length + width / 2, posY + width * sqrt(3) / 4, posZ - width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 120);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setAll(posX - 2 * length + width / 2, posY + width * sqrt(3) / 4, posZ + width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 60);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setRotation2(0, 1, 0, 0);

	segment.generateVertices();
	generateVO(&VAOs[4], &VBOs[4], &segment);
	j += 2 ; index[5] = j;



	GLfloat h = sqrt(2)* width * glm::tan(glm::radians(75.f)) / 2;
	GLfloat h2 = h - width * sqrt(3) / 2;
	GLfloat lineLength = glm::sqrt(h2*h2 + length * length);


	segment.setAll(posX, posY + h / 2, posZ, segmentScale, h / 2, segmentScale, 0, 0, 1,/*glm::degrees(glm::atan(h2/2*(length-width)))*/0);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	
	segment.generateVertices();
	generateVO(&VAOs[5], &VBOs[5], &segment);
	j += 1; index[6] = j;


	// zwienczenie
	GLfloat alpha = glm::radians(75.f);
	segment.setAll(posX - width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ + width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 45);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.setAll(posX + width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ + width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 135);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.setAll(posX + width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ - width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 225);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.setAll(posX - width / 4, posY + width * glm::sqrt(2)*glm::tan(alpha) / 4, posZ - width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 315);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.setRotation2(0, 1, 0, 0);

	segment.generateVertices();
	generateVO(&VAOs[6], &VBOs[6], &segment);
	j += 4; index[7] = j;

	//tyl

	segment.setAll(posX + length / 2, posY, posZ, length / 2 + width/2, segmentScale, width / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[7], &VBOs[7], &segment);
	j += 1; index[8] = j;

	for (int i = 0; i < length / width; ++i)
	{
		segment.setAll(posX + (i+1)*width, posY+segmentScale + width * sqrt(3) / 8, posZ - width/2, segmentScale, segmentScale+ width * sqrt(3) / 8, segmentScale);
		segmentTrans.push_back(*(segment.getModelMatrix()));
		segment.setAll(posX + (i+1) * width, posY + segmentScale + width * sqrt(3) / 8, posZ + width / 2, segmentScale, segmentScale + width * sqrt(3) / 8, segmentScale);
		segmentTrans.push_back(*(segment.getModelMatrix()));
	}

	segment.generateVertices();
	generateVO(&VAOs[8], &VBOs[8], &segment);
	j += 2*length/width; index[9] = j;

	segment.setAll(posX + length/2, posY + segmentScale + width * sqrt(3) / 4, posZ - width / 2, segmentScale + length/2, segmentScale, segmentScale);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.setAll(posX + length / 2, posY + segmentScale + width * sqrt(3) / 4, posZ + width / 2, segmentScale + length / 2, segmentScale, segmentScale);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[9], &VBOs[9], &segment);
	j += 2; index[10] = j;
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
		length2, segmentScale / 2, segmentScale / 2,
		0, 0, 1, x
	);
	segmentTrans.push_back(*(segment.getModelMatrix()));
	segment.generateVertices();
	generateVO(&VAOs[10], &VBOs[10], &segment);
	j += 1; index[11] = j;

	x = glm::degrees(glm::atan(h2 / (length2 + width / 2)));
	segment.setAll(
		posX - length2/2, posY + width * sqrt(3) / 2 + h2 / 2, posZ,
		length2/2, segmentScale / 2, segmentScale / 2,
		0, 0, 1, x
	);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[11], &VBOs[11], &segment);
	j += 1; index[12] = j;

	lineLength = glm::sqrt(h*h + (length + segmentScale + width/2 ) * (length + segmentScale + width/2));
	x = -glm::degrees(glm::atan(h / (length + segmentScale + width / 2)));
	segment.setAll(
		posX + lineLength/2 - segmentScale*2, posY + h / 2, posZ,
		lineLength/2, segmentScale / 2, segmentScale / 2,
		0, 0, 1, x
	);

	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[12], &VBOs[12], &segment);
	j += 1; index[13] = j;
}

void CraneTop::moveHookX(GLfloat dx)
{
	hookPosX += dx;
	if (hookPosX < posX - 2*length + width) hookPosX = posX - 2*length + width;
	else if (hookPosX > posX - width) hookPosX = posX - width;

}

void CraneTop::moveHookY(GLfloat dy)
{
	hookLength += dy;
	if (hookLength <= 1.0f) hookLength = 1.0f;
	else if (hookLength >= length) hookLength = length;

}

CraneTop::CraneTop(GLfloat w, GLfloat scale, GLfloat l, GLfloat x, GLfloat y, GLfloat z, Texture2D * texSeg, Texture2D * texRope, Texture2D * texConcrete, GLuint vao)
{

	width = w; segmentScale = scale; posX = x; posY = y; posZ = z; length = l;
	segmentTexture = texSeg; ropeTexture = texRope; concreteTexture = texConcrete; VAO = vao;
	hookPosX = posX - length + width;

	arm();
	lines();
	
	segment.setAll(posX, posY - segmentScale, posZ, width/3, segmentScale, width/2);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.setAll(posX, posY - segmentScale, posZ, segmentScale / 3, hookLength, segmentScale / 2);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[13], &VBOs[13], &segment);
	j += 2; index[14] = j;

	// obciazenie

	segment.setAll(posX + length / 2 - width / 2, posY, posZ, 2 * width, width*sqrt(3) / 2, width / 4);
	segmentTrans.push_back(*(segment.getModelMatrix()));

	segment.generateVertices();
	generateVO(&VAOs[14], &VBOs[14], &segment);
	j += 1; index[15] = j;
}

void CraneTop::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h, GLfloat rot)
{
	glm::mat4 translateToRot = glm::translate(glm::mat4(1.0f), glm::vec3(-posX, 0, -posZ));
	glm::mat4 translateToRot2 = glm::translate(glm::mat4(1.0f), glm::vec3(posX, 0, posZ));
	glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 1, 0));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(hookPosX, 0, 0));
	glm::mat4 translate2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -hookLength, 0));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, hookLength, 1.0f));

	rotMat = translateToRot2 * rotMat * translateToRot;

	glBindVertexArray(VAOs[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segmentTexture->getTextureID());

	s->setMat4("projection", *(c->getProjectionMatrix()));
	s->setMat4("view", c->getWorldToViewMatrix());

	for (int i = 0; i < segmentTrans.size()-6; ++i)
	{
		for (int k = 0; k < 16; k++)
			if (i == index[k]) glBindVertexArray(VAOs[k]);
		s->setMat4("model", rotMat*segmentTrans[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindTexture(GL_TEXTURE_2D, ropeTexture->getTextureID());

	// Liny

	for (int i = segmentTrans.size() - 6; i < segmentTrans.size() - 3; ++i)
	{
		glBindVertexArray(VAOs[i - segmentTrans.size() - 5]);
		s->setMat4("model", rotMat*segmentTrans[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//Hak

	for (int k = 0; k < 16; k++)
		if (segmentTrans.size() - 2 == index[k]) glBindVertexArray(VAOs[k]);

	s->setMat4("model", rotMat*translate * segmentTrans[segmentTrans.size() - 3]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	s->setMat4("model", rotMat * translate2 * translate * segmentTrans[segmentTrans.size() - 2] * scale);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Obciazenie

	for (int k = 0; k < 16; k++)
		if (segmentTrans.size() - 1 == index[k]) glBindVertexArray(VAOs[k]);

	glBindTexture(GL_TEXTURE_2D, concreteTexture->getTextureID());
	s->setMat4("model", rotMat * segmentTrans[segmentTrans.size() - 1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}



void CraneTop::generateVO(GLuint* vao, GLuint* vbo, Cuboid* segment)
{
	Renderer::generateVO(vao, vbo, segment);
}

