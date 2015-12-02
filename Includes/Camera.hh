#ifndef CAMERA_HH_
# define CAMERA_HH_

# include "Position.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

class	Camera
{
private:
  int		_id;
  float		_x;
  float		_y;
  glm::mat4	_transformation;
public:
  Camera(float, float, float, float, int);
  ~Camera();
  void		update(float, float);
  void		updateHigh(float, float);
  glm::mat4	getTransformation() const;
};
#endif
