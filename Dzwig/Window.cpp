#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"

using namespace std;

void Window::onKey(int key, int scancode, int actions, int mods)
{
	cout << key << endl;
	if (!isFocused) return;
	if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS)
		glfwSetWindowShouldClose(this->openglWindow, GL_TRUE);
	if (key == GLFW_KEY_Q && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.DOWN);
	if (key == GLFW_KEY_E && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.UP);
	if (key == GLFW_KEY_A && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.LEFT);
	if (key == GLFW_KEY_D && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.RIGHT);
	if (key == GLFW_KEY_S && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.BACKWARD);
	if (key == GLFW_KEY_W && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.moveCamera(camera.FORWARD);
	if (key == GLFW_KEY_R && actions == GLFW_PRESS)
		camera.resetCamera();

	if (key == GLFW_KEY_KP_8 && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.rotateCamera(0,5);
	if (key == GLFW_KEY_KP_6 && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.rotateCamera(-5, 0);
	if (key == GLFW_KEY_KP_4 && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.rotateCamera(5, 0);
	if (key == GLFW_KEY_KP_2 && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.rotateCamera(0, -5);
	if (key == GLFW_KEY_KP_MULTIPLY && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.setFOV(camera.getFOV()+ 1.0f);
	if (key == GLFW_KEY_KP_DIVIDE && actions == GLFW_PRESS | GLFW_REPEAT)
		camera.setFOV(camera.getFOV() - 1.0f);
	

}

void Window::mouseCallback(double xpos, double ypos)
{
	if (!isFocused) return;
	camera.rotateCamera(prevMousePos.x - xpos, prevMousePos.y - ypos);
	prevMousePos = glm::vec2(xpos, ypos);
}

void Window::focus_callback(int focused)
{
	if (!focused)
	{
		glfwSetInputMode(openglWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		isFocused = false;
	}
}

void Window::scroll_callback(double xoffset, double yoffset)
{
}

void Window::mouse_button_callback(int button, int action, int mods)
{
	glfwGetCursorPos(openglWindow, &(prevMousePos.x), &(prevMousePos.y));
	if (prevMousePos.y <= height && prevMousePos.y >= 0 && prevMousePos.x >= 0 && prevMousePos.x <= width)
	{
		glfwSetInputMode(openglWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		isFocused = true;
	}
}



void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint Window::LoadMipmapTexture(GLuint texId, const char * fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

Window::Window(GLuint w, GLuint h)
{
	this->width = w;
	this->height = h;
	

	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		initStatus = -1;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		openglWindow = glfwCreateWindow(this->width, this->height, "GKOM Dzwig", nullptr, nullptr);
		if (openglWindow == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(openglWindow);
		glfwSetWindowUserPointer(openglWindow, this);

		// Set keyboard callback function
		glfwSetKeyCallback(openglWindow, Window::onKey);

		// Set focus callback

		glfwSetWindowFocusCallback(openglWindow, Window::focus_callback);

		// Set scroll callback

		glfwSetScrollCallback(openglWindow, Window::scroll_callback);

		// Set mouse button callback
		glfwSetMouseButtonCallback(openglWindow, Window::mouse_button_callback);

		// Set mouse callback and cursor position
		glfwSetCursorPosCallback(openglWindow, Window::cursor_position_callback);
		glfwSetInputMode(openglWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(openglWindow, &(prevMousePos.x), &(prevMousePos.y));


		//Enable z-buffer test
		glEnable(GL_DEPTH_TEST);

		glewExperimental = GL_TRUE;
		// Init glew
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, this->width, this->height);
		glfwSwapInterval(1);

		/*string vv = , ff = "gl_05.frag";
		GLchar v[20];
		GLchar f[20];
		vv.copy(v, vv.length(), 0);
		ff.copy(f, ff.length(), 0);

		shaderProgram.setShaderPaths(f,v);*/
		this->shaderProgram = ShaderProgram("gl_05.vert", "gl_05.frag");
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	return;
}

int Window::mainLoop()
{
	try
	{	
		GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		GLuint VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

							  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE0, "tex.jpg");

		// main event loop
		while (!glfwWindowShouldClose(openglWindow))
		{
			// Check if any events have been activiated
			glfwPollEvents();

			glClearColor(0.0f, 0.3f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);

			// activate shader
			shaderProgram.Use();

			// create transformations
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
			projection = glm::perspective(glm::radians(camera.getFOV()), (float)width / (float)height, 0.1f, 100.0f);

			glm::mat4 trans = projection*camera.getWorldToViewMatrix()*model;
			
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);

			// render box
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glfwSwapBuffers(openglWindow);
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();
	return 0;
}
