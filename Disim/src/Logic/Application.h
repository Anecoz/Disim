#pragma once

struct GLFWwindow;

class Application {
public:
	Application();
  virtual ~Application();

	void run();

  virtual void render() = 0;
  virtual void update(double delta) = 0;

private:
	void initWindowHandle();

  bool _running;
	GLFWwindow* _window;
};

