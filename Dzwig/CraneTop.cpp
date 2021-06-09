#include "CraneTop.h"

CraneTop::CraneTop(std::string textureFileName)
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

	glBindVertexArray(0);


	segment.setAll(-length, posy, -width/2, length + width/2, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(-length , posy, width / 2, length + width / 2, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(-length, posy+width*glm::sqrt(3)/2, 0, length - width / 2, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());

	for (int i = 0; i < 1 + 2*length / width; ++i)
	{
		segment.setAll(-width/2 - i*width, posy, 0, segmentScale, segmentScale, width/2);
		segmentTrans.push_back(segment.getModelMatrix());
	}

	for (int i = 0; i < 2 * length / width; ++i)
	{
		segment.setAll(-width / 2 - i * width, posy+ width*sqrt(3)/4, width/4, segmentScale, segmentScale, width / 2,1,0,0,60);
		segmentTrans.push_back(segment.getModelMatrix());
	}
	for (int i = 0; i < 2 * length / width; ++i)
	{
		segment.setAll(-width / 2 - i * width, posy + width * sqrt(3) / 4, -width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 120);
		segmentTrans.push_back(segment.getModelMatrix());
	}

	segment.setAll(length/2 - width/2, posy, 0, length/2, segmentScale, width/2);
	segmentTrans.push_back(segment.getModelMatrix());

	//segment.setAll( - 2 * length/width, posy, width / 4, width*sqrt(3)/2, segmentScale, segmentScale, 0, 1, 0, 30);
	segment.setAll(-2 * length / width, posy, width / 2, width*sqrt(3) / 4, segmentScale, segmentScale,0,1,0,30);
	//segment.setRotation2(0, 0, 1, 30);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(length-width*2, posy+width, 0, 2 * width, width*sqrt(3)/2, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());
}

void CraneTop::draw(ShaderProgram * s, Camera * c, GLuint w, GLuint h)
{
	glm::mat4 trans;
	glm::mat4 view = c->getWorldToViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(c->getFOV()), w*1.0f / h, 0.1f, 1000.0f);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segment.getTexture().getTextureID());

	for (int i = 0; i < segmentTrans.size(); ++i)
	{
		trans = projection * view * glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), glm::vec3(0, 1, 0)) * segmentTrans[i];
		glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}


