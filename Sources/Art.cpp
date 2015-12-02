#include "Art.hh"

Art::Art(const std::string &path)
{
  _rotation.z = -90.0f;
  _path = "Includes/GDL_lib/assets/Players_Miniature/";
  _path += path;
  _path += ".tga";
}

Art::~Art() {}

bool	Art::initialize()
{
  if (_texture.load(_path) == false)
    {
      std::cerr << "Cannot load the texture" << std::endl;
      return false;
    }
  _geometry.pushVertex(glm::vec3(5.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(5.5, 2.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 2.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  return true;
}

void	Art::update(gdl::Clock const &, gdl::Input&) {}

void	Art::draw(gdl::AShader &shader, gdl::Clock const&)
{
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
