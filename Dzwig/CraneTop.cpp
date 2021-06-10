#include "CraneTop.h"

CraneTop::CraneTop(std::string textureFileName)
{
	
	segment.setTexture(textureFileName);
	ropeTexture = new Texture2D("black.png");
	concreteTexture = new Texture2D("concrete.jpg");

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


	GLfloat length2 = length - width / 2;

	segment.setAll(-length, posy, -width/2, length /*+ width/2*/, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(-length, posy, width / 2, length /*+ width / 2*/, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(-length2, posy+width*glm::sqrt(3)/2, 0, length2, segmentScale, segmentScale);
	segmentTrans.push_back(segment.getModelMatrix());

	for (int i = 0; i < 2*length / width -1; ++i)
	{
		segment.setAll(-width/2 - i*width, posy, 0, segmentScale, segmentScale, width/2);
		segmentTrans.push_back(segment.getModelMatrix());
	}
	segment.setAll(-2*length, posy, 0, segmentScale, segmentScale, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());

	for (int i = 0; i < 2 * length / width -1; ++i)
	{
		segment.setAll(-width / 2 - i * width, posy+ width*sqrt(3)/4, width/4, segmentScale, segmentScale, width / 2,1,0,0,60);
		segmentTrans.push_back(segment.getModelMatrix());
	}
	for (int i = 0; i < 2 * length / width -1; ++i)
	{
		segment.setAll(-width / 2 - i * width, posy + width * sqrt(3) / 4, -width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 120);
		segmentTrans.push_back(segment.getModelMatrix());
	}

	segment.setAll(- 2*length + width/2, posy + width * sqrt(3) / 4, -width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 120);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setAll(-2 * length + width / 2, posy + width * sqrt(3) / 4, width / 4, segmentScale, segmentScale, width*sqrt(8) / 4, 1, 0, 0, 60);
	segment.setRotation2(0, 1, 0, -45);
	segmentTrans.push_back(segment.getModelMatrix());
	segment.setRotation2(0, 1, 0, 0);
	//segment.setAll(-width / 2 - i * width, posy + width * sqrt(3) / 4, -width / 4, segmentScale, segmentScale, width / 2, 1, 0, 0, 120);
	

	//segment.setAll( - 2 * length  - length/width, posy+width*sqrt(3)/4, width / 4, width*sqrt(6)/4, segmentScale, segmentScale, 0, 1, 0, 30);
	//segment.setAll(-2 * length / width, posy, width / 2, width*sqrt(3) / 4, segmentScale, segmentScale,0,1,0,30);
	//segment.setRotation2(0, 0, 1, 45);
	//segmentTrans.push_back(segment.getModelMatrix());

	

	

	GLfloat h = sqrt(2)* width * glm::tan(glm::radians(75.f))/2;
	GLfloat h2 = h - width * sqrt(3) / 2;
	GLfloat lineLength = glm::sqrt(h2*h2 + length*length);

	//segment.setAll(0, posy + h2/2 + h/4, 0, segmentScale, h2/2, segmentScale);
	//segmentTrans.push_back(segment.getModelMatrix());

	

	

	segment.setAll(0, posy+h/2, 0, segmentScale,h/2,segmentScale,0,0,1,/*glm::degrees(glm::atan(h2/2*(length-width)))*/0);
	segmentTrans.push_back(segment.getModelMatrix());


	// zwienczenie
	GLfloat alpha = glm::radians(75.f);
	segment.setAll(-width / 4, posy + width * glm::sqrt(2)*glm::tan(alpha) / 4, width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 45);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(width / 4, posy + width * glm::sqrt(2)*glm::tan(alpha) / 4, width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 135);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(width / 4, posy + width * glm::sqrt(2)*glm::tan(alpha) / 4, -width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 225);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setAll(-width / 4, posy + width * glm::sqrt(2)*glm::tan(alpha) / 4, -width / 4, width*sqrt(2) / (4 * glm::cos(alpha)), segmentScale, segmentScale, 0, 1, 0, 315);
	segment.setRotation2(0, 0, 1, 75);
	segmentTrans.push_back(segment.getModelMatrix());

	segment.setRotation2(0, 1, 0, 0);

	//tyl

	segment.setAll(length / 2 - width / 2, posy, 0, length / 2, segmentScale, width / 2);
	segmentTrans.push_back(segment.getModelMatrix());

	//liny

	GLfloat x = glm::degrees(glm::atan(h2 / (2 * length2 + width / 2)));
	segment.setAll(
		-length2, posy + width * sqrt(3) / 2 + h2 / 2, 0,
		length2, segmentScale / 5, segmentScale / 5,
		0, 0, 1, x
	);
	segmentTrans.push_back(segment.getModelMatrix());

	lineLength = glm::sqrt(h*h + (length-width/2)/2 * (length - width / 2) / 2);
	x = -glm::degrees(glm::atan(h / (length - width/2)));
	segment.setAll(
		length/2, posy + h / 2, 0,
		lineLength, segmentScale / 5, segmentScale / 5,
		0, 0, 1, x
	);

	segmentTrans.push_back(segment.getModelMatrix());


	// obciazenie

	segment.setAll(length/2-width/2, posy, 0, 2 * width, width*sqrt(3) / 2, width/4);
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

	for (int i = 0; i < segmentTrans.size()-3; ++i)
	{
		trans = projection * view * glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime()/36, glm::vec3(0, 1, 0)) * segmentTrans[i];
		glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindTexture(GL_TEXTURE_2D, ropeTexture->getTextureID());
	trans = projection * view * glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() / 36, glm::vec3(0, 1, 0)) * segmentTrans[segmentTrans.size()-3];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	trans = projection * view * glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() / 36, glm::vec3(0, 1, 0)) * segmentTrans[segmentTrans.size() - 2];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, concreteTexture->getTextureID());
	trans = projection * view * glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() / 36, glm::vec3(0, 1, 0)) * segmentTrans[segmentTrans.size() - 1];
	glUniformMatrix4fv(glGetUniformLocation(s->get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}


