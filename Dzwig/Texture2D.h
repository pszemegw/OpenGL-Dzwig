#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include <SOIL.h>
#include <vector>
#include <string>
class Texture2D : public Texture
{
	std::string fileName;
public:
	GLuint LoadMipmapTexture();
	Texture2D(std::string fname);
};

#endif