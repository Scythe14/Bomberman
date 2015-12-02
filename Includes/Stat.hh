#ifndef STAT_HH_
# define STAT_HH_

# include <map>
# include "eBombType.hh"

typedef struct
{
  float			speed;
  int			capacity;
  int			range;
  int			hearts;
  bool			invincible;
  int			score;
  std::map<int,bool>	bombs;
}		Stat;

#endif /* !STAT_HH_ */
