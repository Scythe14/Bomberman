#include "Skybox.hh"
#include "BomberException.hpp"

Skybox::Skybox(const char *path)
{
  _path = path;
}

Skybox::~Skybox()
{
  ;
}

bool Skybox::initialize()
{
  if (_texture1.load(_path + "skybox_back.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
    // BACK FACE
  _geometry1.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry1.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry1.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry1.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry1.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry1.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry1.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry1.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry1.build();

  if (_texture2.load(_path + "skybox_front.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
  // FRONT FACE
  _geometry2.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry2.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry2.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry2.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry2.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry2.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry2.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry2.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry2.build();

  if (_texture3.load(_path + "skybox_left.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
  // LEFT FACE
  _geometry3.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry3.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry3.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry3.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry3.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry3.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry3.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry3.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry3.build();

  if (_texture4.load(_path + "skybox_right.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
  // RIGHT FACE
  _geometry4.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry4.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry4.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry4.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry4.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry4.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry4.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry4.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry4.build();

  if (_texture5.load(_path + "skybox_top.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
  // UP FACE
  _geometry5.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry5.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry5.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry5.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry5.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry5.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry5.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry5.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry5.build();

  if (_texture6.load(_path + "skybox_bottom.tga") == false)
    throw BomberException("Cannot Load Skybox texture");
  // DOWN FACE
  _geometry6.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry6.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry6.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry6.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry6.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry6.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry6.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry6.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry6.build();

  return (true);
}

void Skybox::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture1.bind();
  _geometry1.draw(shader, getTransformation(), GL_QUADS);
  _texture2.bind();
  _geometry2.draw(shader, getTransformation(), GL_QUADS);
  _texture3.bind();
  _geometry3.draw(shader, getTransformation(), GL_QUADS);
  _texture4.bind();
  _geometry4.draw(shader, getTransformation(), GL_QUADS);
  _texture5.bind();
  _geometry5.draw(shader, getTransformation(), GL_QUADS);
  _texture6.bind();
  _geometry6.draw(shader, getTransformation(), GL_QUADS);
}
