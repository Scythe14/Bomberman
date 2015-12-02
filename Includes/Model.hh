#ifndef MODEL_HH_
# define MODEL_HH_

# include <iostream>
# include <string>
# include "Object.hh"

enum eModelType
  {
    PLAYERMODEL,
    BOMBMODEL,
    OTHER
  };

class Model : public Object {

private:
  gdl::Model	_model;
  gdl::Clock	_anim;
  std::string	_entirepath;
  std::string	_path;
  Position<int> _pos;
  unsigned	_id;
  unsigned	_time;
  bool		_init;
  bool		_initModel;

public:

  Model(const std::string &);
  ~Model();

  void			initialize(eModelType);
  void			draw(gdl::AShader &, gdl::Clock const &);
  bool			loadModel();
  void			startAnim();
  void			stopAnim();

  void			setId(const int);
  Position<int>		getPos() const;
  void			setPos(const Position<int> & pos);
  int			getId() const;
  bool			getInitModel() const;
  const gdl::Model&	getModel() const;
  std::string		getPath() const;
};

#endif /* !MODEL_HH_ */
