#pragma once
#include "Texture.h"

class CubemapTexture : public Texture
{
	std::vector<std::string> cubemapFileNames;

public:
	CubemapTexture(std::vector<std::string> files);
	GLuint LoadCubemapTexture();
};

