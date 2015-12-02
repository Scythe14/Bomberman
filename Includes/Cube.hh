#ifndef CUBE_HH_
# define CUBE_HH_

# include <iostream>
# include "Object.hh"
# include "Position.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

class Cube : public Object {

private:
  glm::mat4		_transform;
  Position<int>		_pos;
  int			_type;
public:

  Cube();
  ~Cube();

  glm::mat4		getTransformation();
  const glm::mat4&	getTransform() const;
  Position<int>		getPos() const;
  void			setPos(const Position<int> &);
  int			getType() const;
  void			setType(int type);
};

#endif /* !CUBE_HH_ */
