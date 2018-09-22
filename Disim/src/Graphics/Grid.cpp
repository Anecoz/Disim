#include "Grid.h"

#include <glm/gtx/transform.hpp>

#include "../Utils/GraphicsUtils.h"

Grid::Grid()
  : _modelMatrix(glm::scale(glm::vec3(10.0)))
  , _mesh(GraphicsUtils::loadObj("C:\\Users\\heilm\\source\\repos\\Disim\\Disim\\src\\grid.model"))
  , _shader(
    "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.vert",
    "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.tesc",
    "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.tese",
    "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.frag")
{
}

void Grid::draw(const Camera& camera)
{
  _shader.bind();
  _shader.uploadMatrix(camera.getCamMatrix(), "camMatrix");
  _shader.uploadMatrix(camera.getProjection(), "projMatrix");
  _shader.uploadMatrix(_modelMatrix, "modelMatrix");
  _shader.uploadVec(camera.getPosition(), "cameraPos");
  _mesh->drawTesselated();
  _shader.unbind();
}
