#include "DisimApplication.h"
#include <GLFW/glfw3.h>

#include <iostream>

DisimApplication::DisimApplication()
  : _camera(glm::vec3(5.f, 5.f, 5.f))
{
  
}

void DisimApplication::render()
{
  //_cube.draw(_camera);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  _grid.draw(_camera);
}

void DisimApplication::update(double delta)
{
  _camera.update(delta);
}