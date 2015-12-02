#include <fstream>
#include "StringConversion.hh"
#include "Random.hh"
#include "GenerateMap.hh"

GenerateMap::GenerateMap()
{
}

GenerateMap::~GenerateMap()
{
}

eBlockType	GenerateMap::getRandomPiece(bool includeHard)
{
  int	r = Random::getRand(100);

  if (r <= 50)
    return FLOOR;
  else if (r <= (75))
    return SOFTBLOCK;
  if (includeHard)
    return HARDBLOCK;
  return SOFTBLOCK;
}

void	GenerateMap::cleanCorners(MapType & map, unsigned int x, unsigned int y)
{
  map[0][0] = map[0][1] = map[1][0] =
    map[x - 1][0] = map[x - 1][1] = map[x - 2][0] =
    map[x - 1][y - 1] = map[x - 1][y -2] = map[x - 2][y - 1] =
    map[0][y - 1] = map[1][y - 1] = map[0][y - 2] = FLOOR;
}

void	GenerateMap::gen(int x1, int y1)
{
  MapType	map;
  unsigned int	x;
  unsigned int	y;

  if (x1 < 10 || y1 < 10)
    {
      std::cerr << "Map generated with minimal width/height (10/10)" << std::endl;
      x = x1 < 10 ? 10 : x1;
      y = y1 < 10 ? 10 : y1;
    }
  else
    {
      x = x1;
      y = y1;
    }
  for (unsigned int i = 0; i < x; ++i)
    {
      std::vector<eBlockType> tmp;
      for (unsigned int j = 0; j < y; ++j)
	{
	  if (i == 0 || j == 0 || i == (x - 1) || j == (y - 1))
	    tmp.push_back(GenerateMap::getRandomPiece(false));
	  else
	    tmp.push_back(GenerateMap::getRandomPiece());
	}
      map.push_back(tmp);
    }
  GenerateMap::cleanCorners(map, x, y);
  GenerateMap::draw(map);
}

void GenerateMap::draw(const MapType& map)
{
  std::ofstream	f("Maps/random.map");
  if (!f.is_open())
    return;
  f << "size " << map.size() << " " << map[0].size() << std::endl;
  for (unsigned int x = 0; x < map.size(); ++x)
    {
      for (unsigned int y = 0; y < map[x].size(); ++y)
	{
	  f << map[x][y];
	  if ((y + 1) < map[x].size())
	    f << " ";
	}
      f << std::endl;
    }
  f.close();
}
