#ifndef PLAYERINPUT_HH_
# define PLAYERINPUT_HH_

# include "SdlContext.hh"

typedef enum	e_InputKey
  {
    UP_KEY = 0,
    LEFT_KEY,
    RIGHT_KEY,
    DOWN_KEY,
    BOMB_KEY,
    SWITCHBOMB_KEY,
    NO_KEY
  }		InputKey;

class PlayerInput
{
private:
  int	keyValues[6]; // voir enum
public:
  PlayerInput();
  PlayerInput(bool);
  PlayerInput(const PlayerInput&);
  ~PlayerInput();

  int	getKey(InputKey) const;
  void	setKeyValue(InputKey, int);
};

#endif /**/
