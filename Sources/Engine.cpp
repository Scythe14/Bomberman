#include "Engine.hh"

Engine::Engine()
  : sceneId(0), pSceneId(0), config(), intro(false)
{
  EngineUpdate[0] = &Engine::menuUpdate;
  EngineUpdate[1] = &Engine::gameUpdate;
  EngineCreate[0] = &Engine::menuCreate;
  EngineCreate[1] = &Engine::gameCreate;
  EngineDraw[0] = &Engine::menuDraw;
  EngineDraw[1] = &Engine::gameDraw;
  _menu = NULL;
  _game = NULL;
}

Engine::~Engine()
{
  if (_menu != NULL)
    delete _menu;
  if (_game != NULL)
    delete _game;
}

bool	Engine::initialize()
{
  if (menuCreate() == false)
    return false;
  return true;
}

bool	Engine::menuUpdate()
{
  if (_menu->update() == false)
    return false;
  if (_menu->checkNG() == true)
    sceneId = 1;
  return true;
}

bool	Engine::gameUpdate()
{
  if (_game->update() == false)
    return false;
  if (_game->checkEnd() == true)
    sceneId = 0;
  return true;
}

bool	Engine::update()
{
  pSceneId = sceneId;
  if ((this->*EngineUpdate[sceneId])() == false)
    return false;
  if (sceneId != pSceneId)
    {
      if (switchScene() == false)
	return false;
    }
  return true;
}

bool	Engine::menuDraw()
{
  _menu->draw();
  return true;
}

bool	Engine::gameDraw()
{
  _game->draw();
  return true;
}

void	Engine::draw()
{
  (this->*EngineDraw[sceneId])();
}

bool	Engine::menuCreate()
{
  if (_game)
    {
      delete _game;
      _game = NULL;
    }
  _menu = new Menu(config);
  if (_menu->initialize(intro) == false)
    return false;
  return intro = true;
}

bool	Engine::gameCreate()
{
  if (_menu)
    {
      delete _menu;
      _menu = NULL;
    }
  if (config.getSave() != "")
    return loadGame(config.getSave());
  _game = new Bomberman(config);
  if (_game->initialize() == false)
    return false;
  return true;
}

void	Engine::loadConfig(std::fstream & data)
{
  std::string	str;
  PlayerInput	input;

  data >> str;
  if (str != "config")
    throw BomberException("Savegame seems to be corrupted");
  config.setMultiPlayer(Utils::getNumData<bool>(data));
  config.setGlobalVolume(Utils::getNumData<unsigned int>(data));
  data >> str;
  config.setSkinP1(str);
  data >> str;
  config.setSkinP2(str);
  config.setNbIA(Utils::getNumData<unsigned int>(data));
}

bool	Engine::loadGame(const std::string& saveName)
{
  std::fstream          data;

  data.open(std::string(std::string("SaveGame/") + saveName).c_str(), std::fstream::in);
  if (!data.is_open())
    throw BomberException("Cannot find savegame");
  this->loadConfig(data);
 if (_menu)
    {
      delete _menu;
      _menu = NULL;
    }
 _game = new Bomberman(config);
 try
   {
     if (_game->loadPreviousGame(data) == false)
       return false;
   }
 catch (BomberException &e)
   {
     return false;
   }
 return true;
}

bool	Engine::switchScene()
{
  if ((this->*EngineCreate[sceneId])() == false)
    {
      if (sceneId == 1)
	{
	  std::cerr << "Can't initialize game" << std::endl;
	  return true;
	}
      return false;
    }
  return true;
}

Bomberman *	Engine::getGame() const
{
  return _game;
}
