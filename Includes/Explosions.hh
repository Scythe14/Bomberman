#ifndef __EXPLOSIONS__HH__
# define __EXPLOSIONS__HH__

# include <list>
# include <vector>
# include <map>
# include "Structs.hh"
# include "eDirection.hh"
# include "Position.hh"
# include "Player.hh"
# include "Graphic.hh"
# include "Map.hh"
# include "Powerup.hh"
# include "Bombs.hh"

class Bombs;

class Explosions
{
  typedef Position<int> (Explosions::*spreadFunc)(const t_bomb *, int) const;
  typedef void (Explosions::*effectFunc)(t_explosion *, Player *) const;

  float					_basicCountdown;
  int					_scoreDivisor;
  std::map<eBombType, effectFunc>	_effects;
  std::list<t_explosion *>		_explosions;
  std::list<t_explosion *>		_garbage;
  std::map<eDirection, spreadFunc>	_spreading;

  void	normalExplosionEffect(t_explosion * explosion, Player * player) const;
  void	fullfireExplosionEffect(t_explosion * explosion, Player * player) const;
  void	smogExplosionEffect(t_explosion * explosion, Player * player) const;
  void	frozenExplosionEffect(t_explosion * explosion, Player * player) const;
  void	hardExplosionEffect(t_explosion * explosion, Player * player) const;
  void	ejectExplosionEffect(t_explosion * explosion, Player * player) const;

  Position<int> spreadUp(const t_bomb *bomb, int i) const;
  Position<int> spreadBot(const t_bomb *bomb, int i) const;
  Position<int> spreadLeft(const t_bomb *bomb, int i) const;
  Position<int> spreadRight(const t_bomb *bomb, int i) const;
  Position<int> spreadUpAndLeft(const t_bomb *bomb, int i) const;
  Position<int> spreadUpAndRight(const t_bomb *bomb, int i) const;
  Position<int> spreadBotAndLeft(const t_bomb *bomb, int i) const;
  Position<int> spreadBotAndRight(const t_bomb *bomb, int i) const;

  void globalSpread(t_bomb *bomb, Map & map, Graphic & graphic, spreadFunc func);

public:
  Explosions();
  ~Explosions();


  void	explose(t_bomb * bomb, Map & map, Graphic & graphic);
  const std::list<t_explosion *> &	getExplosions(void) const;

  t_explosion	*getExplosion(void);
  void		removeExplosion(t_explosion *explosion);

  void		addExplosion(const t_bomb * bomb);
  void		addExplosion(const Position<int> & pos,
			     int range,
			     eDirection spreadDirection,
			     Player * player,
			     int points,
			     bool powerup,
			     eBombType type,
			     bool throughtHard,
			     bool throughtSoft,
			     float additionalCountdown);

  void		loadExplosion(std::fstream & data, Player *p);
  void		monitor(std::vector<Player *> & players, Graphic & graphic, float frame, Powerup & powerup);
  void		monitorBombs(Bombs & bombs, Map & map, Graphic & graphic);
};

#endif /* !__EXPLOSIONS__HH__ */
