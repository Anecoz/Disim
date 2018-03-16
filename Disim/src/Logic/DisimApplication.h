#pragma once

#include "Application.h"
#include "../Graphics/DrawableCube.h"
#include "../Graphics/Camera.h"

class DisimApplication : public Application
{
public:
  DisimApplication();
  ~DisimApplication() = default;

  void render() override;
  void update(double delta) override;

private:
  DrawableCube _cube;
  Camera _camera;
};