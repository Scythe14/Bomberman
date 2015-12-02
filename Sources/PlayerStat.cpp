#include "PlayerStat.hh"

PlayerStat::PlayerStat()
{
  _stat.speed = 6;
  _stat.capacity = 1;
  _stat.range = 2;
  _stat.hearts = 1;
  _stat.invincible = 0;
  _stat.score = 0;

  _stat.bombs[NORMAL] = true;
  _stat.bombs[SMOGBOMB] = false;
  _stat.bombs[FULLFIREBOMB] = false;
  _stat.bombs[HARDBOMB] = false;
  _stat.bombs[FROZENBOMB] = false;
  _stat.bombs[EJECTBOMB] = false;

  _startFuncs[BOMBUP] = &PlayerStat::BombupStart;
  _startFuncs[FIREUP] = &PlayerStat::FireupStart;
  _startFuncs[SPEEDUP] = &PlayerStat::SpeedupStart;
  _startFuncs[FULLFIRE] = &PlayerStat::FullfireStart;
  _startFuncs[INVINCIBILITY] = &PlayerStat::InvincibilityStart;
  _startFuncs[HEART] = &PlayerStat::HeartStart;
  _startFuncs[HARD] = &PlayerStat::HardStart;
  _startFuncs[FROZEN] = &PlayerStat::FrozenStart;
  _startFuncs[EJECT] = &PlayerStat::EjectStart;
  _startFuncs[SMOG] = &PlayerStat::SmogStart;

  _endFuncs[BOMBUP] = &PlayerStat::NothingEnd;
  _endFuncs[FIREUP] = &PlayerStat::NothingEnd;
  _endFuncs[SPEEDUP] = &PlayerStat::SpeedupEnd;
  _endFuncs[FULLFIRE] = &PlayerStat::NothingEnd;
  _endFuncs[INVINCIBILITY] = &PlayerStat::InvincibilityEnd;
  _endFuncs[HEART] = &PlayerStat::NothingEnd;
  _endFuncs[HARD] = &PlayerStat::NothingEnd;
  _endFuncs[FROZEN] = &PlayerStat::NothingEnd;
  _endFuncs[EJECT] = &PlayerStat::NothingEnd;
  _endFuncs[SMOG] = &PlayerStat::NothingEnd;
}

PlayerStat::~PlayerStat(void)
{
}

void	PlayerStat::setScore(int score)
{
  _stat.score = score;
}

void	PlayerStat::setRange(int range)
{
  _stat.range = range;
}

bool	PlayerStat::getInvincibility() const
{
  return _stat.invincible;
}

void	PlayerStat::addScore(int score)
{
  _stat.score += score;
}

void	PlayerStat::addLife()
{
  _stat.hearts += 1;
}

void	PlayerStat::removeLife()
{
  _stat.hearts -= 1;
}

std::map<int,bool>	PlayerStat::getBombsType() const
{
  return _stat.bombs;
}

int	PlayerStat::getLife() const
{
  return _stat.hearts;
}

void	PlayerStat::setSpeed(int speed)
{
  if (speed >= 3)
    _stat.speed = speed;
}

int	PlayerStat::getSpeed(void) const
{
  return _stat.speed;
}

int	PlayerStat::getScore(void) const
{
  return _stat.score;
}

int	PlayerStat::getRange(void) const
{
  return _stat.range;
}

void	PlayerStat::setCapacity(int capacity)
{
  _stat.capacity = capacity;
}

int	PlayerStat::getCapacity(void) const
{
  return _stat.capacity;
}

void	PlayerStat::BombupStart(void)
{
  if (_stat.capacity < 8)
    _stat.capacity += 1;
}

void	PlayerStat::FireupStart(void)
{
  if (_stat.range < 9)
    _stat.range += 1;
}

void	PlayerStat::SpeedupStart(void)
{
  _stat.speed += 1;
}

void	PlayerStat::FullfireStart(void)
{
  _stat.bombs[FULLFIREBOMB] = true;
}

void	PlayerStat::HardStart(void)
{
  _stat.bombs[HARDBOMB] = true;
}

void	PlayerStat::FrozenStart(void)
{
  _stat.bombs[FROZENBOMB] = true;
}
void	PlayerStat::EjectStart(void)
{
  _stat.bombs[EJECTBOMB] = true;
}

void	PlayerStat::SmogStart(void)
{
  _stat.bombs[SMOGBOMB] = true;
}

void	PlayerStat::InvincibilityStart(void)
{
  _stat.invincible = true;
}

void	PlayerStat::HeartStart(void)
{
  if (_stat.hearts < 5)
    _stat.hearts += 1;
}

void	PlayerStat::SpeedupEnd()
{
  _stat.speed -= 1;
}

void	PlayerStat::InvincibilityEnd()
{
  _stat.invincible = false;
}

void	PlayerStat::NothingEnd()
{
  return;
}

void		PlayerStat::addPowerup(ePowerUpType powerup, int duration)
{
  time_t				now = Time::getCurrentTime();
  std::pair<ePowerUpType, time_t>	activePowerup(powerup, now + duration);

  for (std::list<std::pair<ePowerUpType, time_t> >::iterator it = _activePowerup.begin(); it != _activePowerup.end(); ++it)
    {
      if (it->first == powerup)
	{
	  it->second = now + duration;
	  (this->*(_startFuncs[powerup]))();
	  return;
	}
    }
  _activePowerup.push_back(activePowerup);
  (this->*(_startFuncs[powerup]))();
}

int   PlayerStat::getInvincibilityRemainTime() const
{
  time_t	now = Time::getCurrentTime();

  for (std::list<std::pair<ePowerUpType, time_t> >::const_iterator it = _activePowerup.begin(); it != _activePowerup.end(); ++it)
    {
      if (it->first == INVINCIBILITY)
	return it->second - now;
    }
  return (0);
}


void	PlayerStat::monitorPowerUp(void)
{
  time_t						now = Time::getCurrentTime();
  std::list<std::pair<ePowerUpType, time_t> >::iterator	toErase;
  bool							isErasable = false;

  for (std::list<std::pair<ePowerUpType, time_t> >::iterator it = _activePowerup.begin(); it != _activePowerup.end(); ++it)
    {
      if (isErasable)
	{
	  (this->*(_endFuncs[toErase->first]))();
	  _activePowerup.erase(toErase);
	  isErasable = false;
	}
      if (it->second < now)
	{
	  isErasable = true;
	  toErase = it;
	}
    }
  if (isErasable)
    {
      (this->*(_endFuncs[toErase->first]))();
      _activePowerup.erase(toErase);
    }
}
