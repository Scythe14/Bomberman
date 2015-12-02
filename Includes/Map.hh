#ifndef MAP_HH_
# define MAP_HH_

# include <vector>
# include "Position.hh"
# include "eBlockType.hh"
# include "BomberException.hpp"

class	Map
{
  Position<int>			_size;
  std::vector<eBlockType>	_case;

public:
  Map();
  ~Map();
  void				load(const char*);
  void				loadPreviousMap(std::fstream & data);
  eBlockType			getCase(int, int) const;
  eBlockType			explose(const Position<int> & pos, bool explose);
  Position<int>			getSize(void) const;
  const std::vector<eBlockType>	&getCase(void) const;
  Position<int>			getRandomPos() const;
  std::vector<Position<int> >	getEmptyCase() const;
  void				emptyCase(int x, int y);
};

#endif /* !MAP_HH_ */
