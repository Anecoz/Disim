#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& initialPosition);
	~Camera() = default;

	void update(double delta);

	void setPosition(glm::vec3& posIn) { _position = posIn; }
	glm::vec3 getPosition() const { return _position; }
  glm::mat4 getProjection() const { return _projection; }
  glm::mat4 getCamMatrix() const { return _cameraMatrix; }
  glm::mat4 getCombined() const { return _projection * _cameraMatrix; }

private:
  void updateCameraMovement(double delta);
  void recalcCameraMatrix();
  void fpsStyleUpdate(double delta);
  void handleMouseMovement(int x, int y);

	glm::mat4 _projection;
	glm::mat4 _cameraMatrix;
	glm::vec3 _position;
  glm::vec3 _forward;
  const glm::vec3 _up = glm::vec3(0.f, 1.f, 0.f);
  const double _speed = 0.05;
  float _sensitivity = 1.0; // Higher value -> lower sens...
};

