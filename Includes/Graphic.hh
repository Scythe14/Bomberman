#ifndef GRAPHIC_HH_
# define GRAPHIC_HH_

# include <vector>
# include <map>
# include <stack>
# include <utility>
# include <string>
# include <sstream>
# include "Map.hh"
# include "Object.hh"
# include "Player.hh"
# include "Position.hh"
# include "Cube.hh"
# include "Skybox.hh"
# include "Model.hh"
# include "Ground.hh"
# include "Char.hh"
# include "ePowerUpType.hh"
# include "String.hh"
# include "eBombType.hh"
# include "eOrientation.hh"
# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "Geometry.hh"
# include "Model.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "Model.hh"
# include "OpenGL.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

class Player;

class Graphic {

private:
  const char *					PATH_GROUND;
  const char *					PATH_SKY;
  const char *					PATH_BOMB;
  const float					WIDTH;
  const float					HEIGHT;

  gdl::SdlContext				_context;
  gdl::BasicShader				_shader;
  std::vector<std::vector<Cube *> >		_map;
  std::vector<std::pair<int,const char *> >	_texPath;
  std::map<int,gdl::Texture *>			_tex;
  std::vector<String*>				_bombtype;
  std::vector<String*>				_endStrings;
  std::vector<Char *>				_numb;
  std::vector<Model *>				_players;
  std::vector<Model *>				_models;
  std::stack<Model *>				_modelsGarbage;
  gdl::Geometry					_geometry;
  glm::mat4					_projection;
  glm::mat4					_projectionEnd;
  glm::mat4					_transformationEnd;
  glm::mat4					_proj;
  glm::mat4					_view;
  glm::mat4					_viewsec;
  std::stringstream				_entryName;
  Skybox					*_sky;
  Ground					*_ground;
  Model						*_tmp1;
  Model						*_tmp2;
  String					*_resume;
  String					*_saveGame;
  String					*_exitGame;
  String					*_score;
  Char						*_invincibility;
  Char						*_bomb;
  Char						*_life;
  Char						*_pause;
  Char						*_cursor;
  int						_nblife1;
  int						_nblife2;
  int						_bomb1;
  int						_bomb2;
  int						_map_x;
  int						_map_y;

  void				initCubeGeometry();
  bool				initMapElements();
  bool				initTextures();
  bool				loadMap(const std::vector<eBlockType> &);
  void				drawGameState(const gdl::Clock &, const glm::mat4 &, Player *,int);
  void				drawPlayer(int);
  void				drawBorder(int);
  void				drawMin(const gdl::Clock &, const std::string &);
  void				drawSec(const gdl::Clock &, const std::string &);
  void				drawScore(const gdl::Clock &, Player *);
  bool				initNumbers();
  void				updateCamera(Player *);
  Model				*getNewBomb(void);
  void				initEnd(bool);
  void				selectWinners(unsigned int, std::string &, std::string &,
					      const std::string &, const std::string &) const;
  void				initBombTypes();
  bool				isModelOnScreen(const Player *, const Player *);
  bool				isModelOnScreen(const Player *, const Model *);
  bool				initModelPlayer();
  void				drawIa(const gdl::Clock &, const std::vector<Player *>, int);
  void				drawEnvironment(const gdl::Clock &, const glm::mat4 &);
  inline int			Min(int, int) const;
  inline int			Max(int, int) const;

public:
  Graphic();
  ~Graphic();

  bool				initGraphic(const std::vector<eBlockType> &, int, int, bool);
  bool				initPlayers(std::vector<Player *> &, bool);
  bool				update(gdl::Input &, gdl::Clock &);
  void				draw(const gdl::Clock &,
				     const std::vector<Player *>, int);
  void				drawMulti(const gdl::Clock &,
					  const std::vector<Player *>, int);
  bool				drawBomb(const Position<int> &);
  void				removeBomb(const Position<int> &, eBombType);
  void				drawExplosion(const Position<int> &, eBombType);
  void				drawPowerUp(const Position<int> &, ePowerUpType &);
  void				removePowerUp(const Position<int> &, int = FLOOR);
  void				removeExplosion(const Position<int> &);
  void				removeBlock(const Position<int> &);
  void				pause(const gdl::Clock &);
  bool				loadPerso(const unsigned int, bool, const Model *, const Model *);
  void				changeBomb(Player *, bool);
  bool				end(const std::vector<Player *> &, bool);
  bool				endScreen(const gdl::Clock&, const  std::string&);
  bool				drawEnd(const gdl::Clock &, const std::string &, bool);

  void				move(Player *, float, float, eOrientation, bool);
  void				updatePauseCursor(int);

};

#endif /* !GRAPHIC_HH_ */
