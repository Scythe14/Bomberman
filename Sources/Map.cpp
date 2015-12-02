#include <fstream>
#include <string>
#include <map>
#include "Random.hh"
#include "Map.hh"

Map::Map()
{
}

Map::~Map()
{
}

void	Map::load(const char *path)
{
  std::fstream fs;
  std::string s;
  int	nb = 0;

  fs.open(path, std::fstream::in);
  if (fs.is_open())
    {
      fs >> s;
      if (s != "size")
	throw BomberException("Map file seems to be corrupted");
      s.clear();
      fs >> nb;
      _size.setX(nb);
      fs >> nb;
      _size.setY(nb);
      for (int i = 0; i < (this->_size.getX() * this->_size.getY()); ++i)
	{
	  fs >> nb;
	  _case.push_back(static_cast<eBlockType>(nb));
	  nb = 0;
	}
      fs.close();
    }

}

void	Map::loadPreviousMap(std::fstream & data)
{
  std::string str;
  int	nb = 0;

  data >> str;
  if (str != "size")
    throw BomberException("Savegame seems to be corrupted");
  str.clear();
  data >> nb;
  _size.setX(nb);
  data >> nb;
  _size.setY(nb);
  for (int i = 0; i < (this->_size.getX() * this->_size.getY()); ++i)
    {
      data >> nb;
      _case.push_back(static_cast<eBlockType>(nb));
      nb = 0;
    }
}

eBlockType	Map::getCase(int x, int y) const
{
  if (x < 0 || x >= _size.getX() || y < 0 || y >= _size.getY())
    return HARDBLOCK;
  return _case[(y * _size.getX()) + x];
}

std::vector<Position<int> >	Map::getEmptyCase() const
{
  std::vector<Position<int> >	empty;

  for (int x = 0; x < _size.getX(); ++x)
    {
      for (int y = 0; y < _size.getY(); ++y)
	{
	  if (_case[x + (y * _size.getX())] == FLOOR)
	    {
	      Position<int> p(x, y);
	      empty.push_back(p);
	    }
	}
    }
  return empty;
}

eBlockType		Map::explose(const Position<int> & pos, bool explose)
{
  if (pos.getY() >= _size.getY() || pos.getX() >= _size.getX() || pos.getX() < 0 || pos.getY() < 0)
    return HARDBLOCK;
  if (_case[pos.getY() * _size.getX() + pos.getX()] == SOFTBLOCK && explose)
    {
      _case[pos.getY() * _size.getX() + pos.getX()] = FLOOR;
      return SOFTBLOCK;
    }
  return _case[pos.getY() * _size.getX() + pos.getX()];
}

Position<int>	Map::getSize(void) const
{
  return _size;
}

const std::vector<eBlockType>&	Map::getCase(void) const
{
  return _case;
}

void	Map::emptyCase(int x, int y)
{
  int	i = y * _size.getX() + x;

  if (i < 0 || static_cast<unsigned int>(i) >= _case.size())
    return;
  _case[i] = FLOOR;
}

Position<int>	Map::getRandomPos() const
{
  Position<int>	randomPos;
  int	count = 1000;

  do
    {
      if (count <= 0)
	{
	  randomPos.setX(-1);
	  randomPos.setY(-1);
	  break;
	}
      randomPos.setX(Random::getRand(_size.getX()));
      randomPos.setY(Random::getRand(_size.getY()));
    }
  while (this->getCase(randomPos.getX(), randomPos.getY()) != FLOOR);
  return randomPos;
}
