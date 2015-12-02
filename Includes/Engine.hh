#ifndef ENGINE_HH_
# define ENGINE_HH_

# include "Menu.hh"
# include "Bomberman.hh"


class Engine {

typedef bool	(Engine::*efptr)();

  Menu		*_menu;
  Bomberman	*_game;
  int		sceneId;
  int		pSceneId;
  efptr		EngineUpdate[2];
  efptr		EngineCreate[2];
  efptr		EngineDraw[2];
  Configuration	config;
  bool		intro;

public:
  Engine();
  ~Engine();

  Bomberman * getGame() const;

  bool	initialize();
  bool	menuUpdate();
  bool	gameUpdate();
  bool	update();
  bool	menuDraw();
  bool	gameDraw();
  void	draw();
  bool	gameCreate();
  bool	loadGame(const std::string & SaveGame);
  void	loadConfig(std::fstream & data);
  bool	menuCreate();
  bool	switchScene();
};

#endif /* !ENGINE_HH_ */
