#include "Camera.hh"

Camera::Camera(float x, float y, float mapX, float mapY, int id)
  : _id(id), _x(mapX), _y(mapY)
{
  _transformation = glm::lookAt(glm::vec3(x, -y + (_y - 7), 10), glm::vec3(x, -y + _y, 0), glm::vec3(0, 1, 0));
}

Camera::~Camera()
{

}

void	Camera::update(float x, float y)
{
  _transformation = glm::lookAt(glm::vec3(x, -y + (_y - 7), 10), glm::vec3(x, -y + _y, 0), glm::vec3(0, 1, 0));
}

void	Camera::updateHigh(float x, float y)
{
  _transformation = glm::lookAt(glm::vec3(x, -y + _y, 7), glm::vec3(x, -y + _y, 0), glm::vec3(0, 1, 0));
}

glm::mat4	Camera::getTransformation() const
{
  return _transformation;
}
