#ifndef CHAR_HPP_
# define CHAR_HPP_

# include <iostream>
# include <string>

# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "Geometry.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "Model.hh"
# include "OpenGL.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"
# include "Object.hh"

class Char : public Object {

private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  std::string	_path;

public:
  Char(unsigned char);
  Char(unsigned char, int);
  Char(unsigned char, int, int);
  Char(const std::string &, int, int);
  virtual ~Char();

  virtual bool	initialize();
  virtual void	draw(gdl::AShader &, gdl::Clock const &);
};

#endif /* !CHAR_HPP_ */
