#include "Skybox.h"



Skybox::Skybox(std::vector<std::string> fileNames)
{
	skyboxTexture = new CubemapTexture(fileNames);
	skyboxShader = ShaderProgram("skybox.vert", "skybox.frag");
	vertices = 
	{
		// Back face
	-1.0f, -1.0f, -1.0f, // Bottom-left
	 1.0f, -1.0f, -1.0f, // bottom-right    
	 1.0f,  1.0f, -1.0f, // top-right              
	 1.0f,  1.0f, -1.0f, // top-right
	-1.0f,  1.0f, -1.0f, // top-left
	-1.0f, -1.0f, -1.0f, // bottom-left                
	// Front face
	-1.0f, -1.0f,  1.0f, // bottom-left
	 1.0f,  1.0f,  1.0f, // top-right
	 1.0f, -1.0f,  1.0f, // bottom-right        
	 1.0f,  1.0f,  1.0f, // top-right
	-1.0f, -1.0f,  1.0f, // bottom-left
	-1.0f,  1.0f,  1.0f, // top-left        
	// Left face
	-1.0f,  1.0f,  1.0f, // top-right
	-1.0f, -1.0f, -1.0f, // bottom-left
	-1.0f,  1.0f, -1.0f, // top-left       
	-1.0f, -1.0f, -1.0f, // bottom-left
	-1.0f,  1.0f,  1.0f, // top-right
	-1.0f, -1.0f,  1.0f, // bottom-right
	// Right face
	 1.0f,  1.0f,  1.0f, // top-left
	 1.0f,  1.0f, -1.0f, // top-right      
	 1.0f, -1.0f, -1.0f, // bottom-right          
	 1.0f, -1.0f, -1.0f, // bottom-right
	 1.0f, -1.0f,  1.0f, // bottom-left
	 1.0f,  1.0f,  1.0f, // top-left
	// Bottom face      
	-1.0f, -1.0f, -1.0f, // top-right
	 1.0f, -1.0f,  1.0f, // bottom-left
	 1.0f, -1.0f, -1.0f, // top-left        
	 1.0f, -1.0f,  1.0f, // bottom-left
	-1.0f, -1.0f, -1.0f, // top-right
	-1.0f, -1.0f,  1.0f, // bottom-right
	// Top face
	-1.0f,  1.0f, -1.0f, // top-left
	 1.0f,  1.0f, -1.0f, // top-right
	 1.0f,  1.0f,  1.0f, // bottom-right                 
	 1.0f,  1.0f,  1.0f, // bottom-right
	-1.0f,  1.0f,  1.0f, // bottom-left  
	-1.0f,  1.0f, -1.0f, // top-left
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

	glBufferData
	(
		GL_ARRAY_BUFFER,
		sizeof(GLfloat)*vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW
	);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
}

void Skybox::draw(glm::mat4 * viewMatrix, glm::mat4 * projectionMatrix)
{
	glDepthFunc(GL_LEQUAL);
	skyboxShader.Use();
	*viewMatrix = glm::mat4(glm::mat3(*viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "view"), 1, GL_FALSE, &(*viewMatrix)[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "projection"), 1, GL_FALSE, &(*projectionMatrix)[0][0]);

	// skybox
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture->getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}
