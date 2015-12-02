#ifndef __GENERATEMAP_HH__
# define __GENERATEMAP_HH__

# include <vector>
# include <string>
# include "eBlockType.hh"

class GenerateMap
{
  typedef std::vector<std::vector<eBlockType> > MapType;

  GenerateMap();
  ~GenerateMap();
  static void		cleanCorners(MapType &map, unsigned int x, unsigned int y);
  static eBlockType	getRandomPiece(bool includeHard = true);
  static void		draw(const MapType& map);

public:
  static void	gen(int x, int y);
};

#endif /* !__GENERATEMAP_HH__ */
