//
// SaveGame.hh for bomberman in /home/theoph_t/rendu/bomberman/SaveGame
//
// Made by Titouan Theophile
// Login   <theoph_t@epitech.net>
//
// Started on  Wed May 20 19:43:18 2015 Titouan Theophile
// Last update Sun Jun 14 13:10:20 2015 Titouan Theophile
//

#ifndef __SAVEGAME_HH__
# define __SAVEGAME_HH__

# include "Bomberman.hh"
# include "Map.hh"
# include "Powerup.hh"
# include "BomberException.hpp"
# include "Time.hh"
# include "eType.hh"
# include "SaveGameReader.hh"

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

class Bomberman;

class SaveGame
{
  static void	saveConfig(std::fstream & data, const Bomberman * game);
  static void	saveMap(std::fstream & data, const std::vector<eBlockType>& map, int x, int y);
  static void	saveBombs(std::fstream & data, const std::list<t_bomb *> &bombs);
  static void	saveExplosions(std::fstream & data, const std::list<t_explosion *>& bombs);
  static void	savePlayers(std::fstream & data, const std::vector<Player *> &players);
  static void	saveAi(std::fstream & data, const AI *ai);
  static void	savePowerUp(std::fstream & data, const std::list<t_powerup>&  powerup);

public:
  static std::vector<std::string>	getSavesGame();
  static void	saveCurrentGame(const Bomberman * game);
};

#endif /* !__SAVEGAME_HH__ */
