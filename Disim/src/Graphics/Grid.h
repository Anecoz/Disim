#pragma once

#include "Lowlevel/IndexedVertexArray.h"
#include "Lowlevel/Shader.h"
#include "Camera.h"

#include <memory>

class Grid
{
public:
  Grid();
  ~Grid() = default;

  void draw(const Camera& camera);

private:
  std::unique_ptr<IndexedVertexArray> _mesh;
  Shader _shader;
};