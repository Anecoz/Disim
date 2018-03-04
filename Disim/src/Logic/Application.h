#pragma once

struct GLFWwindow;

class Application {
public:
	Application();
  ~Application();

	void run();

private:
	void InitWindowHandle();

  bool _running;
	GLFWwindow* _window;
};

