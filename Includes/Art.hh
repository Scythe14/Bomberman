#ifndef ART_HH_
# define ART_HH_

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

class Art : public Object
{
private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  std::string	_path;

public:
  Art(const std::string&);
virtual ~Art();
virtual bool	initialize();
virtual void	update(gdl::Clock const&, gdl::Input&);
virtual void	draw(gdl::AShader&, gdl::Clock const&);
};

#endif /* !ART_HH_ */
