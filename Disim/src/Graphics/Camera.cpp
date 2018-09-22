#include "Camera.h"

#include "../Input/KeyInput.h"
#include "../Input/MousePosInput.h"

#include <iostream>
#include <string>

#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& initialPosition)
  : _yaw(0.0)
  , _pitch(0.0)
  , _roll(0.0)
  , _firstMouse(true)
  , _projection(glm::perspective(glm::half_pi<double>(), 16.0/9.0, 0.1, 1000.0))  
  , _position(initialPosition)
  , _forward(0.0f, 0.0f, 0.0f)
  , _cameraMatrix(glm::lookAt(_position, _forward, _up))
{}

void Camera::update(double delta)
{
  if (_firstMouse) {
    _prevFreelookMousePos.x = 1280 / 2;
    _prevFreelookMousePos.y = 720 / 2;
    _firstMouse = false;
  }

  freelookUpdate(delta);  

  _prevFreelookMousePos = MousePosInput::getPosition();
}

void Camera::freelookUpdate(double delta)
{
  handleFreelookInput(delta);

  auto trans = glm::vec3(_position.x * -1, _position.y * -1, _position.z * -1);
  glm::mat4 view = glm::translate(trans);
  view *= glm::rotate((float)_yaw, glm::vec3(0, 1, 0));
  view *= glm::rotate((float)_pitch, glm::vec3(1, 0, 0));
  view *= glm::rotate((float)_roll, glm::vec3(0, 0, 1));
  _cameraMatrix = glm::inverse(view);

  _right = glm::normalize(view[0]);
  _up = glm::normalize(view[1]);
  _forward = glm::normalize(view[2]);
}

void Camera::handleFreelookInput(double delta)
{
  GLfloat speedModifier = _speed;

  if (KeyInput::isKeyDown(GLFW_KEY_SPACE))
    speedModifier = 3.0;
  if (KeyInput::isKeyDown(GLFW_KEY_LEFT_SHIFT))
    speedModifier += 30.0;
  if (KeyInput::isKeyDown(GLFW_KEY_LEFT_ALT))
    speedModifier += 300.0;

  GLfloat speed = (speedModifier*delta)*10.0;
  auto dx = (float)sin(_yaw) * speed;
  auto dz = (float)cos(_yaw) * speed;

  glm::vec3 movement;

  if (KeyInput::isKeyDown(GLFW_KEY_W))
  {
    movement += _forward * speed;
    //movement.x -= dx;
    //movement.z += dz;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_S))
  {
    movement -= _forward * speed;
    //movement.x += dx;
    //movement.z -= dz;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_A))
  {
    movement += _right * speed;
    //movement.x -= dz;
    //movement.z -= dx;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_D))
  {
    movement -= _right * speed;
    //movement.x += dz;
    //movement.z += dx;
  }

  // Roll
  if (KeyInput::isKeyDown(GLFW_KEY_Q)) {
    _roll -= 0.2 * speed;
  }
  if (KeyInput::isKeyDown(GLFW_KEY_E)) {
    _roll += 0.2 * speed;
  }

  _position += movement;

  auto mouseDelta = MousePosInput::getPosition() - _prevFreelookMousePos;

  _yaw -= mouseDelta.x * _sensitivity;
  _pitch -= mouseDelta.y * _sensitivity;
}
