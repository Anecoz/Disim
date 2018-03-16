#include "Camera.h"

#include "../Input/KeyInput.h"
#include "../Input/MousePosInput.h"

#include <iostream>
#include <string>

#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& initialPosition)
  : _projection(glm::perspective(glm::half_pi<double>(), 16.0/9.0, 0.1, 1000.0))  
  , _position(initialPosition)
  , _forward(0.0f, 0.0f, 0.0f)
  , _cameraMatrix(glm::lookAt(_position, _forward, _up))
{}

void Camera::update(double delta)
{
  fpsStyleUpdate(delta);
	//updateCameraMovement(delta);
  recalcCameraMatrix();

  //std::cout << "Camera is now at: " << std::to_string(_position.x) << ", " << std::to_string(_position.y) << ", " << std::to_string(_position.z) << std::endl;
  //std::cout << "We are looking at: " << std::to_string(_forward.x) << ", " << std::to_string(_forward.y) << ", " << std::to_string(_forward.z) << std::endl;
}

void Camera::updateCameraMovement(double delta)
{
  // Project forward onto xz-plane (y = 0 plane)
  glm::vec3 xzProj(_forward.x, 0.f, _forward.z);
  xzProj = glm::normalize(xzProj);

  if (KeyInput::isKeyDown(GLFW_KEY_W))
  {
    // Move along forward projected onto xz-plane
    _position = _position + xzProj * static_cast<float>((_speed * delta));
  }
  if (KeyInput::isKeyDown(GLFW_KEY_S))
  {
    // Move along negative forward projected onto xz-plane
    _position = _position - xzProj * static_cast<float>((_speed * delta));
  }
  if (KeyInput::isKeyDown(GLFW_KEY_A))
  {
    // Move along xz-projected cross up
    auto dir = glm::cross(_up, xzProj);
    _position = _position + dir * static_cast<float>((_speed * delta));
  }
  if (KeyInput::isKeyDown(GLFW_KEY_D))
  {
    // Move along negative xz-projected cross up
    auto dir = glm::cross(_up, xzProj);
    _position = _position - dir * static_cast<float>((_speed * delta));
  }
}

void Camera::recalcCameraMatrix()
{
  _cameraMatrix = glm::lookAt(_position, _forward, _up);
}

void Camera::fpsStyleUpdate(double delta)
{
  handleMouseMovement(MousePosInput::getPosition().x, MousePosInput::getPosition().y);
  // I did the maths for this a loooooong 
  // time ago and sadly didn't comment anything.
  // It is what it is, move along.
  GLfloat speedModifier = _speed;

  if (KeyInput::isKeyDown(GLFW_KEY_SPACE))
    speedModifier = 3.0;
  if (KeyInput::isKeyDown(GLFW_KEY_LEFT_SHIFT))
    speedModifier += 30.0;
  if (KeyInput::isKeyDown(GLFW_KEY_LEFT_ALT))
    speedModifier += 300.0;

  GLfloat speed = (speedModifier*delta)*10.0;
  // Directional vector
  glm::vec3 n = _forward - _position;
  n = glm::normalize(n);
  n = n * speed;

  glm::mat4 camtrans = glm::translate(glm::vec3(-_position.x, -_position.y, -_position.z));
  glm::mat4 invcamtrans = glm::translate(glm::vec3(_position.x, _position.y, _position.z));

  _forward = glm::vec3(camtrans * glm::vec4(_forward, 1.0f));
  glm::vec3 axis = glm::cross(_forward, _up);
  _forward = glm::vec3(invcamtrans * glm::vec4(_forward, 1.0f));
  axis = glm::normalize(axis);
  axis = axis * speed;

  glm::vec3 tmp, tmp2, tmp3;

  tmp = _position;
  tmp2 = n;
  tmp3 = axis;

  if (KeyInput::isKeyDown(GLFW_KEY_W))
  {
    _position = tmp + tmp2;
    _forward = _forward + n;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_S))
  {
    _position = tmp - tmp2;
    _forward = _forward - n;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_A))
  {
    _position = tmp - tmp3;
    _forward = _forward - axis;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_D))
  {
    _position = tmp + tmp3;
    _forward = _forward + axis;
  }
}

void Camera::handleMouseMovement(int x, int y)
{
  GLfloat xdiff = ((GLfloat)200 - x) / ((GLfloat)_sensitivity*200); // Using offsets where mouse is warped everytime
  GLfloat ydiff = ((GLfloat)200 - y) / ((GLfloat)_sensitivity* 200);

  // Rotate l point----------------
  //Y-axis----------------------
  glm::mat4 camtrans = glm::translate(glm::vec3(-_position.x, -_position.y, -_position.z));
  glm::mat4 camRotY = glm::rotate(xdiff, glm::vec3(0, 1, 0));
  glm::mat4 invcamtrans = glm::translate(glm::vec3(_position.x, _position.y, _position.z));
  glm::mat4 yTot = invcamtrans * camRotY * camtrans;
  _forward = glm::vec3(yTot * glm::vec4(_forward, 1.0));

  //X-axis (or whatever)-------------
  //needs check for if l is on up (y-axis)
  glm::mat4 camRotX = glm::mat4(1.0f);

  _forward = glm::vec3(camtrans * glm::vec4(_forward, 1.0));
  glm::vec3 axis = glm::cross(_forward, _up);
  camRotX = glm::rotate(ydiff, axis);
  _forward = glm::vec3(camRotX * glm::vec4(_forward, 1.0));
  glm::vec3 axisAfter = glm::cross(_forward, _up);
  if (axisAfter.x < 0.05 && axisAfter.x > -0.05
    && axisAfter.z < 0.05 && axisAfter.z > -0.05
    && axisAfter.y < 0.05 && axisAfter.y > -0.05)
  {
    camRotX = glm::rotate(-ydiff, axis);
    _forward = glm::vec3(camRotX * glm::vec4(_forward, 1.0));
  }
  _forward = glm::vec3(invcamtrans * glm::vec4(_forward, 1.0));
}
