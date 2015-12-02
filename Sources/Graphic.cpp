#include <algorithm>
#include "BomberException.hpp"
#include "Object.hh"
#include "Graphic.hh"
#include "Cube.hh"
#include "Model.hh"
#include "Skybox.hh"
#include "Ground.hh"

Graphic::Graphic()
  :
    PATH_GROUND("./Includes/GDL_lib/assets/ground.fbm/Ground.tga"),
    PATH_SKY("./Includes/GDL_lib/assets/Skybox/"),
    PATH_BOMB("./Includes/GDL_lib/assets/bomb.fbx"),
    WIDTH(1440.0f),
    HEIGHT(900.0f),
    _sky(0),
    _ground(0),
    _tmp1(0),
    _tmp2(0),
    _resume(0),
    _saveGame(0),
    _exitGame(0),
    _score(0),
    _invincibility(0),
    _bomb(0),
    _life(0),
    _pause(0),
    _cursor(0),
    _nblife1(0),
    _nblife2(0),
    _bomb1(15),
    _bomb2(15)
{
  _texPath.push_back(std::pair<int, const char *>(SOFTBLOCK, "./Includes/GDL_lib/assets/wall.fbm/Wall.tga"));
  _texPath.push_back(std::pair<int, const char *>(HARDBLOCK, "./Includes/GDL_lib/assets/stone.fbm/Stone.tga"));
  _texPath.push_back(std::pair<int, const char *>(XPLOS, "./Includes/GDL_lib/assets/fire_box.fbm/XPlosion.tga"));
  _texPath.push_back(std::pair<int, const char *>(BOMBUP, "./Includes/GDL_lib/assets/Bonus/bombup.tga"));
  _texPath.push_back(std::pair<int, const char *>(FIREUP, "./Includes/GDL_lib/assets/Bonus/fireup.tga"));
  _texPath.push_back(std::pair<int, const char *>(SPEEDUP, "./Includes/GDL_lib/assets/Bonus/speedup.tga"));
  _texPath.push_back(std::pair<int, const char *>(FULLFIRE, "./Includes/GDL_lib/assets/Bonus/fullfire.tga"));
  _texPath.push_back(std::pair<int, const char *>(INVINCIBILITY, "./Includes/GDL_lib/assets/Bonus/invincibility.tga"));
  _texPath.push_back(std::pair<int, const char *>(HARD, "./Includes/GDL_lib/assets/Bonus/hard.tga"));
  _texPath.push_back(std::pair<int, const char *>(FROZEN, "./Includes/GDL_lib/assets/Bonus/frozen.tga"));
  _texPath.push_back(std::pair<int, const char *>(EJECT, "./Includes/GDL_lib/assets/Bonus/eject.tga"));
  _texPath.push_back(std::pair<int, const char *>(SMOG, "./Includes/GDL_lib/assets/Bonus/smog.tga"));
  _texPath.push_back(std::pair<int, const char *>(HEART, "./Includes/GDL_lib/assets/Bonus/heart.tga"));
  _texPath.push_back(std::pair<int, const char *>(SMOGBOMB, "./Includes/GDL_lib/assets/fire_box.fbm/smog.tga"));
  _texPath.push_back(std::pair<int, const char *>(FULLFIREBOMB, "./Includes/GDL_lib/assets/fire_box.fbm/XPlosion.tga"));
  _texPath.push_back(std::pair<int, const char *>(HARDBOMB, "./Includes/GDL_lib/assets/fire_box.fbm/hard.tga"));
  _texPath.push_back(std::pair<int, const char *>(FROZENBOMB, "./Includes/GDL_lib/assets/fire_box.fbm/frozen.tga"));
  _texPath.push_back(std::pair<int, const char *>(EJECTBOMB, "./Includes/GDL_lib/assets/fire_box.fbm/eject.tga"));
}

Graphic::~Graphic()
{
  std::size_t	i;

  for (std::vector<std::vector<Cube *> >::iterator itx = _map.begin(); itx != _map.end(); ++itx)
    for (std::vector<Cube *>::iterator ity = itx->begin(); ity != itx->end(); ++ity)
      delete *ity;
  while (!_modelsGarbage.empty())
    {
      Model *tmp = _modelsGarbage.top();
      _modelsGarbage.pop();
      delete tmp;
    }
  for (i = 0; i < _players.size(); ++i)
    delete _players[i];
  for (i = 0; i < _models.size(); ++i)
    delete _models[i];
  for (i = 0; i < _numb.size(); ++i)
    delete _numb[i];
  for (i = 0; i < _tex.size(); ++i)
    delete _tex[i];
  for (i = 0; i < _endStrings.size(); ++i)
    delete _endStrings[i];
  for (i = 0; i < _bombtype.size(); ++i)
    delete _bombtype[i];
  if (_tmp1)
    delete _tmp1;
  if (_tmp2)
    delete _tmp2;
  delete _pause;
  delete _cursor;
  delete _resume;
  delete _saveGame;
  delete _exitGame;
  delete _score;
  delete _sky;
  delete _ground;
  delete _bomb;
  delete _life;
  delete _invincibility;
  _context.stop();
}

void		Graphic::initCubeGeometry()
{
  // BACK FACE
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // FRONT FACE
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // LEFT FACE
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // RIGHT FACE
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // UP FACE
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // DOWN FACE
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
}

bool		Graphic::initTextures()
{
  for (std::vector<std::pair<int,const char *> >::const_iterator it = _texPath.begin(); it != _texPath.end(); ++it)
    {
      gdl::Texture	*texture = new gdl::Texture();
      texture->load(it->second);
      _tex[it->first] = texture;
    }
  return (true);
}

bool		Graphic::initNumbers()
{
  Char		*zero = new Char('0', 20);
  Char		*one = new Char('1', 20);
  Char		*two = new Char('2', 20);
  Char		*three = new Char('3', 20);
  Char		*four = new Char('4', 20);
  Char		*five = new Char('5', 20);
  Char		*six = new Char('6', 20);
  Char		*seven = new Char('7', 20);
  Char		*height = new Char('8', 20);
  Char		*nine = new Char('9', 20);

  _pause = new Char(0xFF, HEIGHT / 2, WIDTH / 2);
  _cursor = new Char('-', 50);
  _resume = new String("RESUME", 50, WIDTH / 2 - 100, HEIGHT / 2);
  _saveGame = new String("SAVE", 50, WIDTH / 2 - 100, HEIGHT / 2 + 80);
  _exitGame = new String("EXIT", 50, WIDTH / 2 - 100, HEIGHT / 2 + 160);
  _score = new String("SCORE", 30, WIDTH * 0.9, 10);
  if (zero->initialize() == false ||
      one->initialize() == false ||
      two->initialize() == false ||
      three->initialize() == false ||
      four->initialize() == false ||
      five->initialize() == false ||
      six->initialize() == false ||
      seven->initialize() == false ||
      height->initialize() == false ||
      nine->initialize() == false ||
      _pause->initialize() == false ||
      _cursor->initialize() == false)
    return (false);
  _score->scale(glm::vec3(30, 30, 0));
  _resume->scale(glm::vec3(50, 50, 0));
  _saveGame->scale(glm::vec3(50, 50, 0));
  _exitGame->scale(glm::vec3(50, 50, 0));
  _pause->MoveAtPos(glm::vec3(WIDTH / 2, HEIGHT / 2, 0));
  _cursor->MoveAtPos(glm::vec3(WIDTH / 2 - 200, HEIGHT / 2, 1));
  _numb.push_back(zero);
  _numb.push_back(one);
  _numb.push_back(two);
  _numb.push_back(three);
  _numb.push_back(four);
  _numb.push_back(five);
  _numb.push_back(six);
  _numb.push_back(seven);
  _numb.push_back(height);
  _numb.push_back(nine);
  return (true);
}

void		Graphic::initBombTypes()
{
  String	*bomb = new String("NORMAL", 30, 45, 10);
  String	*smog = new String("SMOG", 30, 45, 10);
  String	*fullfire = new String("FULLFIRE", 30, 45, 10);
  String	*hard = new String("HARD", 30, 45, 10);
  String	*frozen = new String("FROZEN", 30, 45, 10);
  String	*eject = new String("EJECT", 30, 45, 10);

  bomb->scale(glm::vec3(30, 30, 0));
  smog->scale(glm::vec3(30, 30, 0));
  fullfire->scale(glm::vec3(30, 30, 0));
  hard->scale(glm::vec3(30, 30, 0));
  frozen->scale(glm::vec3(30, 30, 0));
  eject->scale(glm::vec3(30, 30, 0));
  _bombtype.push_back(bomb);
  _bombtype.push_back(smog);
  _bombtype.push_back(fullfire);
  _bombtype.push_back(hard);
  _bombtype.push_back(frozen);
  _bombtype.push_back(eject);
}

bool		Graphic::initGraphic(const std::vector<eBlockType> &map,
				     int x, int y,
				     bool multiplayer)
{
  _map_x = x;
  _map_y = y;
  if (!_context.start(WIDTH, HEIGHT, "Bomberman"))
    throw BomberException("Cannot load window\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_POINT_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (initTextures() == false ||
      initNumbers() == false ||
      loadMap(map) == false)
    return (false);
  initBombTypes();
  if (!(_shader.load("./Includes/GDL_lib/shaders/basic.fp", GL_FRAGMENT_SHADER)) ||
      !(_shader.load("./Includes/GDL_lib/shaders/basic.vp", GL_VERTEX_SHADER)) ||
      !(_shader.build()))
    throw BomberException("Shaders haven't been loaded\n");
  if (multiplayer == true)
    _projection = glm::perspective(45.0f, (WIDTH / 2) / HEIGHT, 1.0f, 10000.0f);
  else
    _projection = glm::perspective(45.0f, (WIDTH / 2) / (HEIGHT / 2), 1.0f, 10000.0f);
  _shader.bind();
  _shader.setUniform("projection", _projection);
  return (true);
}

bool		Graphic::initPlayers(std::vector<Player *> &players, bool multi)
{
  Model		*marvin;
  Player	*player;
  Position<int>	tmpos;

  for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
    {
      player = *it;
      player->setCamera(_map_x, _map_y);
      marvin = new Model(player->getSkin());
      if (player->getId() == 0)
	{
	  marvin->initialize(PLAYERMODEL);
	  _view = player->getCamera();
	  _shader.setUniform("view", _view);
	}
      else if (player->getId() == 1 && multi)
	{
	  marvin->initialize(PLAYERMODEL);
	  _viewsec = player->getCamera();
	  _shader.setUniform("view", _viewsec);
	}
      marvin->setId(player->getId());
      marvin->setPos(player->getPosition());
      marvin->translate(glm::vec3(player->getPosX(), -player->getPosY() + _map_y, 0));
      _players.push_back(marvin);
    }
  return (true);
}

bool		Graphic::initMapElements()
{
  int		i = 4;

  _sky = new Skybox(PATH_SKY);
  _ground = new Ground(PATH_GROUND, _map_y, _map_x);
  _invincibility = new Char("./Includes/GDL_lib/assets/Bonus/invincibility.tga", 25, 25);
  _bomb = new Char("./Includes/GDL_lib/assets/Bonus/bombup.tga", 25, 25);
  _life = new Char("./Includes/GDL_lib/assets/Bonus/heart.tga", 25, 25);
  _sky->scale(glm::vec3(_map_x < _map_y ? _map_y * i : _map_x * i, _map_x < _map_y ? _map_y * i: _map_x * i, _map_x < _map_y ? _map_y * i: _map_x * i));
  _sky->translate(glm::vec3((_map_x / 2), -(-_map_y / 2), 0));
  _bomb->translate(glm::vec3(12, 12, 0));
  _life->translate(glm::vec3(302, 12, 0));
  _invincibility->translate(glm::vec3(352, 12, 0));
  if (_sky->initialize() == false ||
      _ground->initialize() == false ||
      _invincibility->initialize() == false ||
      _bomb->initialize() == false ||
      _life->initialize() == false)
    return (false);
  return (true);
}

void		Graphic::drawBorder(const int i)
{
  std::vector<Cube *>	tmp;
  Position<int>		tmpos;

  for (int index = -1; index < (_map_x + 1); ++index)
    {
      Cube *tmpCube = new Cube();

      tmpCube->translate(glm::vec3(index + 0.5, -(i - _map_y) + 1 - 0.5, 0));
      tmpos = tmpCube->getPos();
      tmpos.setX(index);
      tmpos.setY(i);
      tmpCube->setPos(tmpos);
      tmpCube->setType(HARDBLOCK);
      tmp.push_back(tmpCube);
    }
  _map.push_back(tmp);
}

bool		Graphic::loadMap(const std::vector<eBlockType>& map)
{
  std::vector<eBlockType>::const_iterator itMap = map.begin();
  Cube		*hard;
  Cube		*soft;
  int		i;
  int		j;
  Position<int>	tmpos;

  if (initMapElements() == false)
    return (false);
  initCubeGeometry();
  drawBorder(0);
  for (i = 0; i != _map_y; ++i)
    {
      std::vector<Cube *> tmp;

      hard = new Cube();
      hard->translate(glm::vec3(-1 + 0.5, -(i - _map_y) - 0.5, 0));
      tmpos = hard->getPos();
      tmpos.setX(j);
      tmpos.setX(i);
      hard->setPos(tmpos);
      hard->setType(HARDBLOCK);
      tmp.push_back(hard);

      for (j = 0; j != _map_x; ++j)
	{
	  soft = new Cube();

	  soft->setType(FLOOR);
	  tmpos = soft->getPos();
	  tmpos.setX(j);
	  tmpos.setX(i);
	  soft->setPos(tmpos);
	  soft->translate(glm::vec3(j + 0.5, -(i - _map_y) - 0.5, 0));
	  if (map[(i * _map_x) + j] == SOFTBLOCK)
	    soft->setType(SOFTBLOCK);
	  else if (map[(i * _map_x) + j] == HARDBLOCK)
	    soft->setType(HARDBLOCK);
	  tmp.push_back(soft);
	}
      hard = new Cube();
      hard->translate(glm::vec3(_map_x + 0.5, -(i - _map_y) - 0.5, 0));
      tmpos = hard->getPos();
      tmpos.setX(j);
      tmpos.setX(i);
      hard->setPos(tmpos);
      hard->setType(HARDBLOCK);
      tmp.push_back(hard);
      _map.push_back(tmp);
    }
  drawBorder(_map_y + 1);
  return (true);
}

Model		*Graphic::getNewBomb(void)
{
  if (_modelsGarbage.empty())
    return new Model(PATH_BOMB);
  else
    {
      Model *tmp = _modelsGarbage.top();
      tmp->translate(glm::vec3(- (tmp->getPos().getX() + 0.5), (tmp->getPos().getY() + 1 - _map_y), 0));
      _modelsGarbage.pop();
      return tmp;
    }
}

bool		Graphic::drawBomb(const Position<int> &pos)
{
  Model		*bomb;

  bomb = this->getNewBomb();
  bomb->translate(glm::vec3(pos.getX() + 0.5, -pos.getY() - 1 + _map_y, 0));
  bomb->setPos(pos);
  _models.push_back(bomb);
  return (true);
}

void		Graphic::removeBomb(const Position<int> &pos, eBombType type)
{
  for (std::vector<Model *>::iterator it = _models.begin(); it != _models.end(); ++it)
    {
      if ((*it)->getPos() == pos)
      	{
	  this->drawExplosion(pos, type);
	  _modelsGarbage.push(*it);
  	  _models.erase(it);
	  break;
  	}
    }
}

void		Graphic::drawExplosion(const Position<int> &pos, eBombType bombType)
{
  if (bombType == NORMAL)
    _map[pos.getY() + 1][pos.getX() + 1]->setType(XPLOS);
  else if (bombType == SMOGBOMB)
    {
      _map[pos.getY() + 1][pos.getX() + 1]->setType(SMOGBOMB);
      _map[pos.getY() + 1][pos.getX() + 1]->putScale(glm::vec3(1, 1, 2));
    }
  else
    _map[pos.getY() + 1][pos.getX() + 1]->setType(bombType);
}

void		Graphic::removeExplosion(const Position<int> &pos)
{
  if (_map[pos.getY() + 1][pos.getX() + 1]->getType() == SMOGBOMB)
    _map[pos.getY() + 1][pos.getX() + 1]->putScale(glm::vec3(1, 1, 1));
  _map[pos.getY() + 1][pos.getX() + 1]->setType(FLOOR);
}

void		Graphic::removeBlock(const Position<int> &pos)
{
  _map[pos.getY() + 1][pos.getX() + 1]->setType(FLOOR);
}

void		Graphic::drawPowerUp(const Position<int> &pos, ePowerUpType &type)
{
  _map[pos.getY() + 1][pos.getX() + 1]->putScale(glm::vec3(glm::vec3(0.6, 0.6, 0.6)));
  _map[pos.getY() + 1][pos.getX() + 1]->setType(type);
}

void		Graphic::removePowerUp(const Position<int> &pos, int toReplace)
{
  glm::vec3	tmp;

  tmp = _map[pos.getY() + 1][pos.getX() + 1]->getRotation();
  tmp.z = 0;
  _map[pos.getY() + 1][pos.getX() + 1]->setRotation(tmp);
  _map[pos.getY() + 1][pos.getX() + 1]->putScale(glm::vec3(1, 1, 1));
  _map[pos.getY() + 1][pos.getX() + 1]->setType(toReplace);
}

void		Graphic::updateCamera(Player *player)
{
  if (player->getId() == 0 || player->getId() == 1)
    player->updateCamera();
  if (player->getId() == 0)
    {
      _view = player->getCamera();
      _shader.setUniform("view", _view);
    }
  else if (player->getId() == 1)
    {
      _viewsec = player->getCamera();
      _shader.setUniform("view", _viewsec);
    }
}

void		Graphic::move(Player *player,
			      float x, float y,
			      eOrientation orientation,
			      bool moving)
{
  Model		*tmp;
  glm::vec3	tmpvec;

  for (std::vector<Model *>::iterator it = _players.begin(); it != _players.end(); ++it)
    if ((*it)->getId() == player->getId())
      {
	tmp = *it;
	break;
      }
  tmpvec = tmp->getRotation();
  tmpvec.y = orientation;
  tmp->setRotation(tmpvec);
  tmpvec = tmp->getPosition();
  tmpvec.x = x;
  tmpvec.y = _map_y - y;
  tmp->setPosition(tmpvec);
  Position<int> pos;
  tmp->setPos(pos);
  if (moving)
    tmp->startAnim();
  else
    tmp->stopAnim();
  if (player->getType() == PLAYER)
    updateCamera(player);
}

bool			Graphic::update(gdl::Input &input, gdl::Clock &clock)
{
  _context.updateClock(clock);
  _context.updateInputs(input);
  return (true);
}

inline int		Graphic::Max(int a, int b) const
{
  return (std::max(a, b) < 0 ? 0 : std::max(a, b));
}

inline int		Graphic::Min(int a, int b) const
{
  return (std::min(a, b) < 0 ? 0 : std::min(a, b));
}

void			Graphic::drawPlayer(int nb)
{
  int			i;
  glm::vec3		tmp;

  i = Max(0, _players[nb]->getPos().getY() - 13);
  while (i < Min(_players[nb]->getPos().getY() + 13, _map_y + 2))
    {
      std::vector<Cube *>::const_iterator it = _map[i].begin() + Max(0, _players[nb]->getPos().getX() - 13);

      while (it != _map[i].begin() + Min(_players[nb]->getPos().getX() + 13, _map_x + 2))
  	{
	  if (_tex[(*it)->getType()])
	    {
	      _tex[(*it)->getType()]->bind();
	      tmp = (*it)->getRotation();
	      tmp.z += 0.7;
	      if ((*it)->getType() >= 5 && (*it)->getType() <= 14)
		(*it)->setRotation(tmp);
	      _geometry.draw(_shader, (*it)->getTransformation(), GL_QUADS);
	    }
  	  ++it;
  	}
      ++i;
    }
}

void			Graphic::drawMin(const gdl::Clock &clock, const std::string & tmp)
{
  if (tmp.size() == 1)
    {
      _numb[0]->MoveAtPos(glm::vec3((WIDTH / 2) - 50, 10, 0));
      _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) - 30, 10, 0));
      _numb[0]->draw(_shader, clock);
      _numb[tmp[0] - 48]->draw(_shader, clock);
    }
  else
    {
      _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) - 50, 10, 0));
      _numb[tmp[1] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) - 30, 10, 0));
      _numb[tmp[0] - 48]->draw(_shader, clock);
      _numb[tmp[1] - 48]->draw(_shader, clock);
    }
}

void			Graphic::drawSec(const gdl::Clock &clock, const std::string & tmp)
{
  if (tmp.size() == 1)
    {
      _numb[0]->MoveAtPos(glm::vec3((WIDTH / 2) + 5, 5, 0));
      _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) + 25, 10, 0));
      _numb[0]->draw(_shader, clock);
      _numb[tmp[0] - 48]->draw(_shader, clock);
    }
  else
    {
      if (tmp[0] == tmp[1])
  	{
  	  _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) + 25, 10, 0));
  	  _numb[tmp[0] - 48]->draw(_shader, clock);
  	  _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) + 5, 10, 0));
  	  _numb[tmp[0] - 48]->draw(_shader, clock);
  	}
      else
  	{
  	  _numb[tmp[0] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) + 5, 10, 0));
  	  _numb[tmp[1] - 48]->MoveAtPos(glm::vec3((WIDTH / 2) + 25, 10, 0));
  	  _numb[tmp[0] - 48]->draw(_shader, clock);
  	  _numb[tmp[1] - 48]->draw(_shader, clock);
    	}
    }
}

void			Graphic::drawScore(const gdl::Clock &clock, Player *player)
{
  std::stringstream	ss;
  std::string		tmp;
  std::size_t		move;

  move = WIDTH * 0.98;
  ss << player->getScore();
  tmp = ss.str();
  for (int i = tmp.size(); i != 0; --i)
    {
      _numb[tmp[i - 1] - 48]->MoveAtPos(glm::vec3(move, 40, 0));
      _numb[tmp[i - 1] - 48]->draw(_shader, clock);
      move -= 15;
    }
}

void			Graphic::drawGameState(const gdl::Clock &clock, const glm::mat4 &mat, Player *player, int t)
{
  std::stringstream	min;
  std::stringstream	sec;

  min << t / 60;
  sec << t % 60;
  _shader.setUniform("view", glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
  _proj = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
  _shader.setUniform("projection", _proj);
  drawMin(clock, min.str());
  drawSec(clock, sec.str());
  drawScore(clock, player);
  _bomb->draw(_shader, clock);
  _score->draw(_shader, clock);
  _life->draw(_shader, clock);
  _numb[player->getLife()]->MoveAtPos(glm::vec3(327, 12, 0));
  _numb[player->getLife()]->draw(_shader, clock);
  if (player->getInvincibility())
    _invincibility->draw(_shader, clock);
  player->getId() == 0 ? _bombtype[_bomb1 - 15]->draw(_shader, clock) : _bombtype[_bomb2 - 15]->draw(_shader, clock);
  _shader.setUniform("view", mat);
  _shader.setUniform("projection", _projection);
}

inline bool		Graphic::isModelOnScreen(const Player *first, const Player *player)
{
  return (((player->getPosY() >= Max(0, first->getPosY() - 13)) && (player->getPosY() <= Min(first->getPosY() + 13, _map_y + 2))) &&
	  ((player->getPosX() >= Max(0, first->getPosX() - 13)) && (player->getPosX() <= Min(first->getPosX() + 13, _map_x + 2))));
}

inline bool		Graphic::isModelOnScreen(const Player *first, const Model *bomb)
{
  return (((bomb->getPos().getY() >= Max(0, first->getPosY() - 13)) && (bomb->getPos().getY() <= Min(first->getPosY() + 13, _map_y + 2))) &&
	  ((bomb->getPos().getX() >= Max(0, first->getPosX() - 13)) && (bomb->getPos().getX() <= Min(first->getPosX() + 13, _map_x + 2))));
}

void		Graphic::drawIa(const gdl::Clock &clock,
				const std::vector<Player *> players,
				int user)
{
  std::size_t	i;

  for (i = 0; i < _players.size(); ++i)
    if (players[i]->isAlive() && isModelOnScreen(players[user], players[i]))
      {
	if (_players[i]->getInitModel() == false)
	  _players[i]->initialize(PLAYERMODEL);
	_players[i]->draw(_shader, clock);
      }
  if (!_models.empty())
    for (i = 0; i < _models.size(); ++i)
      if (isModelOnScreen(players[user], _models[i]))
	{
	  if (_models[i]->getInitModel() == false)
	    _models[i]->initialize(BOMBMODEL);
	  _models[i]->draw(_shader, clock);
	}
}

void		Graphic::draw(const gdl::Clock &clock,
				      const std::vector<Player *> players,
				      int time)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _sky->draw(_shader, clock);
  _ground->draw(_shader, clock);
  drawPlayer(0);
  drawIa(clock, players, 0);
  drawGameState(clock, _view, players[0], time);
  _context.flush();
}

void		Graphic::drawEnvironment(const gdl::Clock &clock, const glm::mat4 &view)
{
  _shader.bind();
  _shader.setUniform("view", view);
  _sky->draw(_shader, clock);
  _ground->draw(_shader, clock);
}

void		Graphic::drawMulti(const gdl::Clock &clock,
				   const std::vector<Player *> players,
				   int time)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, WIDTH / 2, HEIGHT);
  drawEnvironment(clock, _view);
  drawPlayer(0);
  drawIa(clock, players, 0);
  drawGameState(clock, _view, players[0], time);

  glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT);
  drawEnvironment(clock, _viewsec);
  drawPlayer(1);
  drawIa(clock, players, 1);
  drawGameState(clock, _viewsec, players[1], time);

  _context.flush();
}

void		Graphic::updatePauseCursor(int cursor)
{
  switch (cursor)
    {
    case 0:
      _cursor->MoveAtPos(glm::vec3(WIDTH / 2 - 200, HEIGHT / 2, 1));
      break;
    case 1:
      _cursor->MoveAtPos(glm::vec3(WIDTH / 2 - 200, HEIGHT / 2 + 80, 1));
      break;
    case 2:
      _cursor->MoveAtPos(glm::vec3(WIDTH / 2 - 200, HEIGHT / 2 + 160, 1));
      break;
    }
}

void		Graphic::pause(const gdl::Clock &clock)
{
  glViewport(0, 0, WIDTH, HEIGHT);
 _shader.setUniform("view", glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
  _proj = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
  _shader.setUniform("projection", _proj);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _pause->draw(_shader, clock);
  _resume->draw(_shader, clock);
  _saveGame->draw(_shader, clock);
  _exitGame->draw(_shader, clock);
  _cursor->draw(_shader, clock);
  _shader.setUniform("view", _view);
  _shader.setUniform("projection", _projection);
  _context.flush();
}

void		Graphic::initEnd(bool multi)
{
  String	*P1 = new String("PLAYER 1");
  String	*P2 = new String("PLAYER 2");
  String	*nameEntry = new String("ENTER YOUR NAME");
  String	*name = new String("NAME");

  _projectionEnd = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
  _transformationEnd = glm::lookAt(glm::vec3(0, -30, -30), glm::vec3(0, -30, 0), glm::vec3(0, 1, 0));
  glViewport(0, 0, WIDTH, HEIGHT);
  _shader.bind();
  _shader.setUniform("view", _transformationEnd);
  _shader.setUniform("projection", _projectionEnd);
  if (multi == true)
    {
      P1->translate(glm::vec3(10, -23, 0));
      P2->translate(glm::vec3(-6, -23, 0));
    }
  else
    P1->translate(glm::vec3(3, -23, 0));
  nameEntry->translate(glm::vec3(6, -34, 0));
  name->translate(glm::vec3(6, -36, 0));
  _endStrings.push_back(P1);
  _endStrings.push_back(P2);
  _endStrings.push_back(nameEntry);
  _endStrings.push_back(name);
}

void		Graphic::selectWinners(unsigned int win,
			       std::string &path1,
			       std::string &path2,
			       const std::string &skin1,
			       const std::string &skin2) const
{
  const std::string tmp = "./Includes/GDL_lib/assets/Players/End/";

  if (win == 0)
    {
      path1 = tmp + "victory_" + skin1;
      path2 = tmp + "loose_" + skin2;
    }
  else if (win == 1)
    {
      path1 = tmp + "loose_" + skin1;
      path2 = tmp + "victory_" + skin2;
    }
  else
    {
      path1 = tmp + "loose_" + skin1;
      path2 = tmp + "loose_" + skin2;
    }
}

bool		Graphic::loadPerso(unsigned int win, bool multi, const Model *p1, const Model *p2)
{
  std::string	path1;
  std::string	path2;
  glm::vec3	tmp;

  selectWinners(win, path1, path2, p1->getPath(), p2->getPath());
  _tmp1 = new Model(path1);
  tmp = _tmp1->getRotation();
  tmp.y = 180;
  _tmp1->setRotation(tmp);
  _tmp1->scale(glm::vec3(4, 4, 4));
  !multi ? _tmp1->translate(glm::vec3(-0.5, -32, 0)) : _tmp1->translate(glm::vec3(6, -32, 0));
  _tmp1->initialize(OTHER);
  if (multi == true)
    {
      _tmp2 = new Model(path2);
      tmp = _tmp2->getRotation();
      tmp.y = 180;
      _tmp2->setRotation(tmp);
      _tmp2->scale(glm::vec3(4, 4, 4));
      _tmp2->translate(glm::vec3(-9, -32, 0));
      _tmp2->initialize(OTHER);
    }
  return (true);
}

bool		Graphic::endScreen(const gdl::Clock &clock, const std::string &entry)
{
  String	*tmp;

  for (std::vector<String*>::iterator it = _endStrings.begin(); it != _endStrings.end(); ++it)
    (*it)->draw(_shader, clock);
  if (entry.size() > 0)
    {
      tmp = new String(entry);
      tmp->translate(glm::vec3(6, -36, 0));
      delete _endStrings[3];
      _endStrings[3] = tmp;
    }
  else if (_endStrings[3]->getText() != "NAME")
    {
      tmp = new String("NAME");
      tmp->translate(glm::vec3(6, -36, 0));
      delete _endStrings[3];
      _endStrings[3] = tmp;
    }
  return true;
}

bool		Graphic::end(const std::vector<Player *> &players, bool multi)
{
  int		winner;
  glm::vec3	tmp;

  if (players[0]->isAlive())
    winner = 0;
  else if (players[0]->isAlive())
    winner = 1;
  else
    winner = 2;
  initEnd(multi);
  _sky->putScale(glm::vec3(90, 90, 90));
  tmp = _sky->getRotation();
  tmp.y = 180;
  _sky->setRotation(tmp);
  return (loadPerso(winner, multi, _players[0], _players[1]));
}

bool		Graphic::drawEnd(const gdl::Clock &clock, const std::string &name, bool multi)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  endScreen(clock, name);
  _tmp1->draw(_shader, clock);
  if (multi)
    _tmp2->draw(_shader, clock);
  _sky->draw(_shader, clock);
  _context.flush();
  return (true);
}

void		Graphic::changeBomb(Player *player, bool multi)
{
  if (player->getId() == 0)
    _bomb1 = player->getSelectedBomb();
  else if (player->getId() == 1 && multi)
    _bomb2 = player->getSelectedBomb();
}
