#include "AI.hh"

AI::AI(const Position<float> & pos, eType type, int id, eDirection dir, const std::string& skin, const PlayerInput & input, Bomberman* game):
  Player(pos, type, id, dir, skin, input), _game(game),
  _prevAvoid(NO),
  _avoidAcount(0),
  _sMap(game->getSerializedMap(_id))
{
  _action = NO;
  changeUpKey(U);
  changeLeftKey(L);
  changeRightKey(R);
  changeDownKey(D);
  changeBombKey(B);
}

AI::AI(std::fstream & data, const std::string &skin, eType type, Bomberman * game) :
  Player(data, skin, type), _game(game),
  _prevAvoid(NO),
  _avoidAcount(0),
  _sMap(game->getSerializedMap(_id))
{
  _action = NO;
  changeUpKey(U);
  changeLeftKey(L);
  changeRightKey(R);
  changeDownKey(D);
  changeBombKey(B);
}

AI::~AI()
{
}

eAction	AI::getPosNearPlayer() const
{
  Position<int> pos(-1, -1);
  float x = _pos.getX(), y =_pos.getY();

  for (int i = 0; i < _sMapSize.getY(); ++i)
    {
      for (int j = 0; j < _sMapSize.getX(); ++j)
	{
	  if (_sMap[i * _sMapSize.getX() + j] == PLAY)
	    {
	      float a = ABS(x - j);
	      float b = ABS(y - i);
	      float c = ABS(x - pos.getX());
	      float d = ABS(y - pos.getY());
	      if (a < 1.0000 && b < 1.0000)
		return B;
	      if (pos.getX() == -1 || (a <= c && b <= d))
		{
		  pos.setX(j);
		  pos.setY(i);
		}
	    }
	}
    }
  if (pos.getX() < static_cast<int>(x) && (x - 0.1) > 0.0000)
    {
      if (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - 0.1)] == FLOOR)
	return L;
      else if (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - 0.1)] == SOFTBLOCK)
	return B;
    }
  else if (pos.getX() > static_cast<int>(x) && (x + 0.1) < _sMapSize.getX() + 0.5)
    {
      if ( _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + 0.1)] == FLOOR)
	return R;
      else if (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + 0.1)] == SOFTBLOCK)
	return B;
    }
  else
    {
      if (pos.getY() < static_cast<int>(y) && (y - 0.1) > 0.0000)
	{
	  if (_sMap[static_cast<int>(y - 0.1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
	    return U;
	  else if (_sMap[static_cast<int>(y - 0.1) * _sMapSize.getX() + static_cast<int>(x)] == SOFTBLOCK)
	    return B;
	}
      else if (pos.getY() > static_cast<int>(y) && (y + 0.1) < _sMapSize.getY() + 0.5)
	{
	  if (_sMap[static_cast<int>(y + 0.1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
	    return D;
	  else if (_sMap[static_cast<int>(y - 0.1) * _sMapSize.getX() + static_cast<int>(x)] == SOFTBLOCK)
	    return B;
	}
    }
  return NO;
}

eAction	AI::avoidLeftBomb()
{
  float	x = _pos.getX(), y = _pos.getY();

  _avoidAcount = 0;
  if (y - 1 > 0.0f && _sMap[static_cast<int>(y - 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
    _prevAvoid = U;
  else if (y + 1 < _sMapSize.getY() && _sMap[static_cast<int>(y + 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
    _prevAvoid = D;
  else
    _prevAvoid = R;
  return _prevAvoid;
}

eAction	AI::avoidRightBomb()
{
  float	x = _pos.getX(), y = _pos.getY();

  _avoidAcount = 0;
  if (y - 1 > 0.0000 && _sMap[static_cast<int>(y - 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
    _prevAvoid = U;
  else if (y + 1 < _sMapSize.getY() && _sMap[static_cast<int>(y + 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
    _prevAvoid = D;
  else
    _prevAvoid = L;
  return _prevAvoid;
}

eAction	AI::avoidUpBomb()
{
  float	x = _pos.getX(), y = _pos.getY();

  _avoidAcount = 0;
  if (x - 1 > 0.0000 && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - 1)] == FLOOR)
    _prevAvoid = L;
  else if (x + 1 < _sMapSize.getY() && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + 1)] == FLOOR)
    _prevAvoid = R;
  else
    _prevAvoid = D;
  return _prevAvoid;
}

eAction	AI::avoidDownBomb()
{
  float	x = _pos.getX(), y = _pos.getY();

  _avoidAcount = 0;
  if (x - 1 > 0.0000 && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - 1)] == FLOOR)
    _prevAvoid = L;
  else if (x + 1 < _sMapSize.getY() && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + 1)] == FLOOR)
    _prevAvoid = R;
  else
    _prevAvoid = U;
  return _prevAvoid;
}

eAction	AI::detectBomb(eAction tmp)
{
  float	x = _pos.getX(), y = _pos.getY();

  if (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x)] == BOMB)
    {
      if (x - 1 > 0.0000
	  && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - 1)] == FLOOR)
	return L;
      else if (x + 1 < _sMapSize.getX()
	       && _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + 1)] == FLOOR)
	return R;
      else
	{
	  if (y - 1 > 0.0000
	      && _sMap[static_cast<int>(y - 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
	    return U;
	  else if (y + 1 < _sMapSize.getY()
		   && _sMap[static_cast<int>(y + 1) * _sMapSize.getX() + static_cast<int>(x)] == FLOOR)
	    return D;
	}
    }
  else
    {
      for (int i = 0; i < 4; ++i)
	{
	  if (x - (i + 0.1) > 0.0000
	      && (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - i)] == BOMB
		  || _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - i)] == XPLOS))
	    return avoidLeftBomb();
	  else if (x + (i + 0.1) < _sMapSize.getX()
		   && (_sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x + i)] == BOMB
		       || _sMap[static_cast<int>(y) * _sMapSize.getX() + static_cast<int>(x - i)] == XPLOS))
	    return avoidRightBomb();
	  else if (y - (i + 0.1) > 0.0000
		   && (_sMap[static_cast<int>(y - i) * _sMapSize.getX() + static_cast<int>(x)] == BOMB
		       || _sMap[static_cast<int>(y - i) * _sMapSize.getX() + static_cast<int>(x)] == XPLOS))
	    return avoidUpBomb();
	  else if (y + (i + 0.1) < _sMapSize.getY()
		   && (_sMap[static_cast<int>(y + i) * _sMapSize.getX() + static_cast<int>(x)] == BOMB
		       || _sMap[static_cast<int>(y + i) * _sMapSize.getX() + static_cast<int>(x)] == XPLOS))
	    return avoidDownBomb();
	}
    }
  return tmp;
}

void	AI::loop()
{
  eAction tmp;
  _sMapSize = _game->getMapSize();
  if (isAlive() == true && _game->checkEnd() == false && _action == NO)
    {
      if (_avoidAcount < 40 && _prevAvoid != NO)
	{
	  _action = _prevAvoid;
	  ++_avoidAcount;
	}
      else
	{
	  _sMap = _game->getSerializedMap(_id);
	  tmp = getPosNearPlayer();
	  tmp = detectBomb(tmp);
	  _action = tmp;
	}
    }
}

eAction	AI::getAction() const
{
  return _action;
}

void	AI::setAction(eAction action)
{
  _action = action;
}
