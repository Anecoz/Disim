#include "Application.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../Input/KeyInput.h"
#include "../Input/MousePosInput.h"
#include "../Input/MouseButtonInput.h"

#include <iostream>
#include <chrono>
#include <string>

static void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error code: " << std::to_string(error) << ", description: " << description << std::endl;
}

Application::Application() :
  _running(false)
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(-1);
}

Application::~Application()
{
  glfwDestroyWindow(_window);
}

void Application::run()
{
	// Create gl window stuff
	InitWindowHandle();

	// Init Main loop stuff
	using namespace std::chrono;
	auto lastTime = std::chrono::duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
  auto delta = 0.0;
  auto ns = 1000000000.0 / 60.0;
  auto timer = std::chrono::duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
	int updates = 0;
	int frames = 0;
	std::string ups = " ups ";
  std::string fps = " fps";

  _running = true;

	// Main loop
	while (_running  && !glfwWindowShouldClose(_window)) {
		auto now = std::chrono::duration_cast<nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		delta += (now - lastTime) / ns;
		lastTime = now;

		// Logic Update
		if (delta >= 1.0) {
			glfwPollEvents();
			updates++;
			delta--;

			// Do updates here (to logic)
		}

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(_window);
		// Render stop

		frames++;
		if (duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - timer > 1000) {
			timer += 1000;
			glfwSetWindowTitle(_window, std::string(std::to_string(updates) + ups + std::to_string(frames) + fps).c_str());
			updates = 0;
			frames = 0;
		}
	}
  // Do cleanup here
}

void Application::InitWindowHandle()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(1280, 720, "Disim", NULL, NULL);

	if (!_window) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(0); // Vsync or not

	// Set input callbacks
	glfwSetKeyCallback(_window, KeyInput::invoke);
	glfwSetCursorPosCallback(_window, MousePosInput::invoke);
	glfwSetMouseButtonCallback(_window, MouseButtonInput::invoke);

	// Check for errors
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		exit(-3);
	}

	glClearColor(0.2, 0.2, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Supported OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}