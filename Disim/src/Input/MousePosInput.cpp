#include "MousePosInput.h"

double MousePosInput::_x;
double MousePosInput::_y;

void MousePosInput::invoke(GLFWwindow* window, double xPos, double yPos) {
  _x = xPos;
  _y = yPos;
}