#include "DisimApplication.h"
#include <GLFW/glfw3.h>

DisimApplication::DisimApplication()
  : _camera(glm::vec3(5.f, 5.f, 5.f))
{
}

void DisimApplication::render()
{
  _cube.draw(_camera);
}

void DisimApplication::update(double delta)
{
  _camera.update(delta);
  glfwSetCursorPos(_window, 200, 200);
}