#include "Object.hh"

Object::Object()
  : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
}

Object::~Object()
{
}

void			Object::translate(glm::vec3 const &v) {
  _position += v;
}

void			Object::MoveAtPos(glm::vec3 const &v) {
  _position = v;
}

void			Object::rotate(glm::vec3 const& axis, float angle) {
  _rotation += axis * angle;
}

void			Object::scale(glm::vec3 const& scale) {
  _scale *= scale;
}

void			Object::putScale(glm::vec3 const& scale) {
  _scale = scale;
}

glm::mat4		Object::getTransformation()
{
  glm::mat4		transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}

bool		Object::initialize()
{
  return false;
}

void		Object::draw(gdl::AShader &, gdl::Clock const &)
{
}

glm::vec3	Object::getPosition() const
{
  return _position;
}

glm::vec3	Object::getRotation() const
{
  return _rotation;
}

void		Object::setPosition(const glm::vec3 &position)
{
  _position = position;
}

void		Object::setRotation(const glm::vec3 &rotation)
{
  _rotation = rotation;
}

