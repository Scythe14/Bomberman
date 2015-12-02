#include "Char.hh"

Char::Char(unsigned char c)
{
  _rotation.z = -90.0f;
  _path = "./Includes/Font/";
  _path += c;
  _path += ".tga";
}

Char::Char(unsigned char c, int x)
{
  _rotation.z = 90.0f;
  scale(glm::vec3(x, x, 0));
  if (c != '-')
    {
      _path = "./Includes/Font/";
      _path += c;
      _path += ".tga";
    }
  else
    _path = "./Includes/GDL_lib/assets/cursor.tga";
}

Char::Char(unsigned char c, int x, int y)
{
  _rotation.z = 90.0f;
  scale(glm::vec3(x, y, 0));
  if (c != 0xFF && c != '-')
    {
      _path = "./Includes/Font/";
      _path += c;
      _path += ".tga";
    }
  else if (c == 0xFF)
    _path = "./Includes/GDL_lib/assets/pause.tga";
}

Char::Char(const std::string &path, int x, int y)
{
  scale(glm::vec3(x, y, 0));
  _path = path;
}

Char::~Char()
{
}

bool	Char::initialize()
{
  if (_texture.load(_path) == false)
    {
      std::cerr << "Cannot load the cube texture : " << _path << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  return (true);
}

void	Char::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
