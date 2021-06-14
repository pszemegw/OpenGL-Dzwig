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



Window::Window(GLuint w, GLuint h)
{
	this->width = w;
	this->height = h;
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		initStatus = -1;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		int monitorX, monitorY;
		glfwGetMonitorPos(primary, &monitorX, &monitorY);
		const GLFWvidmode *mode = glfwGetVideoMode(primary);
		if (!mode)
			return;

		openglWindow = glfwCreateWindow(this->width, this->height, "GKOM Dzwig", nullptr, nullptr);
		if (openglWindow == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(openglWindow);
		glfwSetWindowUserPointer(openglWindow, this);
		
		glfwSetWindowPos(openglWindow, monitorX + (mode->width - width) / 2,
			monitorY + (mode->height - height) / 2);

		// Set keyboard callback function
		glfwSetKeyCallback(openglWindow, Window::onKey);

		// Set focus callback

		glfwSetWindowFocusCallback(openglWindow, Window::focus_callback);

		// Set scroll callback

		//glfwSetScrollCallback(openglWindow, Window::scroll_callback);

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

		//SKYBOX

		skybox = new Skybox({ 
			"skybox/xpos.png",
			"skybox/xneg.png",
			"skybox/ypos.png",
			"skybox/yneg.png",
			"skybox/zpos.png",
			"skybox/zneg1.png" });

		// KAMERA

		camera = new Camera(0.f,10.f,30.f,-90.f,0.f,90.f,width,height,0.1f,10000.f);
		camera->increaseCameraSpeed(10.f);

		// ŒWiAT£A
		light = new Light(&shaderProgram);

		// DWIG
		dzwig = new Crane();
		dzwig->setLights(light);

		//SHADER
		this->shaderProgram = ShaderProgram("gl_05.vert", "gl_05.frag");

		// POD£O¯E
		ground = new Cuboid(0, -1.f, 0, 10000, 1, 10000);
		ground->setTexture("gnd1.jpg");

		
		
		
		this->mainLoop();
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
		GLuint VBO, VAO;
		GLuint skyboxVAO, skyboxVBO;

		Renderer::generateVO(&VAO, &VBO, ground);
		
		GLdouble lastFrame = 0.0f;
		

		light->setCameraLight(camera->getCameraPosition(), 1.f, 0.01f, 0.01f,
			glm::vec3(1.f, 1.f, 1.f), glm::vec3(.8f, .8f, .8f), glm::vec3(1.f, 1.f, 1.f));

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
			
			light->updateCameraPosition(camera->getCameraPosition());

			light->setShaderParams();


			// RYSOWANIE DZWIGU
			dzwig->draw(&shaderProgram, camera, this->width, this->height);


			// RYSOWANIE POD£O¯A
			drawGround(VAO);

			// RYSOWANIE SKYBOX'a
			skybox->draw(&(camera->getWorldToViewMatrix()), camera->getProjectionMatrix());
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














// CALLBACKS

void Window::onKey(int key, int scancode, int action, int mods)
{
	if (!isFocused) return;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		light->toggleCameraLight();

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(this->openglWindow, GL_TRUE);

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		camera->resetCamera();

	if (key == GLFW_KEY_KP_8 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(0, 5);
	if (key == GLFW_KEY_KP_6 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(-5, 0);
	if (key == GLFW_KEY_KP_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(5, 0);
	if (key == GLFW_KEY_KP_2 && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->rotateCamera(0, -5);
	if (key == GLFW_KEY_KP_MULTIPLY && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->setFOV(camera->getFOV() + 1.0f);
	if (key == GLFW_KEY_KP_DIVIDE && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->setFOV(camera->getFOV() - 1.0f);
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->increaseCameraSpeed(.5f);
	if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera->decreaseCameraSpeed(.5f);


	if (key == GLFW_KEY_1 && (action == GLFW_PRESS))
		dzwig->toggleLamp(0);
	if (key == GLFW_KEY_2 && (action == GLFW_PRESS))
		dzwig->toggleLamp(1);
	if (key == GLFW_KEY_3 && (action == GLFW_PRESS))
		dzwig->toggleLamp(2);
	if (key == GLFW_KEY_4 && (action == GLFW_PRESS))
		dzwig->toggleLamp(3);

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
	//cout << xoffset << "    " << yoffset << endl;
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

	if (glfwGetKey(openglWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->moveCamera(Camera::Y_MINUS);

	if (glfwGetKey(openglWindow, GLFW_KEY_UP) == GLFW_PRESS)
		camera->moveCamera(Camera::Y_PLUS);

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

	if (glfwGetKey(openglWindow, GLFW_KEY_O) == GLFW_PRESS)
		light->cameraLightIntensityInc(0.0001f);
	if (glfwGetKey(openglWindow, GLFW_KEY_P) == GLFW_PRESS)
		light->cameraLightIntensityInc(-0.0001f);
}



void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::drawGround(GLuint vao)
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ground->getTexture().getTextureID());

	shaderProgram.setMat4("model", *ground->getModelMatrix());
	shaderProgram.setMat4("view", camera->getWorldToViewMatrix());
	shaderProgram.setMat4("projection", *(camera->getProjectionMatrix()));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}