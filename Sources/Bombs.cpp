#include <list>
#include "Bombs.hh"
#include "Position.hh"
#include "eBombType.hh"
#include "eDirection.hh"
#include "Map.hh"

Bombs::Bombs(void):
  _bombs()
{
  _effects[NORMAL] = &Bombs::normalBombEffect;
  _effects[SMOGBOMB] = &Bombs::smogBombEffect;
  _effects[FULLFIREBOMB] = &Bombs::fullfireBombEffect;
  _effects[HARDBOMB] = &Bombs::hardBombEffect;
  _effects[FROZENBOMB] = &Bombs::frozenBombEffect;
  _effects[EJECTBOMB] = &Bombs::ejectBombEffect;
}

Bombs::~Bombs(void)
{
  for (std::list<t_bomb *>::iterator it = _bombs.begin(); it != _bombs.end(); ++it)
    delete *it;
}

void Bombs::loadBomb(std::fstream & data, Player * p)
{
  t_bomb	*bomb = this->getBomb();

  bomb->_pos.setX(Utils::getNumData<int>(data));
  bomb->_pos.setY(Utils::getNumData<int>(data));
  bomb->_range = Utils::getNumData<int>(data);
  bomb->_type = Utils::getNumData<eBombType>(data);
  bomb->_spreadDirection = Utils::getNumData<eDirection>(data);
  bomb->_countdown = Utils::getNumData<float>(data);
  bomb->_explosionsCountDown = Utils::getNumData<float>(data);
  bomb->_status = Utils::getNumData<eStatus>(data);
  bomb->_owner = p;
  bomb->_ownerId =0;
  bomb->_points = Utils::getNumData<int>(data);
  bomb->_throughtHard = Utils::getNumData<bool>(data);
  bomb->_throughtSoft = Utils::getNumData<bool>(data);
  _bombs.push_back(bomb);
}

t_bomb	*Bombs::getBomb(void)
{
  t_bomb	*bomb;

  if (!(_garbage.empty()))
    {
      bomb = _garbage.front();
      _garbage.pop_front();
    }
  else
    bomb = new t_bomb;
  return bomb;
}

void		Bombs::removeBomb(t_bomb *bomb)
{
  _garbage.push_back(bomb);
}


void				Bombs::monitor(Graphic & graphic, float frame, const Explosions & explosions)
{
  std::list<t_bomb *>::iterator	toErase;
  bool				isErasable = false;
  const std::list<t_explosion *> &exploList = explosions.getExplosions();

  for (std::list<t_bomb *>::iterator it = _bombs.begin(); it != _bombs.end(); ++it)
    {
      if (isErasable)
	{
	  this->removeBomb(*toErase);
	  _bombs.erase(toErase);
	  isErasable = false;
	}
      if ((*it)->_status == STOP)
	for (std::list<t_explosion *>::const_iterator ite = exploList.begin(); ite != exploList.end(); ++ite)
	  if ((*ite)->_pos == (*it)->_pos && (*ite)->_type != SMOGBOMB)
	    {
	      (*it)->_status = DOING;
	      break;
	    }
      (*it)->_countdown -= frame;
      if ((*it)->_countdown <= 0 && (*it)->_status == STOP)
	(*it)->_status = DOING;
      if ((*it)->_status == DONE)
	{
	  isErasable = true;
	  toErase = it;
	  graphic.removeBomb((*it)->_pos, (*it)->_type);
	}
    }
  if (isErasable)
    {
      this->removeBomb(*toErase);
      _bombs.erase(toErase);
    }
}

bool		 Bombs::addBomb(const Position<int> & pos,
				Player * owner,
				Graphic & graphic,
				float countdown)
{
  t_bomb	*bomb = this->getBomb();
  int		bombAmount = 0;

  for (std::list<t_bomb *>::iterator it = _bombs.begin(); it != _bombs.end(); ++it)
    {
      if ((*it)->_pos == pos)
	return false;
      if ((*it)->_owner == owner)
	bombAmount += 1;
    }
  if (owner->getCapacity() <= bombAmount)
    return false;
  bomb->_pos = pos;
  bomb->_range = owner->getRange();
  bomb->_type = owner->getSelectedBomb();
  bomb->_countdown = countdown;
  bomb->_status = STOP;
  bomb->_owner = owner;
  bomb->_explosionsCountDown = 0;
  (this->*(_effects[bomb->_type]))(bomb);
  _bombs.push_back(bomb);
  graphic.drawBomb(pos);
  return true;
}

bool		Bombs::isBombed(const Position<int> & pos) const
{
  for (std::list<t_bomb *>::const_iterator it = _bombs.begin(); it != _bombs.end(); ++it)
    {
      if ((*it)->_pos == pos)
	return true;
    }
  return false;
}

const std::list<t_bomb *>&	Bombs::getBombs() const
{
  return (_bombs);
}

void	Bombs::normalBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = NESW;
  bomb->_points = 100;
  bomb->_throughtHard = false;
  bomb->_throughtSoft = true;
}

void	Bombs::fullfireBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = ALL;
  bomb->_points = 80;
  bomb->_explosionsCountDown = 2;
  bomb->_throughtHard = false;
  bomb->_throughtSoft = true;
}

void	Bombs::smogBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = ALL;
  bomb->_range = 2;
  bomb->_points = 0;
  bomb->_explosionsCountDown = 4;
  bomb->_throughtHard = false;
  bomb->_throughtSoft = false;
}

void	Bombs::frozenBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = CORNERS;
  bomb->_points = 20;
  bomb->_explosionsCountDown = 2.5f;
  bomb->_throughtHard = false;
  bomb->_throughtSoft = false;
}

void	Bombs::hardBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = NESW;
  bomb->_range *= 5;
  bomb->_points = 50;
  bomb->_throughtHard = true;
  bomb->_throughtSoft = true;
}

void	Bombs::ejectBombEffect(t_bomb *bomb) const
{
  bomb->_spreadDirection = NESW;
  bomb->_points = 60;
  bomb->_throughtHard = false;
  bomb->_throughtSoft = false;
}
