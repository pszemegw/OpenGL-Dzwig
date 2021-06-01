#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <SOIL.h>
#include <vector>
#include <string>

#include "ShaderProgram.h"
class Texture
{
protected:
	int width, height;
	GLuint textureID;
	GLuint textureType;
public:
	GLuint getTextureID();
	int getWidth();
	int getHeight();
};

