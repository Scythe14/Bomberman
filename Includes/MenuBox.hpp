#ifndef SKYBOX_HPP_
# define SKYBOX_HPP_

# include <iostream>
# include "Object.hh"

class MenuBox : public Object {

private:
  gdl::Texture			_texture1;
  gdl::Texture			_texture2;
  gdl::Texture			_texture3;
  gdl::Texture			_texture4;
  gdl::Texture			_texture5;
  gdl::Texture			_texture6;

  gdl::Geometry			_geometry1;
  gdl::Geometry			_geometry2;
  gdl::Geometry			_geometry3;
  gdl::Geometry			_geometry4;
  gdl::Geometry			_geometry5;
  gdl::Geometry			_geometry6;
  float				_speed;

public:
  virtual ~MenuBox() { ; }

  virtual bool initialize()
  {
    _speed = 10.0f;

    if (_texture1.load("Includes/HomeScreen/texture.tga") == false)
      return (false);
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

    _texture2.load("Includes/HomeScreen/texture.tga");
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

    _texture3.load("Includes/HomeScreen/texture.tga");
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

    _texture4.load("Includes/HomeScreen/texture.tga");
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

    _texture5.load("Includes/HomeScreen/texture.tga");
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

    _texture6.load("Includes/HomeScreen/texture.tga");
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

  virtual void update(gdl::Clock const &, gdl::Input &) {}

  virtual void draw(gdl::AShader &shader, gdl::Clock const &)
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

};

#endif /* !SKYBOX_HPP_ */
