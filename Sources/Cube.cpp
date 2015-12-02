#include <iostream>
#include "BomberException.hpp"
#include "Cube.hh"

Cube::Cube()
{
  _pos.setX(0xCAFE);
  _pos.setY(0xCAFE);
}

Cube::~Cube()
{
  ;
}

glm::mat4		Cube::getTransformation()
{
  glm::mat4		transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  _transform = transform;
  return (_transform);
}

Position<int>	Cube::getPos() const
{
  return (_pos);
}

const glm::mat4&	Cube::getTransform() const
{
  return (_transform);
}

void			Cube::setPos(const Position<int> &pos)
{
  _pos.setX(pos.getX());
  _pos.setY(pos.getY());
}

int			Cube::getType() const
{
  return _type;
}

void			Cube::setType(int type)
{
  _type = type;
}
