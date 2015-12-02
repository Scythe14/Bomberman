#include <list>
#include <vector>
#include "Explosions.hh"
#include "eDirection.hh"
#include "Position.hh"
#include "Bombs.hh"
#include "Player.hh"

Explosions::Explosions():
  _basicCountdown(0.5),
  _scoreDivisor(10)
{
  _spreading[NONE] = 0;
  _spreading[LEFT] = &Explosions::spreadLeft;
  _spreading[UPPERLEFT] = &Explosions::spreadUpAndLeft;
  _spreading[UP] = &Explosions::spreadUp;
  _spreading[UPPERRIGHT] = &Explosions::spreadUpAndRight;
  _spreading[RIGHT] = &Explosions::spreadRight;
  _spreading[BOTTOMRIGHT] = &Explosions::spreadBotAndRight;
  _spreading[BOTTOM] = &Explosions::spreadBot;
  _spreading[BOTTOMLEFT] = &Explosions::spreadBotAndLeft;

  _effects[NORMAL] = &Explosions::normalExplosionEffect;
  _effects[SMOGBOMB] = &Explosions::smogExplosionEffect;
  _effects[FULLFIREBOMB] = &Explosions::fullfireExplosionEffect;
  _effects[HARDBOMB] = &Explosions::hardExplosionEffect;
  _effects[FROZENBOMB] = &Explosions::frozenExplosionEffect;
  _effects[EJECTBOMB] = &Explosions::ejectExplosionEffect;
}

Explosions::~Explosions()
{
  for (std::list<t_explosion *>::iterator it = _explosions.begin(); it != _explosions.end(); ++it)
    delete *it;
  for (std::list<t_explosion *>::iterator it = _garbage.begin(); it != _garbage.end(); ++it)
    delete *it;
}

t_explosion	*Explosions::getExplosion(void)
{
  t_explosion	*explosion;

  if (!(_garbage.empty()))
    {
      explosion = _garbage.front();
      _garbage.pop_front();
    }
  else
    explosion = new t_explosion;
  return explosion;
}

void		Explosions::removeExplosion(t_explosion *explosion)
{
  _garbage.push_back(explosion);
}

void Explosions::addExplosion(const t_bomb * bomb)
{
  this->addExplosion(bomb->_pos, bomb->_range, bomb->_spreadDirection, bomb->_owner, bomb->_points, false, bomb->_type, bomb->_throughtHard, bomb->_throughtSoft, bomb->_explosionsCountDown);
}

void Explosions::addExplosion(const Position<int> & pos, int range, eDirection spreadDirection, Player * owner, int points, bool powerup, eBombType type, bool throughtHard, bool throughtSoft, float additionalCountdown)
{
  t_explosion	*explosion = this->getExplosion();

  for (std::list<t_explosion *>::iterator it = _explosions.begin(); it != _explosions.end(); ++it)
    {
      if ((*it)->_pos == pos)
	{
	  (*it)->_countdown = _basicCountdown + additionalCountdown;
	  (*it)->_owner = owner;
	  return;
	}
    }
  explosion->_pos = pos;
  explosion->_type = type;
  explosion->_throughtHard = throughtHard;
  explosion->_throughtSoft = throughtSoft;
  explosion->_range = range;
  explosion->_spreadDirection = spreadDirection;
  explosion->_first = false; //WARNING - osef je l'utilise plus je crois, grep pour savoir
  explosion->_countdown = _basicCountdown + additionalCountdown;
  explosion->_powerup = powerup;
  explosion->_owner = owner;
  explosion->_points = points;
  _explosions.push_back(explosion);
}

void Explosions::loadExplosion(std::fstream & data,  Player * p )
{
  t_explosion	*explosion = this->getExplosion();

  explosion->_pos.setX(Utils::getNumData<int>(data));
  explosion->_pos.setY(Utils::getNumData<int>(data));
  explosion->_range = Utils::getNumData<int>(data);
  explosion->_spreadDirection = Utils::getNumData<eDirection>(data);
  explosion->_type = Utils::getNumData<eBombType>(data);
  explosion->_countdown = Utils::getNumData<float>(data);
  explosion->_first = Utils::getNumData<bool>(data);
  explosion->_owner = p;
  explosion->_ownerId = 0;//player->getId();
  explosion->_points = Utils::getNumData<int>(data);
  explosion->_powerup = Utils::getNumData<bool>(data);
  explosion->_throughtHard = Utils::getNumData<bool>(data);
  explosion->_throughtSoft = Utils::getNumData<bool>(data);
  _explosions.push_back(explosion);
}

void	Explosions::monitor(std::vector<Player *> & players, Graphic & graphic, float frame, Powerup & powerup)
{
  std::list<t_explosion *>::iterator	toErase;
  bool					isErasable = false;

  for (std::list<t_explosion *>::iterator it = _explosions.begin(); it != _explosions.end(); ++it)
    {
      for (std::vector<Player *>::iterator itp = players.begin(); itp != players.end(); ++itp)
	if ((*itp)->isAlive() && (*itp)->getExplosed() <= 0 && (*itp)->getPosition() == (*it)->_pos)
	  (this->*(_effects[(*it)->_type]))(*it, *itp);
      if (isErasable)
	{
	  this->removeExplosion(*toErase);
	  _explosions.erase(toErase);
	  isErasable = false;
	}
      (*it)->_countdown -= frame;
      if ((*it)->_countdown <= 0)
	{
	  graphic.removeExplosion((*it)->_pos);
	  if ((*it)->_powerup)
	    powerup.generate((*it)->_pos, graphic);
	  toErase = it;
	  isErasable = true;
 	}
      else
	powerup.erase((*it)->_pos, graphic, (*it)->_type);
    }
  if (isErasable)
    {
      this->removeExplosion(*toErase);
      _explosions.erase(toErase);
    }
}

void	Explosions::monitorBombs(Bombs & bombs, Map & map, Graphic & graphic)
{
  std::list<t_bomb *>		list = bombs.getBombs();

  for (std::list<t_bomb *>::iterator it = list.begin(); it != list.end(); ++it)
    {
      if ((*it)->_status == DOING)
	this->explose(*it, map, graphic);
    }
}

const std::list<t_explosion *> &	Explosions::getExplosions(void) const
{
  return _explosions;
}

void Explosions::explose(t_bomb * bomb, Map & map, Graphic & graphic)
{
  bomb->_status = DONE;
  this->addExplosion(bomb);
  for (int i = 1; i <= 128; i *= 2)
    {
      if (bomb->_spreadDirection & i)
	this->globalSpread(bomb, map, graphic, _spreading[static_cast<eDirection>(i)]);
    }
}

void Explosions::globalSpread(t_bomb *bomb, Map & map, Graphic & graphic, spreadFunc func)
{
  eBlockType	explosed;

  for (int i = 1; i <= bomb->_range; ++i)
    {
      bool		powerup = false;
      Position<int>	tmp = (this->*(func))(bomb, i);
      explosed = map.explose(tmp, bomb->_throughtSoft);
      if (explosed == HARDBLOCK)
	{
	  if (bomb->_throughtHard)
	    continue;
	  else
	    break;
	}
      else if (explosed == SOFTBLOCK)
	{
	  if (!(bomb->_throughtSoft))
	    break;
	  powerup = true;
	  graphic.removeBlock(tmp);
	  if (bomb->_owner->isAlive())
	    bomb->_owner->addScore(bomb->_points / _scoreDivisor);
	}
      graphic.drawExplosion(tmp, bomb->_type);
      this->addExplosion(tmp, bomb->_range, bomb->_spreadDirection, bomb->_owner, bomb->_points, powerup, bomb->_type, bomb->_throughtHard, bomb->_throughtSoft, bomb->_explosionsCountDown);
      if (explosed == SOFTBLOCK && (bomb->_throughtSoft && !(bomb->_throughtHard)))
	break;
    }
}

Position<int> Explosions::spreadUp(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setY(bomb->_pos.getY() - i);

  return tmp;
}

Position<int> Explosions::spreadBot(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;
  tmp.setY(bomb->_pos.getY() + i);

  return tmp;
}

Position<int> Explosions::spreadLeft(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setX(bomb->_pos.getX() - i);

  return tmp;
}

Position<int> Explosions::spreadRight(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setX(bomb->_pos.getX() + i);
  return tmp;
}

Position<int> Explosions::spreadUpAndLeft(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setX(bomb->_pos.getX() - i);
  tmp.setY(bomb->_pos.getY() - i);

  return tmp;
}

Position<int> Explosions::spreadUpAndRight(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setY(bomb->_pos.getY() - i);
  tmp.setX(bomb->_pos.getX() + i);

  return tmp;
}

Position<int> Explosions::spreadBotAndLeft(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setY(bomb->_pos.getY() + i);
  tmp.setX(bomb->_pos.getX() - i);

  return tmp;
}

Position<int> Explosions::spreadBotAndRight(const t_bomb *bomb, int i) const
{
  Position<int>	tmp = bomb->_pos;

  tmp.setY(bomb->_pos.getY() + i);
  tmp.setX(bomb->_pos.getX() + i);

  return tmp;
}

void	Explosions::normalExplosionEffect(t_explosion *explosion, Player * player) const
{
  player->kill();
  player->setExplosed(0.5f);
  if (player != explosion->_owner  && explosion->_owner->isAlive())
    explosion->_owner->addScore(explosion->_points);
}

void	Explosions::fullfireExplosionEffect(t_explosion * explosion, Player * player) const
{
  player->kill();
  player->setExplosed(0.5f);
  if (player != explosion->_owner  && explosion->_owner->isAlive())
    explosion->_owner->addScore(explosion->_points);
}

void	Explosions::smogExplosionEffect(t_explosion * explosion, Player * player) const
{
  player->setExplosed(0.5f);
  if (player != explosion->_owner  && explosion->_owner->isAlive())
    explosion->_owner->addScore(explosion->_points);
  player->setSpeed(player->getSpeed() - 1);
}

void	Explosions::frozenExplosionEffect(t_explosion * explosion, Player * player) const
{
  player->setExplosed(3);
  if (player != explosion->_owner  && explosion->_owner->isAlive())
    explosion->_owner->addScore(explosion->_points);
  player->setStunned(2.5f);
}

void	Explosions::hardExplosionEffect(t_explosion * explosion, Player * player) const
{
  player->kill();
  player->setExplosed(0.5f);
  if (player != explosion->_owner  && explosion->_owner->isAlive())
    explosion->_owner->addScore(explosion->_points);
}

void	Explosions::ejectExplosionEffect(t_explosion * explosion, Player * player) const
{
  player->setExplosed(0.5f);
  player->setEject(true);
  explosion->_owner->addScore(0);
}
