#include "Texture2D.h"

GLuint Texture2D::LoadMipmapTexture()
{
	unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");
	glGenTextures(1, &textureID);

	glActiveTexture(textureID);
	glBindTexture(textureType, textureID);
	glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(textureType);
	SOIL_free_image_data(image);
	glBindTexture(textureType, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}

Texture2D::Texture2D(std::string fname) : Texture()
{
	fileName = fname;
	textureType = GL_TEXTURE_2D;
	LoadMipmapTexture();
}