#ifndef	AI_HH_
# define AI_HH_

class	AI;

# include <string>
# include "Bomberman.hh"
# include "eAction.hh"

#define ABS(x) (x) < 0.0000 ? -(x) : (x)

class Bomberman;

class	AI : public Player
{
  eAction	    _action;
  Bomberman	    *_game;
  Position<int>	_sMapSize;
  eAction	    _prevAvoid;
  int		    _avoidAcount;
  std::vector<eBlockType> &_sMap;

  eAction getPosNearPlayer() const;
  eAction detectBomb(eAction tmp);
  eAction avoidLeftBomb();
  eAction avoidRightBomb();
  eAction avoidUpBomb();
  eAction avoidDownBomb();

public:
  AI(const Position<float> & pos, eType type, int id, eDirection dir, const std::string & skin, const PlayerInput& input, Bomberman*);
  AI(std::fstream &data, const std::string& skin, eType type, Bomberman* game);
  ~AI();
  void	loop();
  eAction getAction() const;
  void	setAction(eAction);
};

#endif	/* !AI_HH_ */
