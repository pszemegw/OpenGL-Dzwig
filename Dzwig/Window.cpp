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
#include <windows.h>

using namespace std;

void Window::onKey(int key, int scancode, int action, int mods)
{
	/*cout << key << endl;
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
		camera->decreaseCameraSpeed(.5f);*/

	/*if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		cube->setPosition(cube->getPosition()[0], cube->getPosition()[1]+1, cube->getPosition()[2]);
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		cube->setPosition(cube->getPosition()[0], cube->getPosition()[1] - 1, cube->getPosition()[2]);*/


	/*if (key == GLFW_KEY_KP_DECIMAL && (action == GLFW_PRESS || action == GLFW_REPEAT))
		test = !test;*/
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

void Window::keyboardInput()
{
	if (glfwGetKey(this->openglWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->openglWindow, true);

	if (glfwGetKey(openglWindow, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveCamera(Camera::FORWARD);
	if (glfwGetKey(openglWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveCamera(Camera::BACKWARD);
	if (glfwGetKey(openglWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveCamera(Camera::LEFT);
	if (glfwGetKey(openglWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveCamera(Camera::RIGHT);

	if (glfwGetKey(openglWindow, GLFW_KEY_Q) == GLFW_PRESS)
		camera->moveCamera(Camera::DOWN);

	if (glfwGetKey(openglWindow, GLFW_KEY_E) == GLFW_PRESS)
		camera->moveCamera(Camera::UP);

	if (glfwGetKey(openglWindow, GLFW_KEY_R) == GLFW_PRESS)
		camera->resetCamera();

	if (glfwGetKey(openglWindow, GLFW_KEY_KP_2) == GLFW_PRESS)
		camera->rotateCamera(0, -5);

	if (glfwGetKey(openglWindow, GLFW_KEY_KP_8) == GLFW_PRESS)
		camera->rotateCamera(0, 5);

	if (glfwGetKey(openglWindow, GLFW_KEY_KP_6) == GLFW_PRESS)
		camera->rotateCamera(-5, 0);

	if (glfwGetKey(openglWindow, GLFW_KEY_KP_4) == GLFW_PRESS)
		camera->rotateCamera(5, 0);

	if (glfwGetKey(openglWindow, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
		camera->setFOV(camera->getFOV() + 1.0f);
	if (glfwGetKey(openglWindow, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		camera->setFOV(camera->getFOV() - 1.0f);
	if (glfwGetKey(openglWindow, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		camera->increaseCameraSpeed(.1f);
	if (glfwGetKey(openglWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		camera->decreaseCameraSpeed(.1f);

	if (glfwGetKey(openglWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		dzwig->rotateCrane(0.1f);
	if (glfwGetKey(openglWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
		dzwig->rotateCrane(-0.1f);

	if (glfwGetKey(openglWindow, GLFW_KEY_L) == GLFW_PRESS)
		dzwig->moveHookX(0.1f);
	if (glfwGetKey(openglWindow, GLFW_KEY_J) == GLFW_PRESS)
		dzwig->moveHookX(-0.1f);

	if (glfwGetKey(openglWindow, GLFW_KEY_K) == GLFW_PRESS)
		dzwig->moveHookY(0.1f);
	if (glfwGetKey(openglWindow, GLFW_KEY_I) == GLFW_PRESS)
		dzwig->moveHookY(-0.1f);
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
	//glHint(GL_FOG_HINT, GL_NICEST);
	try
	{
		openglWindow = glfwCreateWindow(this->width, this->height, "GKOM Dzwig", nullptr, nullptr);
		if (openglWindow == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(openglWindow);
		glfwSetWindowUserPointer(openglWindow, this);

		// Set keyboard callback function
		//glfwSetKeyCallback(openglWindow, Window::onKey);

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

		//Enable face culling
		glEnable(GL_CULL_FACE);
		
		glewExperimental = GL_TRUE;
		// Init glew
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, this->width, this->height);
		glfwSwapInterval(1);

		skybox = new Skybox({ 
			"skybox/xpos.png",
			"skybox/xneg.png",
			"skybox/ypos.png",
			"skybox/yneg.png",
			"skybox/zpos.png",
			"skybox/zneg1.png" });
		camera = new Camera(0.f,10.f,10.f,-90.f,0.f,90.f,width,height,0.1f,10000.f);
		camera->increaseCameraSpeed(10.f);
		dzwig = new Crane();
		this->shaderProgram = ShaderProgram("gl_05.vert", "gl_05.frag");
		ground = new Cuboid(0, -1.f, 0, 10000, 1, 10000);
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
		GLuint VBO, VAO, VBO1, VAO1;
		unsigned int skyboxVAO, skyboxVBO;
		unsigned int lightVAO;

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		// texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


		// skybox VAO
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		
		GLdouble lastFrame = 0.0f;

		glEnable(GL_FOG);
		GLfloat fogColor[] = { 0.0f, 0.3f, 0.9f, 1.0f };
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_START, 0.1f);
		glFogf(GL_FOG_END, 100.0f);

		// main event loop
		while (!glfwWindowShouldClose(openglWindow))
		{
			GLdouble currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			camera->setDeltaTime(deltaTime);
			keyboardInput();
			// Check if any events have been activiated
			glfwPollEvents();

			if (!isFocused) 
			{
				Sleep(500); 
				continue;
			}

			glClearColor(0.0f, 0.3f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// activate shader
			shaderProgram.Use();
			this->shaderProgram.setVec3("lightColor", glm::vec3(1.f, 1.f, .5f));
			this->shaderProgram.setVec3("ambientColor", glm::vec3(0.2f, .2f, 1.0f));
			//this->shaderProgram.setVec3("lightColor", glm::vec3(1.f, 0.0f, 0.0f));
			this->shaderProgram.setVec3("lightPos", *(camera->getCameraPosition()));
			this->shaderProgram.setVec3("light.position", *(camera->getCameraPosition()));
			//this->shaderProgram.setVec3("light.direction", 10.f, 1.0f, 0.f);

			shaderProgram.setFloat("light.constant", 0.5f);
			shaderProgram.setFloat("light.linear", 0.01f);
			shaderProgram.setFloat("light.quadratic", 0.0032f);

			this->shaderProgram.setVec3("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));
			this->shaderProgram.setVec3("viewPos", *(camera->getCameraPosition()));
			this->shaderProgram.setVec3("direction", camera->getCameraFront());
			this->shaderProgram.setFloat("cutOff", glm::cos(glm::radians(15.f)));


			// create transformations
			glm::mat4 view = camera->getWorldToViewMatrix();
			glm::mat4 projection = glm::mat4(1.0f);

			projection = glm::perspective(glm::radians(camera->getFOV()), (float)width / height, 0.1f, 1000.0f);

			glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians((GLfloat) glfwGetTime()*1), glm::vec3(0.f, 1.f, 0.f));

			glm::mat4 trans;















			


















			dzwig->draw(&shaderProgram, camera, this->width, this->height);

			glBindVertexArray(VAO1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ground->getTexture().getTextureID());
			if (test) glEnableVertexAttribArray(1);
			else glDisableVertexAttribArray(1);

			trans = projection * camera->getWorldToViewMatrix()*ground->getModelMatrix();
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.get_programID(), "transform"), 1, GL_FALSE, &trans[0][0]);
			shaderProgram.setMat4("model", ground->getModelMatrix());
			shaderProgram.setMat4("view", camera->getWorldToViewMatrix());
			shaderProgram.setMat4("projection", projection);
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
