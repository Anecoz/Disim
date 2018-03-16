#pragma once

#include "Lowlevel/IndexedVertexArray.h"
#include "Lowlevel/Shader.h"

#include <memory>

class Camera;

class DrawableCube
{
public:
  DrawableCube();

  void draw(const Camera& camera);
private:
  std::unique_ptr<IndexedVertexArray> _cubeMesh;
  Shader _shader;
};