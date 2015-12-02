#include "BomberException.hpp"
#include "../Includes/Model.hh"

Model::Model(const std::string &path)
  : _time(0), _init(false), _initModel(false)
{
  std::string::size_type	i;

  _entirepath = path;
  i = path.rfind('/');
  _path = path.substr(i + 1);
}

Model::~Model() {
}

void		Model::initialize(eModelType type)
{
  if (_init == false)
    _init = true;
  else
    return;
  if (_model.load(_entirepath.c_str()) == false)
    throw BomberException("Cannot load the Model Frame");
  if (type == PLAYERMODEL)
    {
      _rotation.x = 90.0;
      scale(glm::vec3(0.08, 0.08, 0.08));
      if (_path != "white.fbx")
	{
	  _position.z -= 0.4;
	  putScale(glm::vec3(0.92, 0.92, 0.92));
	  if (_model.createSubAnim(0, "start", 0, 20) == false ||
	      _model.createSubAnim(0, "reset", 6, 6) == false)
	    throw BomberException("Cannot load 3d model");
	}
      else
	{
	  if (_model.createSubAnim(0, "start", 0, 20) == false ||
	      _model.createSubAnim(0, "reset", 7, 7) == false)
	    throw BomberException("Cannot load 3d model");
	}
      _model.setCurrentSubAnim("reset");
    }
  else if (type == BOMBMODEL)
    {
      scale(glm::vec3(0.6, 0.6, 0.6));
      _rotation.x = 3;
      if (_model.createSubAnim(0, "start", 0, 20) == false)
	throw BomberException("Cannot load 3d model");
      _model.setCurrentSubAnim("start");
    }
  else
    {
      scale(glm::vec3(2, 2, 2));
      if (_model.createSubAnim(0, "start", 0, 55) == false)
	throw BomberException("Cannot load 3d model");
      _model.setCurrentSubAnim("start");
    }
  _model.pause(false);
}

void		Model::startAnim()
{
  if (_time == 0)
    {
      _model.setCurrentSubAnim("start");
      ++_time;
    }
}

void		Model::stopAnim()
{
  _model.setCurrentSubAnim("reset");
}

void		Model::draw(gdl::AShader &shader, gdl::Clock const &time)
{
  _model.draw(shader, getTransformation(), time.getElapsed());
  if (_time > 20)
    {
      _model.setCurrentSubAnim("reset");
      _time = 0;
    }
  else if (_time != 0)
    ++_time;
}

void		Model::setId(const int id)
 {
  _id = id;
}

Position<int>	Model::getPos() const
{
  return (_pos);
}

void	Model::setPos(const Position<int> & pos)
{
  _pos = pos;
}

const gdl::Model&	Model::getModel() const
{
  return (_model);
}

std::string	Model::getPath() const
{
  return (_path);
}

int		Model::getId() const
 {
  return (_id);
}

bool		Model::getInitModel() const
 {
  return (_initModel);
}
