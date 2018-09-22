#include "Grid.h"

#include "../Utils/GraphicsUtils.h"

Grid::Grid()
  : _mesh(GraphicsUtils::loadObj("C:\\Users\\heilm\\source\\repos\\Disim\\Disim\\src\\grid.model"))
  , _shader("C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.vert", "C:/Users/heilm/source/repos/Disim/Disim/src/Graphics/standard.frag")
{
}

void Grid::draw(const Camera & camera)
{
  _shader.bind();
  _shader.uploadMatrix(camera.getCamMatrix(), "camMatrix");
  _shader.uploadMatrix(camera.getProjection(), "projMatrix");
  _mesh->draw();
  _shader.unbind();
}
