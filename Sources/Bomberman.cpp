#include <cmath>
#include "GenerateMap.hh"
#include "Random.hh"
#include "Bomberman.hh"

Bomberman::Bomberman(const Configuration & config):
  _status(END),
  _config(config),
  _powerup(100, 0.5),
  _graphic(),
  _explosions(),
  _remainingTime(config.getTimeLimit() * 60),
  _frame(0),
  _pauseCursor(0)
{
  _actionFunc.push_back(&Bomberman::move);
  _actionFunc.push_back(&Bomberman::move);
  _actionFunc.push_back(&Bomberman::move);
  _actionFunc.push_back(&Bomberman::move);
  _actionFunc.push_back(&Bomberman::addBomb);
  _actionFunc.push_back(&Bomberman::changeBomb);

  _gameFuncs.push_back(&Bomberman::updatePlaying);
  _gameFuncs.push_back(&Bomberman::updatePause);
  _gameFuncs.push_back(&Bomberman::updateHighscore);
}

Bomberman::~Bomberman()
{
  for (std::size_t i = 0; i != _players.size(); ++i)
    delete _players[i];
}

void	Bomberman::initKeyCode()
{
  for (unsigned int i = SDLK_a; i <= SDLK_z; ++i)
    _keyCode.push_back(std::pair<int, char>(i, i - 32));
}

void	Bomberman::cleanMapAroundPlayer()
{
  for (std::vector<Player *>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    for (int x = (*it)->getPosition().getX() - 2; x < (*it)->getPosition().getX() + 2; ++x)
      for (int y = (*it)->getPosition().getY() - 2; y < (*it)->getPosition().getY() + 2; ++y)
	_map.emptyCase(x, y);
}

bool    Bomberman::loadPreviousGame(std::fstream & data)
{
  std::vector<std::string>	iaSkins;
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/black.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/blue.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/gold.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/pink.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/red.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/white.fbx");

  _remainingTime = Utils::getNumData<float>(data);
  // MAP
  _map.loadPreviousMap(data);
  _smap = _map.getCase();
  _graphic.initGraphic(_map.getCase(), _map.getSize().getX(), _map.getSize().getY(), _config.getMultiPlayer());
  // PLAYERS & AI
  loadPlayers(data);
  // BOMBS
  loadBombs(data);
  // EXPLOSION
  loadExplosions(data);

  // POWERUP
  loadPowerUp(data);
  // GRAPHIC
  _graphic.initPlayers(_players, _config.getMultiPlayer());

  // AUDIO
  if (!_battleTheme.openFromFile("Includes/Sounds/BattleTheme.wav") ||
      !_explosionSoundbuf.loadFromFile("Includes/Sounds/Explosion.wav") ||
      !_deathSoundbuf.loadFromFile("Includes/Sounds/Death.wav"))
    return false;
  _explosionSound.setBuffer(_explosionSoundbuf);
  _deathSound.setBuffer(_deathSoundbuf);

  // _battleTheme.play();
  _battleTheme.setLoop(true);

  // END
  this->initKeyCode();
  _status = PLAYING;
  return true;
}


bool	Bomberman::initialize()
{
  std::vector<std::string>	iaSkins;
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/black.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/blue.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/gold.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/pink.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/red.fbx");
  iaSkins.push_back("./Includes/GDL_lib/assets/Players/white.fbx");

  // MAP
  if (_config.getMap() == "RANDOM")
    {
      GenerateMap::gen((Random::getRand(290)) + 10, (Random::getRand(290)) + 10);
      _map.load("./Maps/random.map");
    }
  else
    _map.load(_config.getMap().c_str());

  _smap = _map.getCase();

  // PLAYERS
  std::vector<Position<int> > empty = _map.getEmptyCase();

  int initNbIA = 0;
  if (_config.getNbIA() == 0 && _config.getMultiPlayer() == false)
    initNbIA = 1;

  Position <float> pos = this->getNewPlayerPos(_players.size(), empty);
  if (pos.getX() == -1 || pos.getY() == -1)
    return false;
  _players.push_back(new Player(pos, PLAYER, _players.size(), BOTTOM, _config.getSkinP1(), _config.getP1Inputs()));

  if (_config.getMultiPlayer())
    {
      pos = this->getNewPlayerPos(_players.size(), empty);
      if (pos.getX() == -1 || pos.getY() == -1)
	return false;
      _players.push_back(new Player(pos, PLAYER, _players.size(), UP, _config.getSkinP2(), _config.getP2Inputs()));
    }

  // IA
  for (unsigned int i = 0; i < (_config.getNbIA() + initNbIA); ++i)
    {
      pos = this->getNewPlayerPos(_players.size(), empty);
      if (pos.getX() == -1 || pos.getY() == -1)
	return false;
      _players.push_back(new AI(pos, IA, _players.size(), UP, iaSkins[i % 6], _config.getP1Inputs(), this));
    }
  this->cleanMapAroundPlayer();
  // GRAPHIC
  _graphic.initGraphic(_map.getCase(), _map.getSize().getX(), _map.getSize().getY(), _config.getMultiPlayer());
  _graphic.initPlayers(_players, _config.getMultiPlayer());

  // AUDIO
  if (!_battleTheme.openFromFile("Includes/Sounds/BattleTheme.wav") ||
      !_explosionSoundbuf.loadFromFile("Includes/Sounds/Explosion.wav") ||
      !_deathSoundbuf.loadFromFile("Includes/Sounds/Death.wav"))
    return false;
  _explosionSound.setBuffer(_explosionSoundbuf);
  _deathSound.setBuffer(_deathSoundbuf);
  // _battleTheme.play();
  _battleTheme.setLoop(true);
  // END
  this->initKeyCode();
  _status = PLAYING;
  return true;
}

Position<float>	Bomberman::getNewPlayerPos(int id, const std::vector<Position<int> > & empty)
{
  Position<float>	pos(-1,-1);
  if (empty.size() == 0)
    return pos;
  unsigned int	players = _config.getMultiPlayer() ? 2 : 1;
  players += _config.getNbIA();
  if (_config.getNbIA() == 0 && _config.getMultiPlayer() == false)
    players = 2;
  if (players == 1)
    return empty[0];
  unsigned int space = (empty.size() - 1) / (players - 1);
  space = space >= 3 ? space : 3;
  if (static_cast<unsigned int>(id * space) >= empty.size())
    return pos;
  pos.setX(empty[id * space].getX() + 0.5f);
  pos.setY(empty[id * space].getY() + 0.5f);
  return pos;
}

bool	Bomberman::checkEnd() const
{
  return _status == END;
}

void	Bomberman::setKeyEntryName()
{
  for (std::vector<std::pair<int, char> >::iterator it = _keyCode.begin();
       it != _keyCode.end(); ++it)
    {
      if (_input.getKey((*it).first, true)) {
  	_nameEntry.push_back((*it).second);
      	return;
      }
    }
}

bool	Bomberman::updateHighscore()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getKey(SDL_QUIT))
    {
      _status = END;
      return true;
    }
  if (_input.getKey(SDLK_BACKSPACE, true) && _nameEntry.size() > 0)
    _nameEntry.resize(_nameEntry.size() - 1);
  if (_input.getKey(SDLK_RETURN, true))
    {
      if (_nameEntry.empty())
	_nameEntry = "UNKNOW";
      _scores.addHighScore(_nameEntry, _players[0]->getScore());
      _status = END;
      return true;
    }
  if (_nameEntry.size() < 6)
    setKeyEntryName();
  return true;
}

bool	Bomberman::updatePause()
{
  if (_input.getKey(SDLK_UP, true)) {
      --_pauseCursor;
      if (_pauseCursor < 0)
	_pauseCursor = 2;
      _graphic.updatePauseCursor(_pauseCursor);
    }
  else if (_input.getKey(SDLK_DOWN, true)) {
      ++_pauseCursor;
      if (_pauseCursor > 2)
	_pauseCursor = 0;
      _graphic.updatePauseCursor(_pauseCursor);
    }
  if (_input.getKey(SDLK_RETURN, true)) {
      switch (_pauseCursor) {
      case 0:
	_status = PLAYING;
	break;
      case 1:
	SaveGame::saveCurrentGame(this);
	break;
      case 2:
	_status = END;
	break;
      default:
	break;
      }
    }
    return (true);
}

bool	Bomberman::updatePlaying()
{
  _smap = _map.getCase();
  for (std::vector<Player*>::iterator it = _players.begin(); it != _players.end(); ++it)
    if ((*it)->getType() == IA)
      (static_cast<AI*>(*it))->loop();

  for (std::vector<Player*>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->getStunned() <= 0)
	{
	  _isMoving = (*it)->isMoving();
	  (*it)->move(false);
	  for (int i = static_cast<int>(UP_KEY); i < static_cast<int>(NO_KEY); ++i)
	    {
	      if ((*it)->getType() == PLAYER)
		{
		  if ((i == SWITCHBOMB_KEY && _input.getKey((*it)->getKey(static_cast<InputKey>(i)), true)) ||
		      _input.getKey((*it)->getKey(static_cast<InputKey>(i))))
		    (this->*(_actionFunc[i]))(*it, static_cast<enum eAction>(i));
		}
	      else
	      	{
	      	  if ((static_cast<AI *>(*it))->getAction() != NO)
	      	    (this->*(_actionFunc[(static_cast<AI *>(*it))->getAction()]))(*it, static_cast<enum eAction>(i));
		  (static_cast<AI*>(*it))->setAction(NO);
	      	}
	    }
 	}
    }
  _powerup.monitor(_players, _graphic);
  for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
      (*it)->monitorPowerUp();
      (*it)->setExplosed((*it)->getExplosed() - _frame);
      (*it)->setStunned((*it)->getStunned() - _frame);
      (*it)->eject(_map, _graphic);
    }
  _bombs.monitor(_graphic, _frame, _explosions);
  _explosions.monitor(_players, _graphic, _frame, _powerup);
  _explosions.monitorBombs(_bombs, _map, _graphic);
  this->monitorEnd();
  _frame = 0;
  return true;
}

bool	Bomberman::update()
{
  if (_status == END)
    return true;

  float frame = static_cast<float>(1)/static_cast<float>(80);
  _graphic.update(_input, _clock);
  if (_status == PLAYING)
    {
      _frame += _clock.getElapsed();
      if (_frame < frame)
	return true;
    }

  if (_input.getKey(SDLK_p, true))
    {
      _status = _status == PAUSE ? PLAYING : PAUSE;
      _pauseCursor = 0;
    }

  _remainingTime -= _frame;
  if (_remainingTime < 0)
    _remainingTime = 0;

  if (_input.getKey(SDLK_ESCAPE, true) || _input.getInput(SDL_QUIT))
    _status = PAUSE;

  if (_status != END)
    return (this->*(_gameFuncs[_status]))();
  return true;
}

void	Bomberman::move(Player* player, enum eAction action)
{
  float posY = player->getPosY();
  float posX = player->getPosX();
  int   tmposY = floor(player->getPosY());
  int   tmposX = floor(player->getPosX());
  enum eOrientation orientation;

  switch (action) {
      case U :
          posY -= (_frame * player->getSpeed());
          tmposY = floor(posY - 0.2f);
          orientation = GRAPH_U;
          break;
      case D :
          posY += (_frame * player->getSpeed());
          tmposY = floor(posY + 0.2f);
          orientation = GRAPH_D;
          break;
      case L:
          posX -= (_frame * player->getSpeed());
          tmposX = floor(posX - 0.2f);
          orientation = GRAPH_L;
          break;
      case R :
          posX += (_frame * player->getSpeed());
          tmposX = floor(posX + 0.2f);
          orientation = GRAPH_R;
          break;
    default:
      return;
  }

  if (posY < 0 ||
      posX < 0 ||
      posY > _map.getSize().getY() ||
      posX > _map.getSize().getX())
    return;
  if (posY < 0.1000)
    posY = 0;
  if (posX < 0.1000)
    posX = 0;

  Position<int> tmpos(posX, posY);
  if (player->getPosition() != tmpos && _bombs.isBombed(tmpos))
    return;

  if (tmposX == floor(player->getPosX())
      || _map.getCase(tmposX, floor(player->getPosY())) == FLOOR || !(player->isAlive()))
  {
    player->moveX(posX);
    player->move(true);
  }
  if (tmposY == floor(player->getPosY())
      || _map.getCase(floor(player->getPosX()), tmposY) == FLOOR || !(player->isAlive()))
  {
    player->moveY(posY);
    player->move(true);
  }
  if (player->isMoving())
    _graphic.move(player, player->getPosX(), player->getPosY(), orientation, _isMoving);
}

void	Bomberman::addBomb(Player *player, enum eAction)
{
  if (player->isAlive() && _bombs.addBomb(player->getPosition(), player, _graphic))
    _explosionSound.play();
}

void	Bomberman::changeBomb(Player *player, enum eAction)
{
  player->changeBomb();
  _graphic.changeBomb(player, _config.getMultiPlayer());
}

void	Bomberman::draw()
{
  if (_status == END)
    return;
  if (_status == PAUSE)
    _graphic.pause(_clock);
  else if (_status == HIGHSCORE)
    _graphic.drawEnd(_clock, _nameEntry, _config.getMultiPlayer());
  else if (_config.getMultiPlayer())
    _graphic.drawMulti(_clock, _players, static_cast<int>(_remainingTime));
  else
    _graphic.draw(_clock, _players, static_cast<int>(_remainingTime));
}

Map	Bomberman::getMap() const
{
  return _map;
}

const Bombs &		Bomberman::getBombs() const
{
  return _bombs;
}

const Powerup &		Bomberman::getPowerUp() const
{
  return _powerup;
}

const Explosions &	Bomberman::getExplosions() const
{
  return _explosions;
}

const std::vector<Player *>&	Bomberman::getPlayers() const
{
  return _players;
}

float	Bomberman::getRemaningTime() const
{
  return _remainingTime;
}

const Configuration &	Bomberman::getConfig() const
{
  return _config;
}

Player *	Bomberman::getOwner(int id) const
{
  for (unsigned int i = 0; i < _players.size(); i++)
    {
      if (_players[i]->getId() == id)
	return _players[i];
    }
  return NULL;
}

void	Bomberman::monitorEnd()
{
  int	remainingPlayers = 0;
  int	remainingIA = 0;

  for (std::vector<Player*>::iterator it = _players.begin(); it != _players.end(); ++it)
    if ((*it)->isAlive() && ((*it)->getType() == PLAYER))
      ++remainingPlayers;
    else if ((*it)->isAlive())
      ++remainingIA;

  if (remainingPlayers <= 0 || (remainingIA <= 0 && remainingPlayers <= 1) || _remainingTime <= 0)
    {
      _status = HIGHSCORE;
      _graphic.end(_players, _config.getMultiPlayer());
    }
}

std::vector<eBlockType>&	Bomberman::getSerializedMap(int id)
{
  const std::list<t_bomb*> &bombs = _bombs.getBombs();
  const std::list<t_explosion*>& explosion = _explosions.getExplosions();

  for (std::vector<Player*>::iterator it = _players.begin();
       it != _players.end(); ++it)
    {
      if (!(*it))
	continue;
      if ((*it)->isAlive() == false || (*it)->getId() == id)
	{
	  _smap[static_cast<int>((*it)->getPosY()) * _map.getSize().getX() +
	    static_cast<int>((*it)->getPosX())] = FLOOR;
	  continue;
	}
      _smap[static_cast<int>((*it)->getPosY()) * _map.getSize().getX() +
	    static_cast<int>((*it)->getPosX())] = PLAY;
    }
  for (std::list<t_bomb*>::const_iterator it = bombs.begin();
       it != bombs.end(); ++it)
    {
      if (*it)
	_smap[(*it)->_pos.getY() * _map.getSize().getX() + (*it)->_pos.getX()] = BOMB;
    }
  for (std::list<t_explosion*>::const_iterator it = explosion.begin();
       it != explosion.end(); ++it)
    {
      if (*it)
   	_smap[(*it)->_pos.getY() * _map.getSize().getX() + (*it)->_pos.getX()] = XPLOS;
    }
  return _smap;
}

Position<int>	Bomberman::getMapSize()
{
  return _map.getSize();
}

void			Bomberman::loadPlayers(std::fstream & data)
{
  int			nb;
  std::string		skin;
  std::string		str;
  eType			type;

  data >> str;
  if (str != "players")
    throw BomberException("Sasvegame seems to be corrupted");
  data >> nb;
  for (; nb > 0; nb--)
    {
      type = Utils::getNumData<eType>(data);
      data >> skin;
      if (type == PLAYER)
	_players.push_back(new Player(data, skin, type));
      else
	_players.push_back(new AI(data, skin, type, this));
    }
}

void			Bomberman::loadBombs(std::fstream & data)
{
  int			nb;
  std::string		str;

  data >> str;
  if (str != "bombs")
    throw BomberException("Savegame seems to be corrupted");
  data >> nb;
  for (; nb > 0; nb--)
    _bombs.loadBomb(data,this->getOwner(Utils::getNumData<int>(data)));
}

void			Bomberman::loadExplosions(std::fstream & data)
{
  int			nb;
  std::string		str;

  data >> str;
  if (str != "explosions")
    throw BomberException("Savegame seems to be corrupted");
  data >> nb;
  for (; nb > 0; nb--)
    _explosions.loadExplosion(data, this->getOwner(Utils::getNumData<int>(data)));
}

void			Bomberman::loadPowerUp(std::fstream & data)
{
  int			nb;
  std::string		str;

  data >> str;
  if (str != "powerup")
    throw BomberException("Savegame seems to be corrupted");
  data >> nb;
  for (; nb > 0; nb--)
    _powerup.loadPowerup(data, _graphic);
}
