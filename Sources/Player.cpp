#include <unistd.h>
#include "SdlContext.hh"
#include "Player.hh"

Player::Player(const Position<float>& pos, eType type, int id, eDirection dir, const std::string & skin, const PlayerInput &input):
  PlayerStat(),
  _id(id),
  _pos(pos),
  _input(input),
  _dir(dir),
  _type(type),
  _isAlive(true),
  _isMoving(false),
  _selected(NORMAL),
  _explosed(0),
  _stunned(0),
  _eject(false),
  _skin(skin),
  _camera(0)
{
}

Player::Player(int id, float x, float y, eType type, eDirection dir, bool alive):
  PlayerStat(),
  _camera(0)
{
  _id = id;
  _type = type;
  _pos.setX(x);
  _pos.setY(y);
  _dir = dir;
  _isAlive = alive;
}

Player::Player(std::fstream & data, const std::string skin, eType type) :
  PlayerStat(),
  _skin(skin),
  _camera(0)
{
  int	nb;

  _id = Utils::getNumData<int>(data);
  _pos.setY(Utils::getNumData<float>(data));
  _pos.setX(Utils::getNumData<float>(data));
  _dir = Utils::getNumData<eDirection>(data);
  _isAlive = Utils::getNumData<bool>(data);
  _type = type;
  _isMoving = Utils::getNumData<bool>(data);
  _selected = Utils::getNumData<eBombType>(data);
  _explosed = Utils::getNumData<float>(data);
  _stunned = Utils::getNumData<float>(data);
  _eject = Utils::getNumData<float>(data);
  changeUpKey(Utils::getNumData<int>(data));
  changeDownKey(Utils::getNumData<int>(data));
  changeLeftKey(Utils::getNumData<int>(data));
  changeRightKey(Utils::getNumData<int>(data));
  changeBombKey(Utils::getNumData<int>(data));
  changeSwitchBombKey(Utils::getNumData<int>(data));
  setSpeed(Utils::getNumData<int>(data));
  setRange(Utils::getNumData<int>(data));
  setCapacity(Utils::getNumData<int>(data));
  addPowerup(INVINCIBILITY, Utils::getNumData<bool>(data));
  setScore(Utils::getNumData<int>(data));
  data >> nb;
  for (; nb > 1; nb--)
    addLife();
  data >> nb;
  ePowerUpType	ref[6] = {SMOG, FULLFIRE, HARD, FROZEN, EJECT};
  bool status;
  for (int i = 0; i < nb; i++)
    {
      status = Utils::getNumData<bool>(data);
      if (i != 0 && status == true)
	addPowerup(ref[i - 1], 5);
    }
}

Player::~Player()
{
  if (_camera)
    delete _camera;
}

std::string	Player::getSkin() const
{
  return _skin;
}

eBombType Player::getSelectedBomb() const
{
  return _selected;
}

void	Player::changeBomb()
{
  int	select = static_cast<int>(_selected) - 14;

  while (_stat.bombs[(select % 7) + 15] == false)
    ++select;
  _selected = static_cast<eBombType>((select % 7) + 15);
}

void	Player::setExplosed(float duration)
{
  if (duration <= 0)
    _explosed = 0;
  else
    _explosed = duration;
}

float	Player::getExplosed() const
{
  return _explosed;
}

void	Player::setStunned(float duration)
{
  if (duration <= 0)
    _stunned = 0;
  else
    _stunned = duration;
}

float	Player::getStunned() const
{
  return _stunned;
}

void	Player::setEject(bool eject)
{
  _eject = eject;
}

bool	Player::getEject() const
{
  return _eject;
}

bool	Player::isAlive() const
{
  return _isAlive;
}

int	Player::getId() const
{
  return _id;
}

eType	Player::getType() const
{
  return this->_type;
}

float	Player::getPosX() const
{
  return _pos.getX();
}

float	Player::getPosY() const
{
  return _pos.getY();
}

Position<int>	Player::getPosition(void) const
{
  Position<int>	pos(_pos.getX(), _pos.getY());
  return pos;
}

void	Player::moveX(float x)
{
  _pos.setX(x);
}

void	Player::moveY(float y)
{
  _pos.setY(y);
}

void	Player::changeUpKey(int key)
{
  _input.setKeyValue(UP_KEY, key);
}

void	Player::changeBombKey(int key)
{
  _input.setKeyValue(BOMB_KEY, key);
}

void	Player::changeDownKey(int key)
{
  _input.setKeyValue(DOWN_KEY, key);
}

void	Player::changeLeftKey(int key)
{
  _input.setKeyValue(LEFT_KEY, key);
}

void	Player::changeRightKey(int key)
{
  _input.setKeyValue(RIGHT_KEY, key);
}

void	Player::changeSwitchBombKey(int key)
{
  _input.setKeyValue(SWITCHBOMB_KEY, key);
}

int	Player::getKey(InputKey key) const
{
  return _input.getKey(key);
}

void	Player::kill(void)
{
  if (!_isAlive || this->getInvincibility())
    return;
  this->removeLife();
  if (this->getLife() <= 0)
    _isAlive = false;
}

void	Player::setCamera(float mapX, float mapY)
{
  Camera  *cameraView = new Camera(getPosX(), getPosY(), mapX, mapY, getId());

  _camera = cameraView;
}

void	Player::updateCamera()
{
  _camera->update(getPosX(), getPosY());
}

glm::mat4	Player::getCamera() const
{
  return _camera->getTransformation();
}

eDirection	Player::getDir() const
{
  return (_dir);
}

void	Player::move(bool isMoving)
{
  _isMoving = isMoving;
}

bool	Player::isMoving(void) const
{
  return _isMoving;
}


void	Player::eject(const Map & map, Graphic & graphic)
{
  if (_eject)
    {
      Position<float> randomPos = map.getRandomPos();
      if (randomPos.getX() != -1 && randomPos.getY() != -1 )
	{
	  randomPos.setX(randomPos.getX() + 0.5f);
	  randomPos.setY(randomPos.getY() + 0.5f);
	  _pos = randomPos;
	  graphic.move(this, this->getPosX(), this->getPosY(), GRAPH_U, false);
	}
    }
  _eject = false;
}
