#include <iostream>
#include "Ground.hh"

Ground::Ground(const std::string &s, float y, float x)
  : _path(s), _x(x),  _y(y)
{
}

Ground::~Ground()
{
}

bool		Ground::initialize()
{
  if (_texture.load(_path) == false)
    {
      std::cerr << "Cannot load the ground texture" << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(_x + 0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(_x + 0.5, -0.5, _y + 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, _y + 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(_x, 0.0f));
  _geometry.pushUv(glm::vec2(_x, _y));
  _geometry.pushUv(glm::vec2(0.0f, _y));
  _geometry.build();
  _rotation.x -= 90.0f;
  translate(glm::vec3(0, 0, -1.12));
  return (true);
}

void		Ground::draw(gdl::AShader& shader, gdl::Clock const&)
{
  _texture.bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
