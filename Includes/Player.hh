#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <iostream>
# include <fstream>
# include "Position.hh"
# include "eDirection.hh"
# include "PlayerInput.hh"
# include "PlayerStat.hh"
# include "eType.hh"
# include "Camera.hh"
# include "Map.hh"
# include "Graphic.hh"
# include "utils.hpp"

class Graphic;

class	Player : public PlayerStat
{
protected:
  typedef void (Player::*ejectFunc)(const Map &);

  int			_id;
  Position<float>	_pos;
  PlayerInput		_input;
  eDirection		_dir;
  eType			_type;
  bool			_isAlive;
  bool			_isMoving;
  eBombType		_selected;
  float			_explosed;
  float			_stunned;
  bool			_eject;
  const std::string	_skin;
  Camera		*_camera;

public:
  Player(int id, float x, float y, eType type, eDirection dir, bool alive);
  Player(const Position<float> & pos,
	 eType type,
	 int id,
	 eDirection dir,
	 const std::string & skin,
	 const PlayerInput & _input);
  Player(std::fstream &data, const std::string skin, eType type);
  virtual ~Player ();

  bool		isAlive() const;
  void		changeBomb();
  void		eject(const Map & map, Graphic & graphic);
  void		kill(void);
  void		updateCamera();
  void		move(bool);
  bool		isMoving(void) const;

  eBombType	getSelectedBomb() const;
  float		getExplosed() const;
  bool		getEject() const;
  float		getStunned() const;
  int		getId() const;
  eType		getType() const;
  float		getPosX() const;
  float		getPosY() const;
  std::string	getSkin() const;
  eDirection	getDir() const;
  Position<int>	getPosition(void) const;
  int		getKey(InputKey key) const;
  glm::mat4	getCamera() const;

  void		setEject(bool ejected);
  void		setExplosed(float duration);
  void		setStunned(float duration);
  void		setCamera(float, float);

  void		moveX(float x);
  void		moveY(float y);

  void		changeUpKey(int key);
  void		changeDownKey(int key);
  void		changeLeftKey(int key);
  void		changeRightKey(int key);
  void		changeBombKey(int key);
  void		changeSwitchBombKey(int key);
};

#endif /* !PLAYER_HH_ */
