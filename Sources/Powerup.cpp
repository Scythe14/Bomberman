#include "Random.hh"
#include "Powerup.hh"

Powerup::Powerup(int max, float ratio):
  _powerUp(),
  _max(max),
  _ratio(ratio)
{
}

Powerup::~Powerup()
{

}

void			Powerup::loadPowerup(std::fstream & data, Graphic & graphic)
{
  t_powerup		powerup;
  Position<int>		pos;

  pos.setX(Utils::getNumData<int>(data));
  pos.setY(Utils::getNumData<int>(data));
  powerup.first = pos;
  powerup.second = Utils::getNumData<ePowerUpType>(data);
  graphic.drawPowerUp(powerup.first, powerup.second);
  _powerUp.push_back(powerup);
}

std::list<t_powerup>	Powerup::getPowerUp() const
{
  return _powerUp;
}

void			Powerup::generate(const Position<int> & pos, Graphic & graphic)
{
  if (_max <= 0)
    return;

  if (Random::getRand(100000) < (100000 * _ratio))
    {
      t_powerup powerUp;
      powerUp.first = pos;
      powerUp.second = static_cast<ePowerUpType>(Random::getRand(10) + 5);
      _powerUp.push_back(powerUp);
      --_max;
      graphic.drawPowerUp(powerUp.first, powerUp.second);
    }
}

void	Powerup::monitor(std::vector<Player *> players, Graphic & graphic)
{
  std::list<t_powerup>::iterator	toErase;
  bool					isErasable = false;

  for (std::list<t_powerup>::iterator it = _powerUp.begin(); it != _powerUp.end(); ++it)
    {
      if (isErasable)
	{
	  isErasable = false;
	  _powerUp.erase(toErase);
	}
      for (std::vector<Player *>::iterator itp = players.begin(); itp != players.end(); ++itp)
	{
	  if ((*itp)->getPosition() == it->first && (*itp)->isAlive())
	    {
	      ++_max;
	      (*itp)->addPowerup(it->second, 5);
	      graphic.removePowerUp(it->first);
	      toErase = it;
	      isErasable = true;
	    }
	}
    }
  if (isErasable)
    _powerUp.erase(toErase);
}

void	Powerup::erase(Position<int> pos, Graphic & graphic, eBombType type)
{
  int	toReplace = FLOOR;

  for (std::list<t_powerup>::iterator it = _powerUp.begin(); it != _powerUp.end(); ++it)
    {
      if (it->first == pos)
	{
	  ++_max;
	  _powerUp.erase(it);
	  if (type == NORMAL)
	    toReplace = XPLOS;
	  else if (type == HARDBOMB)
	    toReplace = HARDBOMB;
	  graphic.removePowerUp(it->first, toReplace);
	  return;
	}
    }
}
