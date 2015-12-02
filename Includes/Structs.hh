#ifndef __STRUCTS__HH__
# define __STRUCTS__HH__

# include "eBombType.hh"
# include "Position.hh"
# include "eDirection.hh"
# include "eStatus.hh"
# include "Player.hh"

typedef struct	s_explosion
{
  Position<int>	_pos;
  int		_range;
  eDirection	_spreadDirection;
  eBombType	_type;
  float		_countdown;
  bool		_first;
  Player *	_owner;
  int		_ownerId;
  int		_points;
  bool		_powerup;
  bool		_throughtHard;
  bool		_throughtSoft;
}		t_explosion;

typedef struct	s_bomb
{
  Position<int>	_pos;
  int		_range;
  eBombType	_type;
  eDirection	_spreadDirection;
  float		_countdown;
  float		_explosionsCountDown;
  eStatus	_status;
  Player *	_owner;
  int		_ownerId;
  int		_points;
  bool		_throughtHard;
  bool		_throughtSoft;
}		t_bomb;

#endif /* !__STRUCTS__HH__ */
