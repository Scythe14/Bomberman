//
// SaveGame.cpp for bomberman in /home/theoph_t/rendu/bomberman/SaveGame
//
// Made by Titouan Theophile
// Login   <theoph_t@epitech.net>
//
// Started on  Wed May 20 19:50:09 2015 Titouan Theophile
// Last update Sun Jun 14 13:10:44 2015 Titouan Theophile
//

#include "SaveGame.hh"

std::vector<std::string>	SaveGame::getSavesGame()
{
  std::vector<std::string>	saves;
  SaveGameReader		reader;


  if (reader.openDir("SaveGame") == false)
    return saves;
  saves = reader.readDir();
  return (saves);
}

void			SaveGame::saveConfig(std::fstream & data, const Bomberman * game)
{
  data << "config" << std::endl
       << game->getConfig().getMultiPlayer() << " "
       << game->getConfig().getGlobalVolume() << " "
       << game->getConfig().getSkinP1() << " "
       << game->getConfig().getSkinP2() << " "
       << game->getConfig().getNbIA() << " "
       << game->getRemaningTime() << std::endl;
}

void			SaveGame::saveMap(std::fstream & data, const std::vector<eBlockType> & map, int x, int y)
{
  data << "size "
       << x << " "
       << y << std::endl;
  for (unsigned int i = 0; i < map.size(); i++)
    {
      data << map[i];
      if (!((i + 1) % x))
	data << std::endl;
      else
	data << " ";
    }
}

void			SaveGame::savePlayers(std::fstream & data, const std::vector<Player *> & players)
{
  std::map<int, bool> bombs;

  data << "players "
       << players.size() << std::endl;
  for (unsigned int i = 0; i < players.size(); i++)
    {
      bombs = players[i]->getBombsType();
      data << players[i]->getType() << " "
	   << players[i]->getSkin() << " "
	   << players[i]->getId() << " "
	   << players[i]->getPosY() << " "
	   << players[i]->getPosX() << " "
	   << players[i]->getDir() << " "
	   << players[i]->isAlive() << " "
	   << players[i]->isMoving() << " "
	   << players[i]->getSelectedBomb() << " "
	   << players[i]->getExplosed() << " "
	   << players[i]->getStunned() << " "
	   << players[i]->getEject() << " "
	   << players[i]->getKey(UP_KEY) << " "
	   << players[i]->getKey(DOWN_KEY) << " "
	   << players[i]->getKey(LEFT_KEY) << " "
	   << players[i]->getKey(RIGHT_KEY) << " "
	   << players[i]->getKey(BOMB_KEY) << " "
	   << players[i]->getKey(SWITCHBOMB_KEY) << " "
	   << players[i]->getSpeed() << " "
	   << players[i]->getRange() << " "
	   << players[i]->getCapacity() << " "
	   << players[i]->getInvincibilityRemainTime() << " "
	   << players[i]->getScore() << " "
	   << players[i]->getLife() << " "
	   << bombs.size();
      for (std::map<int, bool>::iterator it = bombs.begin(); it != bombs.end(); ++it)
	  data << " " << (*it).second;
      data << std::endl;
    }
}

void			SaveGame::saveBombs(std::fstream & data, const std::list<t_bomb *> & bombs)
{
  data << "bombs "
        << bombs.size()
       << std::endl;
  for (std::list<t_bomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
    {
      data << (*it)->_owner->getId() << " "
  	   << (*it)->_pos.getX() << " "
  	   << (*it)->_pos.getY() << " "
  	   << (*it)->_range << " "
  	   << (*it)->_type << " "
  	   << (*it)->_spreadDirection << " "
  	   << (*it)->_countdown << " "
  	   << (*it)->_explosionsCountDown << " "
  	   << (*it)->_status << " "
  	   << (*it)->_points << " "
  	   << (*it)->_throughtHard << " "
  	   << (*it)->_throughtSoft << " "
  	   << std::endl;
    }
}

void			SaveGame::saveExplosions(std::fstream & data, const std::list<t_explosion *> & explosions)
{
  data << "explosions "
       << explosions.size()
       << std::endl;
  for (std::list<t_explosion *>::const_iterator it = explosions.begin(); it != explosions.end(); ++it)
    {
      data << (*it)->_owner->getId() << " "
	   << (*it)->_pos.getX() << " "
	   << (*it)->_pos.getX() << " "
	   << (*it)->_range << " "
	   << (*it)->_spreadDirection << " "
	   << (*it)->_type << " "
	   << (*it)->_countdown << " "
	   << (*it)->_first << " "
	   << (*it)->_points << " "
	   << (*it)->_powerup << " "
	   << (*it)->_throughtHard << " "
	   << (*it)->_throughtSoft << " "
	   << std::endl;
    }
}

void			SaveGame::savePowerUp(std::fstream & data, const std::list<t_powerup> & powerup)
{
  data << "powerup "
       << powerup.size()
       << std::endl;
  for (std::list<t_powerup>::const_iterator it = powerup.begin(); it != powerup.end(); ++it)
    {
      data << (*it).first.getX() << " "
	   << (*it).first.getY() << " "
	   << (*it).second << std::endl;
    }
}

void			SaveGame::saveCurrentGame(const Bomberman * game)
{
  std::fstream		data;
  std::string		name("SaveGame/");

  name.append(Time::getCurrentDate());
  data.open(name.c_str(), std::fstream::out | std::fstream::trunc);
  std::cout << "New save in " << name.c_str() << std::endl;
  if (!data.is_open())
    throw BomberException("Cannot save current game");
  saveConfig(data, game);
  saveMap(data, game->getMap().getCase(), game->getMap().getSize().getX(), game->getMap().getSize().getY());
  savePlayers(data, game->getPlayers());
  saveBombs(data, game->getBombs().getBombs());
  saveExplosions(data, game->getExplosions().getExplosions());
  savePowerUp(data, game->getPowerUp().getPowerUp());
  data.close();
}
