#ifndef BOMBERMAN_HH_
# define BOMBERMAN_HH_

# include <map>
# include <SFML/Audio.hpp>
# include <SFML/System.hpp>
# include "Explosions.hh"
# include "Bombs.hh"
# include "Player.hh"
# include "Graphic.hh"
# include "Map.hh"
# include "Powerup.hh"
# include "BomberException.hpp"
# include "AI.hh"
# include "Menu.hh"
# include "utils.hpp"
# include "Configuration.hh"
# include "SaveGame.hh"
# include "Score.hh"
# include "eGameStatus.hh"
# include "eAction.hh"



class Bomberman : public gdl::Game {

  typedef void (Bomberman::*PlFunc)(Player *, enum eAction);
  typedef bool (Bomberman::*GameFunc)();

private:
  eGameStatus				_status;
  const Configuration &		_config;
  Powerup				    _powerup;
  Graphic				    _graphic;
  Explosions				_explosions;
  Map					    _map;
  gdl::Clock				_clock;
  gdl::Input				_input;
  std::vector<Player*>		_players;
  Bombs					    _bombs;
  float					    _remainingTime;
  std::vector<PlFunc>		_actionFunc;
  float					    _frame;
  bool					    _isMoving;
  int					    _pauseCursor;
  sf::Music				    _battleTheme;
  sf::SoundBuffer			_explosionSoundbuf;
  sf::SoundBuffer			_deathSoundbuf;
  sf::Sound				    _deathSound;
  sf::Sound				    _explosionSound;
  Score					    _scores;
  std::vector<GameFunc>		_gameFuncs;
  std::string				_nameEntry;
  Time					    _time;
  std::vector<eBlockType>	_smap;
  std::vector<std::pair<int, char> >	_keyCode;

  void				move(Player*, enum eAction);
  void				addBomb(Player*, enum eAction);
  void				changeBomb(Player*, enum eAction);

  void				initKeyCode();
  void				setKeyEntryName();

  void				monitorEnd();

  bool				updateHighscore();
  bool				updatePause();
  bool				updatePlaying();

  Position<float>	getNewPlayerPos(int id, const std::vector<Position<int> > & empty);
  void				cleanMapAroundPlayer();

public:
  Bomberman(const Configuration & config);
  ~Bomberman();
  void				launchIA();
  bool				initialize();
  bool				checkEnd() const;
  bool				update();
  void				draw();

  std::vector<eBlockType>&	    getSerializedMap(int id);
  Position<int>			        getMapSize();

  Map				            getMap() const;
  const std::vector<Player *>&	getPlayers() const;
  Player *			            getOwner(int id) const;
  const Bombs &			        getBombs() const;
  const Powerup &		        getPowerUp() const;
  const Explosions &		    getExplosions() const;
  float				            getRemaningTime() const;
  const Configuration &		    getConfig() const;

  void				            loadBombs(std::fstream & data);
  void          				loadPlayers(std::fstream & data);
  void			            	loadExplosions(std::fstream & data);
  void          				loadPowerUp(std::fstream & data);
  bool			            	loadPreviousGame(std::fstream & data);
};

#endif	/* !BOMBERMAN_HH_ */
