#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <iostream>
# include "Position.hh"

# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "Geometry.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "../Includes/GDL_lib/includes/Model.hh"
# include "OpenGL.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

class Object {

protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public:

  Object();
  virtual ~Object();

  virtual bool	initialize();
  virtual void	draw(gdl::AShader &, gdl::Clock const &);
  void		translate(glm::vec3 const &);
  void		MoveAtPos(glm::vec3 const &);
  void		rotate(glm::vec3 const&, float);
  void	 	scale(glm::vec3 const&);
  void		putScale(glm::vec3 const&);
  glm::mat4	getTransformation();

  glm::vec3	getPosition() const;
  glm::vec3	getRotation() const;

  void		setPosition(const glm::vec3 &);
  void		setRotation(const glm::vec3 &);
};

#endif /* !OBJECT_HH_ */
