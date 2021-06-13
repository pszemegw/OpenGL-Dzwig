#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Skybox.h"
#include "Camera.h"
#include "Cuboid.h"
#include "Crane.h"
#include "Light.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Window
{
	GLint initStatus = 0;
	GLuint width = 800;
	GLuint height = 600;
	GLdouble deltaTime = 0.f;
	GLFWwindow* openglWindow;
	ShaderProgram shaderProgram;
	
	Camera* camera;
	Skybox* skybox;
	Crane* dzwig;
	bool lmbPressed = false;
	bool rmbPressed = false;
	bool isFocused = true;

	glm::dvec2 prevMousePos;

	Cuboid* cube;
	Cuboid* ground;

	Light* light;

	void drawGround(GLuint vao);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void onKey(GLFWwindow* window, int key, int scancode, int actions, int mods)
	{
		Window* obj = (Window*)glfwGetWindowUserPointer(window);
		obj->onKey(key, scancode, actions, mods);
	}

	static void focus_callback(GLFWwindow* window, int focused)
	{
		Window* obj = (Window*)glfwGetWindowUserPointer(window);
		obj->focus_callback(focused);
	}
	
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* obj = (Window*)glfwGetWindowUserPointer(window);
		obj->mouseCallback(xpos, ypos);
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Window* obj = (Window*)glfwGetWindowUserPointer(window);
		obj->mouseCallback(xoffset, yoffset);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* obj = (Window*)glfwGetWindowUserPointer(window);
		obj->mouse_button_callback(button, action, mods);
	}

	
public:
	Window(GLuint w = 800, GLuint h = 600);
	int mainLoop();

	void onKey(int key, int scancode, int actions, int mods);
	
	void mouseCallback(double xpos, double ypos);
	void focus_callback(int focused);
	void scroll_callback(double xoffset, double yoffset);
	void mouse_button_callback(int button, int action, int mods);

	void keyboardInput();
	
	

};