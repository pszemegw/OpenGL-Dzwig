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
#include "Texture2D.h"
#include "CubemapTexture.h"
#include "Cuboid.h"
#include "CraneTower.h"
#include "CraneBase.h"
#include "CraneTop.h"

using namespace std;

void Window::onKey(int key, int scancode, int action, int mods)
{
	cout << key << endl;
	if (!isFocused) return;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(this->openglWindow, GL_TRUE);
	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->DOWN);
	if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->UP);
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->LEFT);
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->RIGHT);
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->BACKWARD);
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->moveCamera(camera->FORWARD);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		camera->resetCamera();

	if (key == GLFW_KEY_KP_8 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(0,5);
	if (key == GLFW_KEY_KP_6 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(-5, 0);
	if (key == GLFW_KEY_KP_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(5, 0);
	if (key == GLFW_KEY_KP_2 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(0, -5);
	if (key == GLFW_KEY_KP_MULTIPLY && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->setFOV(camera->getFOV()+ 1.0f);
	if (key == GLFW_KEY_KP_DIVIDE && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->setFOV(camera->getFOV() - 1.0f);
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->increaseCameraSpeed(.5f);
	if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->decreaseCameraSpeed(.5f);

	/*if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		cube->setPosition(cube->getPosition()[0], cube->getPosition()[1]+1, cube->getPosition()[2]);
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		cube->setPosition(cube->getPosition()[0], cube->getPosition()[1] - 1, cube->getPosition()[2]);*/


	if (key == GLFW_KEY_KP_DECIMAL && (action == GLFW_PRESS || action == GLFW_REPEAT))
		test = !test;
}

void Window::mouseCallback(double xpos, double ypos)
{
	if (!isFocused) return;
	camera->rotateCamera(prevMousePos.x - xpos, prevMousePos.y - ypos);
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
	cout << xoffset << "    " << yoffset << endl;
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

		glEnable(GL_CULL_FACE);

		glewExperimental = GL_TRUE;
		// Init glew
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, this->width, this->height);
		glfwSwapInterval(1);

		skybox = new Skybox({ "skybox/right.jpg",
			"skybox/left.jpg",
			"skybox/top.jpg",
			"skybox/bottom.jpg",
			"skybox/front.jpg",
			"skybox/back.jpg" });
		camera = new Camera();
		camera->increaseCameraSpeed(10.f);
		camera->moveCamera(Camera::BACKWARD);
		camera->moveCamera(Camera::UP);
		camera->decreaseCameraSpeed(10.f);
		this->shaderProgram = ShaderProgram("gl_05.vert", "gl_05.frag");

		ground = new Cuboid(0, -1.f, 0, 1000, 1, 1000);
		ground->setTexture("gnd1.jpg");
		
		

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
		GLuint VBO, VAO, VBO1, VAO1, VAO2, VBO2;
		unsigned int skyboxVAO, skyboxVBO;
		unsigned int lightVAO;
		CraneTower tower("metal.png");
		CraneBase base(1.5f,.2f,"concrete.jpg");
		CraneTop top("metal.png");


		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(
			GL_ARRAY_BUFFER,
			ground->getVertexTextureArraySize() * sizeof(GLfloat),
			ground->getVertexTextureArrayPointer(),
			GL_STATIC_DRAW);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		// texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


		// skybox VAO
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		
		// main event loop
		while (!glfwWindowShouldClose(openglWindow))
		{
			// Check if any events have been activiated
			glfwPollEvents();

			glClearColor(0.0f, 0.3f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// activate shader
			shaderProgram.Use();

			// create transformations
			glm::mat4 view = camera->getWorldToViewMatrix();
			glm::mat4 projection = glm::mat4(1.0f);

			projection = glm::perspective(glm::radians(camera->getFOV()), (float)width / height, 0.1f, 1000.0f);

			glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians((GLfloat) glfwGetTime()*1), glm::vec3(0.f, 1.f, 0.f));

			glm::mat4 trans;



			tower.draw(&shaderProgram, camera, this->width, this->height);
			base.draw(&shaderProgram, camera, this->width, this->height);
			top.draw(&shaderProgram, camera, this->width, this->height);



			glBindVertexArray(VAO1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ground->getTexture().getTextureID());
			if (test) glEnableVertexAttribArray(1);
			else glDisableVertexAttribArray(1);

			trans = projection * camera->getWorldToViewMatrix()*ground->getModelMatrix();
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			skybox->draw(&(camera->getWorldToViewMatrix()), &projection);
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
