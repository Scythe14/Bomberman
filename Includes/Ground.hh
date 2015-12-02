#ifndef GROUND_HH_
# define GROUND_HH_

# include <iostream>
# include <string>
# include "Object.hh"
# include "Geometry.hh"
# include "Texture.hh"

class Ground : public Object {

private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  std::string	_path;
  float		_x;
  float		_y;

public:
  Ground(const std::string &, float, float);
  ~Ground();

  bool		initialize();
  void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif /* !GROUND_HH_ */
