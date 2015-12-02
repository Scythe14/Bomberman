#ifndef __POWERUP_HH__
# define __POWERUP_HH__

# include <list>
# include <vector>
# include <utility>
# include <fstream>
# include "Position.hh"
# include "Player.hh"
# include "Graphic.hh"

typedef std::pair<Position<int>, ePowerUpType > t_powerup;

class Powerup
{
  std::list<t_powerup>	_powerUp;
  int			_max;
  float			_ratio;

public:
  Powerup(int max, float ratio);
  ~Powerup();

  void			loadPowerup(std::fstream & data, Graphic & graphic);
  std::list<t_powerup>	getPowerUp() const;
  void			generate(const Position<int> &pos, Graphic & Graphic);
  void			monitor(std::vector<Player *> players, Graphic & Graphic);
  void			erase(Position<int> pos, Graphic & graphic, eBombType type = NOBOMB);
};

#endif /* !__POWERUP_HH__ */
