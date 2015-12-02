#ifndef __BOMBS__HH__
# define __BOMBS__HH__

# include <list>
# include <map>
# include "Structs.hh"
# include "eBombType.hh"
# include "Position.hh"
# include "eDirection.hh"
# include "Map.hh"
# include "Graphic.hh"
# include "Explosions.hh"

class Explosions;

class Bombs
{
  typedef void (Bombs::*effectFunc)(t_bomb *) const;

  std::list<t_bomb *>			_bombs;
  std::list<t_bomb *>			_garbage;
  std::map<eBombType, effectFunc>	_effects;

  void				normalBombEffect(t_bomb *bomb) const;
  void				fullfireBombEffect(t_bomb *bomb) const;
  void				smogBombEffect(t_bomb *bomb) const;
  void				frozenBombEffect(t_bomb *bomb) const;
  void				hardBombEffect(t_bomb *bomb) const;
  void				ejectBombEffect(t_bomb *bomb) const;

public:

  Bombs(void);
  ~Bombs(void);

  t_bomb			*getBomb(void);
  bool				isBombed(const Position<int> & pos) const;
  void				removeBomb(t_bomb *bomb);
  const std::list<t_bomb *>&	getBombs(void) const;

  void				loadBomb(std::fstream & data, Player *p);

  bool				addBomb(const Position<int> & pos,
					Player * owner,
					Graphic & graphic,
					float countdown = 1);

  void				monitor(Graphic & graphic,
					float frame,
					const Explosions & explosions);
};

#endif /* !__BOMBS__HH__ */
