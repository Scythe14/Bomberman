#ifndef __POSITION__HH__
# define __POSITION__HH__

# include <ostream>

template<typename T>
class Position
{
  T	_x;
  T	_y;
public:
  Position(T x = 0, T y = 0):
    _x(x),
    _y(y)
  {}

  ~Position(){};

  template<typename U>
  Position(const Position<U> & pos):
    _x(static_cast<T>(pos.getX())),
    _y(static_cast<T>(pos.getY()))
  {
  }

  template<typename U>
  Position & operator=(const Position<U> & pos)
  {
    if (this != &pos)
      {
	_x = static_cast<T>(pos.getX());
	_y = static_cast<T>(pos.getY());
      }
    return *this;
  }

  bool operator==(const Position & pos) const
  {
    return _x == pos._x && _y == pos._y;
  }

  bool operator!=(const Position & pos) const
  {
    return _x != pos._x || _y != pos._y;
  }

  void setX(T x)
  {
    _x = x;
  }

  void setY(T y)
  {
    _y = y;
  }

  T getX(void) const
  {
    return _x;
  }

  T getY(void) const
  {
    return _y;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & o, const Position<T> & pos)
{
  o << pos.getX() << "/" << pos.getY();
  return o;
}
#endif /* !__POSITION__HH__ */
