#ifndef __PLAYERSTAT__HH__
# define __PLAYERSTAT__HH__

# include <ctime>
# include <list>
# include <utility>
# include <map>
# include "Time.hh"
# include "Stat.hh"
# include "ePowerUpType.hh"

class PlayerStat
{
  typedef void (PlayerStat::*funcPtr)(void);

  std::list<std::pair<ePowerUpType, time_t> >	_activePowerup;
  std::map<ePowerUpType, funcPtr>		_startFuncs;
  std::map<ePowerUpType, funcPtr>		_endFuncs;

protected:
  Stat						_stat;

public:
  PlayerStat();
  ~PlayerStat();

  int			getSpeed() const;
  int			getRange() const;
  int			getCapacity() const;
  bool			getInvincibility() const;
  std::map<int,bool>	getBombsType() const;
  int			getScore() const;
  int			getLife() const;
  int			getInvincibilityRemainTime() const;

  void			setSpeed(int speed);
  void			setRange(int range);
  void			setCapacity(int capacity);
  void			setScore(int score);

  void			addLife();
  void			addScore(int score);
  void			addPowerup(ePowerUpType powerup, int duration);
  void			removeLife();

  void			monitorPowerUp();

  void			BombupStart(void);
  void			FireupStart(void);
  void			SpeedupStart(void);
  void			FullfireStart(void);
  void			InvincibilityStart(void);
  void			HeartStart(void);
  void			HardStart(void);
  void			FrozenStart(void);
  void			EjectStart(void);
  void			SmogStart(void);

  void			SpeedupEnd(void);
  void			NothingEnd(void);
  void			InvincibilityEnd(void);
};

#endif /* !__PLAYERSTAT__HH__ */
