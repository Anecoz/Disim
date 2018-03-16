#include "DrawableCube.h"

#include "Camera.h"

#include "../Utils/GraphicsUtils.h"

DrawableCube::DrawableCube()
  : _shader("C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.vert", "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.frag")
  , _cubeMesh(GraphicsUtils::createUnitCube())
{
}

void DrawableCube::draw(const Camera& camera)
{
  _shader.bind();
  _shader.uploadMatrix(camera.getCamMatrix(), "camMatrix");
  _shader.uploadMatrix(camera.getProjection(), "projMatrix");
  _cubeMesh->draw();
  _shader.unbind();
}
