#ifndef _CUBEMAPTEXTURE_H_
#define _CUBEMAPTEXTURE_H_

#pragma once
#include "Texture.h"

class CubemapTexture : public Texture
{
	std::vector<std::string> cubemapFileNames;

public:
	CubemapTexture(std::vector<std::string> files);
	GLuint LoadCubemapTexture();
};

#endif _CUBEMAPTEXTURE_H_