#include "BomberException.hpp"
#include "Skybox.hh"
#include "Score.hh"
#include "Menu.hh"

Menu::Menu(Configuration &_config)
  : prev_id(0), id_menu(0), _ng(false), chInput(false), _endintro(false), config(_config)
{
  nb_player = 1;
  sel[0] = 0;
  pSel[0] = 0;
  sel[1] = 0;
  pSel[1] = 0;
  sel[2] = 0;
  pSel[2] = 0;
  sel[3] = 0;
  pSel[3] = 0;
  sel[4] = 0;
  pSel[4] = 0;
  sel[5] = 0;
  pSel[5] = 0;
  ssVol << config.getGlobalVolume();
  ssIA << config.getNbIA();
  ssTime << config.getTimeLimit();
  MenuUpdate[0] = &Menu::HomeUpdate;
  MenuUpdate[1] = &Menu::NGUpdate;
  MenuUpdate[2] = &Menu::LGUpdate;
  MenuUpdate[3] = &Menu::ConfigUpdate;
  MenuUpdate[4] = &Menu::RankUpdate;
  MenuUpdate[5] = &Menu::InputsUpdate;
  MenuView[0] = &Menu::HomeMenu;
  MenuView[1] = &Menu::NewGame;
  MenuView[2] = &Menu::LoadGame;
  MenuView[3] = &Menu::Config;
  MenuView[4] = &Menu::Ranking;
  MenuView[5] = &Menu::Inputs;
  // UP Key update
  HomeUpdateVec.push_back(std::pair<int, ufptr>(SDLK_UP, &Menu::HomeUpUpdate));
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_UP, &Menu::NGUpUpdate));
  LGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_UP, &Menu::LGUpUpdate));
  ConfigUpdateVec.push_back(std::pair<int, ufptr>(SDLK_UP, &Menu::ConfigUpUpdate));
  InputUpdateVec.push_back(std::pair<int, ufptr>(SDLK_UP, &Menu::InputUpUpdate));
  // DOWN Key update
  HomeUpdateVec.push_back(std::pair<int, ufptr>(SDLK_DOWN, &Menu::HomeDownUpdate));
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_DOWN, &Menu::NGDownUpdate));
  LGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_DOWN, &Menu::LGDownUpdate));
  ConfigUpdateVec.push_back(std::pair<int, ufptr>(SDLK_DOWN, &Menu::ConfigDownUpdate));
  InputUpdateVec.push_back(std::pair<int, ufptr>(SDLK_DOWN, &Menu::InputDownUpdate));
  // RETURN Key update
  HomeUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RETURN, &Menu::HomeReturnUpdate));
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RETURN, &Menu::NGReturnUpdate));
  LGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RETURN, &Menu::LGReturnUpdate));
  ConfigUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RETURN, &Menu::ConfigReturnUpdate));
  InputUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RETURN, &Menu::InputReturnUpdate));
  // LEFT Key update
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_LEFT, &Menu::NGLeftUpdate));
  LGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_LEFT, &Menu::LGLeftUpdate));
  ConfigUpdateVec.push_back(std::pair<int, ufptr>(SDLK_LEFT, &Menu::ConfigLeftUpdate));
  // RIGHT Key update
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RIGHT, &Menu::NGRightUpdate));
  LGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RIGHT, &Menu::LGRightUpdate));
  ConfigUpdateVec.push_back(std::pair<int, ufptr>(SDLK_RIGHT, &Menu::ConfigRightUpdate));
  // Q Key update
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_q, &Menu::NGQUpdate));
  // D Key update
  NGUpdateVec.push_back(std::pair<int, ufptr>(SDLK_d, &Menu::NGDUpdate));

  // REDIRECTIONS NG
  NGRedirect[0] = &Menu::NGMultiplayer;
  NGRedirect[1] = &Menu::NGSkinCursor;
  NGRedirect[2] = &Menu::NGTimeLimit;
  NGRedirect[3] = &Menu::NGNbIA;
  NGRedirect[4] = &Menu::NGMapCursor;

  mapSelec = Utils::readDir("./Maps/", ".map");
  mapSelec->push_back("GENERATE");
  savesFiles = SaveGame::getSavesGame();
  if (savesFiles.empty())
    savesFiles.push_back("NO FILE FOUND");
  mapCursor = 0;
  saveCursor = 0;
  skinSelec = Utils::readDir("./Includes/GDL_lib/assets/Players/", ".fbx");
  initKeyCode();
  highScore.loadHighScore();
}

Menu::~Menu()
{
  Object	*tmp;

  while (!strings.empty())
    {
      tmp = strings.back();
      strings.pop_back();
      delete tmp;
    }
  while (!obj.empty())
    {
      tmp = obj.back();
      obj.pop_back();
      delete tmp;
    }
  context.stop();
}

void	Menu::initKeyCode()
{
  std::string c;

  for (unsigned int i = SDLK_0; i <= SDLK_9; ++i)
    {
      c = static_cast<char>(i);
      keyCode.push_back(std::pair<int, std::string>(i, c));
    }

  keyCode.push_back(std::pair<int, std::string>(SDLK_BACKSPACE, std::string("BSPAC")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_RETURN, std::string("RET")));

  for (unsigned int i = SDLK_a; i <= SDLK_z; ++i)
    {
      c = static_cast<char>(i - 32);
      keyCode.push_back(std::pair<int, std::string>(i, c));
    }
  keyCode.push_back(std::pair<int, std::string>(SDLK_LALT, std::string("LALT")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_LCTRL, std::string("LCTRL")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_RALT, std::string("RALT")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_RCTRL, std::string("RCTRL")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_LSHIFT, std::string("LSH")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_RSHIFT, std::string("RSH")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_LEFT, std::string("LEFT")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_UP, std::string("UP")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_RIGHT, std::string("RIGHT")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_DOWN, std::string("DOWN")));
  keyCode.push_back(std::pair<int, std::string>(SDLK_SPACE, std::string("SPACE")));
}

bool	Menu::initialize(bool init)
{
  Skybox	*skybox = new Skybox("./Includes/GDL_lib/assets/Skybox/");
  if (!context.start(800, 600, "Bomberman Menu"))
    return false;
  if (!shader.load("Includes/GDL_lib/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !shader.load("Includes/GDL_lib/shaders/basic.vp", GL_VERTEX_SHADER)
      || !shader.build())
    {
      std::cerr << "Fail to load Shaders" << std::endl;
      return false;
    }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
  transformation = glm::lookAt(glm::vec3(0, -30, -30), glm::vec3(0, -30, 0), glm::vec3(0, 1, 0));
  shader.bind();
  shader.setUniform("view", transformation);
  shader.setUniform("projection", projection);
  if (skybox->initialize() == false)
    return (false);
  skybox->scale(glm::vec3(70, 70, 70));
  glm::vec3 tmpos = skybox->getPosition();
  tmpos.y -= 30;
  skybox->setPosition(tmpos);
  obj.push_back(skybox);
  if (HomeMenu() == false)
    return false;
  if (init == false)
    if (intro() == false)
      return (false);
  _endintro = true;
  // AUDIO
  if (!menuTheme.openFromFile("Includes/Sounds/menuTheme.wav"))
    return false;
  if (!soundBuf.loadFromFile("Includes/Sounds/Cursor2.wav"))
    return false;
  selecSound.setBuffer(soundBuf);
  menuTheme.play();
  menuTheme.setLoop(true);
  return true;
}

bool	Menu::intro()
{
  Model		*marvin = new Model("./Includes/GDL_lib/assets/Players/white.fbx");
  Model		*bomb = new Model("./Includes/GDL_lib/assets/bomb.fbx");
  float		t = 15.0f;

  marvin->initialize(BOMBMODEL);
  bomb->initialize(OTHER);
  bomb->MoveAtPos(glm::vec3(0, -37.5, -12));
  bomb->scale(glm::vec3(1, 1, 1));
  marvin->scale(glm::vec3(0.5, 0.5, 0.5));
  marvin->MoveAtPos(glm::vec3(t, -36, -12));
  glm::vec3 tmpRot = marvin->getRotation();
  tmpRot.y -= 90.0f;
  marvin->setRotation(tmpRot);
  while (t > -17.0f)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      if (t < -16)
      	{
      	  glClearColor(0xFF, 0xFF, 0xFF, 1);
      	  context.flush();
      	  t -= 0.02;
      	  continue;
      	}
      if (t < -1)
      	bomb->draw(shader, clock);
      marvin->draw(shader, clock);
      marvin->MoveAtPos(glm::vec3(t, -36, -12));
      update();
      context.flush();
      t -= 0.1;
    }
  glClearColor(0, 0, 0, 1);
  delete marvin;
  delete bomb;
  return (true);
}

bool	Menu::checkNG() const
{
  return _ng;
}

void	Menu::HomeUpUpdate()
{
  selecSound.play();
  --sel[0];
  if (sel[0] < 0)
    sel[0] = 4;
  strings[pSel[0]]->translate(glm::vec3(0, 0, 1));
  strings[sel[0]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::HomeDownUpdate()
{
  selecSound.play();
  ++sel[0];
  if (sel[0] > 4)
    sel[0] = 0;
  strings[pSel[0]]->translate(glm::vec3(0, 0, 1));
  strings[sel[0]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::HomeReturnUpdate()
{
  id_menu = sel[0] + 1;
}

bool	Menu::HomeUpdate()
{
  pSel[0] = sel[0];
  for (std::vector<std::pair<int, ufptr> >::iterator it = HomeUpdateVec.begin();
       it != HomeUpdateVec.end(); ++it)
    {
      if (inputs.getKey((*it).first, true))
	(this->*(*it).second)();
    }
  if (id_menu == 5)
    id_menu = 6;
  return true;
}

const std::string	&Menu::switchMap() const
{
  std::vector<std::string>::const_iterator	it = mapSelec->begin();
  int	iteration = 0;

  while (iteration != mapCursor) {
    ++it;
    ++iteration;
  }
  return *it;
}

void	Menu::printNewMap(const std::string &name)
{
  String	*newMap = new String(name);
  String	*tmp = strings.back();
  std::string	pathMap;

  strings.pop_back();
  delete tmp;
  newMap->translate(glm::vec3(1.5f, -33, -17));
  strings.push_back(newMap);
  pathMap = "Maps/";
  pathMap += name;
  pathMap += ".map";
  if (static_cast<unsigned int>(mapCursor) == mapSelec->size() - 1)
    config.setMap("RANDOM");
  else
    config.setMap(pathMap);
}

void	Menu::newSkinP1(const std::string &name)
{
  Object	*newArt = new Art(name);

  if (newArt->initialize() == false)
    throw BomberException("Cannot initialize miniature");
  newArt->translate(glm::vec3(6, -27, -17));
  delete  obj[obj.size() - 2];
  obj[obj.size() - 2] = newArt;
}

void	Menu::newSkinP2(const std::string &name)
{
  Object	*newArt = new Art(name);

  if (newArt->initialize() == false)
    throw BomberException("Cannot initialize miniature");
  newArt->translate(glm::vec3(-8, -27, -17));
  delete  obj[obj.size() - 1];
  obj[obj.size() - 1] = newArt;
}

void	Menu::printNewSkin(const std::string &name, bool pl)
{
  std::string	pathArt = "Includes/GDL_lib/assets/Players/";

  pathArt += name;
  pathArt += ".fbx";
  if (pl == false) {
    newSkinP1(name);
    config.setSkinP1(pathArt);
  }
  else {
    newSkinP2(name);
    config.setSkinP2(pathArt);
  }
}


const std::string	&Menu::switchSkin(bool pl) const
{
  std::vector<std::string>::const_iterator	it = skinSelec->begin();
  int	iteration = 0;
  int	cursor;

  if (pl == false)
    cursor = skinP1Cursor;
  else
    cursor = skinP2Cursor;
  while (iteration != cursor) {
    ++it;
    ++iteration;
  }
  return *it;
}


void	Menu::printTime()
{
  String	*_timeVal = new String(ssTime.str());

  _timeVal->translate(glm::vec3(3, -29, -17));
  delete strings[8];
  strings[8] = _timeVal;
}

void	Menu::printNbIA()
{
  String	*_IAVal = new String(ssIA.str());

  _IAVal->translate(glm::vec3(-2, -29, -17));
  delete strings[9];
  strings[9] = _IAVal;
}

void	Menu::NGUpUpdate()
{
  selecSound.play();
  --sel[1];
  if (sel[1] < 0)
    sel[1] = 5;
  strings[pSel[1]]->translate(glm::vec3(0, 0, 1));
  strings[sel[1]]->translate(glm::vec3(0, 0 , -1));
}

void	Menu::NGDownUpdate()
{
  selecSound.play();
  ++sel[1];
  if (sel[1] > 5)
    sel[1] = 0;
  strings[pSel[1]]->translate(glm::vec3(0, 0, 1));
  strings[sel[1]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::NGMultiplayer(bool direction)
{
  if (config.getMultiPlayer() != direction) {
    if (config.getMultiPlayer() == true) {
      config.setMultiPlayer(direction);
      strings[6]->translate(glm::vec3(0, 0, -1));
      strings[7]->translate(glm::vec3(0, 0, 1));
    }
    else {
      config.setMultiPlayer(direction);
      strings[6]->translate(glm::vec3(0, 0, 1));
      strings[7]->translate(glm::vec3(0, 0, -1));
    }
  }
}

void	Menu::NGTimeLimit(bool direction)
{
  if (direction == false) {
    if (config.getTimeLimit() <= 2)
      return;
    config.setTimeLimit(config.getTimeLimit() - 1);
  }
  else {
    if (config.getTimeLimit() == 10)
      return;
    config.setTimeLimit(config.getTimeLimit() + 1);
  }
  ssTime.str("");
  ssTime << config.getTimeLimit();
  printTime();
}

void	Menu::NGNbIA(bool direction)
{
  if (direction == false) {
    if (config.getNbIA() == 0)
      return;
    config.setNbIA(config.getNbIA() - 1);
  }
  else {
    if (config.getNbIA() >= 9999)
      return;
    config.setNbIA(config.getNbIA() + 1);
  }
  ssIA.str("");
  ssIA << config.getNbIA();
  printNbIA();
}

void	Menu::NGMapCursor(bool direction)
{
  if (direction == false) {
    --mapCursor;
    if (mapCursor < 0)
      mapCursor = mapSelec->size() - 1;
  }
  else {
    ++mapCursor;
    if (static_cast<unsigned int>(mapCursor) >= mapSelec->size())
      mapCursor = 0;
  }
  printNewMap(switchMap());
}

void	Menu::NGSkinCursor(bool direction)
{
  if (direction == false) {
    --skinP1Cursor;
    if (skinP1Cursor < 0)
      skinP1Cursor = skinSelec->size() - 1;
  }
  else {
    ++skinP1Cursor;
    if (static_cast<unsigned int>(skinP1Cursor) >= skinSelec->size())
      skinP1Cursor = 0;
  }
  printNewSkin(switchSkin(false), false);
}

void	Menu::NGLeftUpdate()
{
  if (sel[1] != 5)
    (this->*NGRedirect[sel[1]])(false);
}

void	Menu::NGRightUpdate()
{
  if (sel[1] != 5)
    (this->*NGRedirect[sel[1]])(true);
}

void	Menu::NGQUpdate()
{
  if (sel[1] == 1)
    {
      --skinP2Cursor;
      if (skinP2Cursor < 0)
	skinP2Cursor = skinSelec->size() -1;
      printNewSkin(switchSkin(true), true);
    }
}

void	Menu::NGDUpdate()
{
  if (sel[1] == 1)
    {
      ++skinP2Cursor;
      if (static_cast<unsigned int>(skinP2Cursor) >= skinSelec->size())
	skinP2Cursor = 0;
      printNewSkin(switchSkin(true), true);
    }
}

void	Menu::NGReturnUpdate()
{
  Object	*tmp = obj.back();
  obj.pop_back();
  delete tmp;
  tmp = obj.back();
  obj.pop_back();
  delete tmp;
  if (sel[1] == 5) {
    config.setMultiPlayer(false);
    id_menu = 0;
  }
  else {
    _ng = true;
    config.setSave("");
  }
  return;
}

bool	Menu::NGUpdate()
{
  pSel[1] = sel[1];
  for (std::vector<std::pair<int, ufptr> >::iterator it = NGUpdateVec.begin();
       it != NGUpdateVec.end(); ++it)
    {
      if (inputs.getKey((*it).first, true)) {
	selecSound.play();
	(this->*(*it).second)();
      }
    }
  return true;
}

void	Menu::printNewSave(const std::string &save)
{
  String	*newSave = new String(save);
  std::string	pathSave;

  delete strings[0];
  newSave->translate(glm::vec3(6, -30, -18));
  strings[0] = newSave;
}

const std::string	&Menu::switchSave() const
{
  std::vector<std::string>::const_iterator	it = savesFiles.begin();
  int	iteration = 0;

  while (iteration != saveCursor) {
    ++it;
    ++iteration;
  }
  config.setSave(*it);
  return *it;
}

void	Menu::LGUpUpdate()
{
  --sel[2];
  if (sel[2] < 0)
    sel[2] = 1;
  strings[pSel[2]]->translate(glm::vec3(0, 0, 1));
  strings[sel[2]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::LGDownUpdate()
{
  ++sel[2];
  if (sel[2] > 1)
    sel[2] = 0;
  strings[pSel[2]]->translate(glm::vec3(0, 0, 1));
  strings[sel[2]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::LGLeftUpdate()
{
  --saveCursor;
  if (saveCursor < 0)
    saveCursor = savesFiles.size() - 1;
  printNewSave(switchSave());
}

void	Menu::LGRightUpdate()
{
  ++saveCursor;
  if (static_cast<unsigned int>(saveCursor) >= savesFiles.size())
    saveCursor = 0;
  printNewSave(switchSave());
}

void	Menu::LGReturnUpdate()
{
  if (sel[2] == 0) {
    _ng = true;
    return;
  }
  else if (sel[2] == 1)
    id_menu = 0;
}

bool	Menu::LGUpdate()
{
  pSel[2] = sel[2];
  for (std::vector<std::pair<int, ufptr> >::iterator it = LGUpdateVec.begin();
       it != LGUpdateVec.end(); ++it)
    {
      if (inputs.getKey((*it).first, true)) {
	selecSound.play();
	(this->*(*it).second)();
      }
    }
  return true;
}

bool	Menu::volumeMod(bool variation)
{
  String		*tmp;
  std::stringstream	tval;
  unsigned int		val;

  val = config.getGlobalVolume();
  if (variation == false) {
    if (val == 0)
      return true;
    val -= 10;
  }
  else {
    if (val == 100)
      return true;
    val += 10;
  }
  tval << val;
  tmp = new String(tval.str());
  tmp->translate(glm::vec3(-2.5f, -29, -17));
  strings.push_back(tmp);
  menuTheme.setVolume(val);
  selecSound.setVolume(val);
  config.setGlobalVolume(val);
  ssVol.str("");
  ssVol.str(tval.str());
  return true;
}

void	Menu::setInput()
{
  glm::vec3	translationVec;

  for (std::vector<std::pair<int, std::string> >::const_iterator pos = keyCode.begin();
       pos != keyCode.end(); ++pos)
    {
      if (inputs.getKey((*pos).first, true))
	{
	  if (sel[5] <= 5) {
	    config.setP1InputKey(static_cast<InputKey>(sel[5]), (*pos).first);
	    translationVec = glm::vec3(4.7f, -24 - sel[5], -15);
	  }
	  else {
	    config.setP2InputKey(static_cast<InputKey>(sel[5] - 6), (*pos).first);
	    translationVec = glm::vec3(-1, -24 - (sel[5] - 6), -15);
	  }
	  String	*tmp = new String((*pos).second);
	  tmp->translate(translationVec);
	  strings[sel[5] + 15] = tmp;
	  chInput = false;
	  break;
	}
    }
}

void	Menu::InputUpUpdate()
{
  --sel[5];
  if (sel[5] < 0)
    sel[5] = 12;
  strings[pSel[5] + 2]->translate(glm::vec3(0, 0, 1));
  strings[sel[5] + 2]->translate(glm::vec3(0, 0, -1));
}

void	Menu::InputDownUpdate()
{
  ++sel[5];
  if (sel[5] > 12)
    sel[5] = 0;
  strings[pSel[5] + 2]->translate(glm::vec3(0, 0, 1));
  strings[sel[5] + 2]->translate(glm::vec3(0, 0, -1));
}

void	Menu::InputReturnUpdate()
{
  if (sel[5] == 12)
    id_menu = 3;
  else
    chInput = true;
}

bool	Menu::InputsUpdate()
{
  pSel[5] = sel[5];
  if (chInput == true)
    setInput();
  else {
    for (std::vector<std::pair<int, ufptr> >::iterator it = InputUpdateVec.begin();
	 it != InputUpdateVec.end(); ++it)
      {
	if (inputs.getKey((*it).first, true)) {
	  selecSound.play();
	  (this->*(*it).second)();
	}
      }
  }
  return true;
}
void	Menu::ConfigUpUpdate()
{
  --sel[3];
  if (sel[3] < 0)
    sel[3] = 2;
  strings[pSel[3]]->translate(glm::vec3(0, 0, 1));
  strings[sel[3]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::ConfigDownUpdate()
{
  ++sel[3];
  if (sel[3] > 2)
    sel[3] = 0;
  strings[pSel[3]]->translate(glm::vec3(0, 0, 1));
  strings[sel[3]]->translate(glm::vec3(0, 0, -1));
}

void	Menu::ConfigLeftUpdate()
{
  if (sel[3] == 0)
    {
      if (config.getGlobalVolume() == 0)
	return;
      String	*tmp;
      tmp = strings.back();
      strings.pop_back();
      delete tmp;
      if (volumeMod(false) == false)
	return;
    }
}

void	Menu::ConfigRightUpdate()
{
  if (sel[3] == 0)
    {
      if (config.getGlobalVolume() == 100)
	return;
      String	*tmp;
      tmp = strings.back();
      strings.pop_back();
      delete tmp;
      if (volumeMod(true) == false)
	return;
    }
}

void	Menu::ConfigReturnUpdate()
{
  if (sel[3] == 1)
    id_menu = 5;
  else if (sel[3] == 2)
    id_menu = 0;
}

bool	Menu::ConfigUpdate()
{
  pSel[3] = sel[3];
  for (std::vector<std::pair<int, ufptr> >::iterator it = ConfigUpdateVec.begin();
       it != ConfigUpdateVec.end(); ++it)
    {
      if (inputs.getKey((*it).first, true)) {
	selecSound.play();
	(this->*(*it).second)();
      }
    }
  return true;
}

bool	Menu::RankUpdate()
{
  if (inputs.getKey(SDLK_RETURN, true)) {
    selecSound.play();
    id_menu = 0;
  }
  return true;
}

bool	Menu::update()
{
  context.updateClock(clock);
  context.updateInputs(inputs);
  if (_endintro) {
    (this->*MenuUpdate[id_menu])();
    if (id_menu == 6)
      return false;
    if (prev_id != id_menu)
      {
	sel[prev_id] = 0;
	pSel[prev_id] = 0;
	prev_id = id_menu;
	SwitchView();
	(this->*MenuView[id_menu])();
      }
  }
  return true;
}

void	Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  glm::vec3 tmpRot = obj[0]->getRotation();
  tmpRot.y += 0.03;
  obj[0]->setRotation(tmpRot);
  for (size_t i = 0; i < obj.size(); ++i)
    obj[i]->draw(shader, clock);
  if (_endintro)
    for (size_t i = 0; i < strings.size(); ++i)
      strings[i]->draw(shader, clock);
  context.flush();
}

bool	Menu::HomeMenu()
{
  String	*_newGame = new String("NEW GAME");
  String	*_loadGame = new String("LOAD GAME");
  String	*_config = new String("CONFIGURATION");
  String	*_ranking = new String("RANKING");
  String	*_exit = new String("EXIT");

  _newGame->translate(glm::vec3(3.5f, -32, -18));
  _loadGame->translate(glm::vec3(4, -33, -17));
  _config->translate(glm::vec3(6, -34, -17));
  _ranking->translate(glm::vec3(3, -35, -17));
  _exit->translate(glm::vec3(1.5f, -36, -17));

  strings.push_back(_newGame);
  strings.push_back(_loadGame);
  strings.push_back(_config);
  strings.push_back(_ranking);
  strings.push_back(_exit);

  return true;
}

bool	Menu::NewGame()
{
  // Scrolling view to get Map on which you means to play
  // Scrooling view to choose your character
  // Enable multiplayer (which activate a second source of inputs for character selection)
  String	*_map = new String("MAPS");
  String	*_skin = new String("SKIN");
  String	*_multiplayer = new String("PLAYERS");
  String	*_nbIA = new String("IA");
  String	*_IAValue = new String(ssIA.str());
  String	*_timelimit = new String("TIME");
  String	*_timeVal = new String(ssTime.str());
  String	*_nb1 = new String("1");
  String	*_nb2 = new String("2");
  String	*_back = new String("BACK");
  String	*_mapSelec = new String(mapSelec->front());
  Object	*skinP1 = new Art(skinSelec->front());
  Object	*skinP2 = new Art(skinSelec->front());
  std::string	path;

  if (skinP1->initialize() == false
      || skinP2->initialize() == false)
    return false;
  _multiplayer->translate(glm::vec3(3, -24, -18));
  config.setMultiPlayer(false);
  _nb1->translate(glm::vec3(2, -25.5f, -18));
  _nb2->translate(glm::vec3(-2, -25.5f, -17));
  _skin->translate(glm::vec3(1.5f, -27, -17));
  _timelimit->translate(glm::vec3(4, -28, -17));
  _timeVal->translate(glm::vec3(3, -29, -17));
  _nbIA->translate(glm::vec3(-2, -28, -17));
  _IAValue->translate(glm::vec3(-2, -29, -17));
  _map->translate(glm::vec3(1.5f, -31, -17));
  _mapSelec->translate(glm::vec3(1.5f, -33, -17));
  _back->translate(glm::vec3(1.5f, -36, -17));
  skinP1->translate(glm::vec3(6, -27, -17));
  skinP2->translate(glm::vec3(-8, -27, -17));
  strings.push_back(_multiplayer);
  strings.push_back(_skin);
  strings.push_back(_timelimit);
  strings.push_back(_nbIA);
  strings.push_back(_map);
  strings.push_back(_back);
  strings.push_back(_nb1);
  strings.push_back(_nb2);
  strings.push_back(_timeVal);
  strings.push_back(_IAValue);
  strings.push_back(_mapSelec);
  obj.push_back(skinP1);
  obj.push_back(skinP2);
  path = "Includes/GDL_lib/assets/Players/";
  path += skinSelec->front();
  path += ".fbx";
  config.setSkinP1(path);
  config.setSkinP2(path);
  return true;
}

bool	Menu::LoadGame() {
  String	*_saveFiles = new String(savesFiles.front());
  String	*_back = new String("BACK");

  _saveFiles->translate(glm::vec3(6, -30, -18));
  _back->translate(glm::vec3(1.5f, -34, -17));
  strings.push_back(_saveFiles);
  strings.push_back(_back);
  config.setSave(savesFiles.front());
  return true;
}

bool	Menu::Config()
{
  String	*_volume = new String("VOLUME");
  String	*_value = new String(ssVol.str());
  String	*_pInputs = new String("PLAYER INPUTS");
  String	*_back = new String("BACK");

  _volume->translate(glm::vec3(4.25f, -29, -18));
  _value->translate(glm::vec3(-2.5f, -29, -17));
  _pInputs->translate(glm::vec3(5.5f, -32, -17));
  _back->translate(glm::vec3(1.5f, -35, -17));
  strings.push_back(_volume);
  strings.push_back(_pInputs);
  strings.push_back(_back);
  strings.push_back(_value);
  return true;
}

const std::string	Menu::getRankingName(int pos) const
{
  return highScore.getHighScore(pos).first;
}

const std::string	Menu::getRankingScore(int pos) const
{
  std::stringstream	ret;

  ret << highScore.getHighScore(pos).second;
  return ret.str();
}

bool	Menu::Ranking()
{
  String	*_fpos = new String("1ST");
  String	*_fname = new String(getRankingName(0));
  String	*_fscore = new String(getRankingScore(0));
  String	*_spos = new String("2ND");
  String	*_sname = new String(getRankingName(1));
  String	*_sscore = new String(getRankingScore(1));
  String	*_tpos = new String("3RD");
  String	*_tname = new String(getRankingName(2));
  String	*_tscore = new String(getRankingScore(2));
  String	*_forthPos = new String("4TH");
  String	*_forthName = new String(getRankingName(3));
  String	*_forthScore = new String(getRankingScore(3));
  String	*_fifthPos = new String("5TH");
  String	*_fifthName = new String(getRankingName(4));
  String	*_fifthScore = new String(getRankingScore(4));
  String	*_back = new String("BACK");

  _fpos->translate(glm::vec3(10, -23, -15));
  _fname->translate(glm::vec3(6, -23, -15));
  _fscore->translate(glm::vec3(-6, -23, -15));
  _spos->translate(glm::vec3(10, -25, -15));
  _sname->translate(glm::vec3(6, -25, -15));
  _sscore->translate(glm::vec3(-6, -25, -15));
  _tpos->translate(glm::vec3(10, -27, -15));
  _tname->translate(glm::vec3(6, -27, -15));
  _tscore->translate(glm::vec3(-6, -27, -15));
  _forthPos->translate(glm::vec3(10, -29, -15));
  _forthName->translate(glm::vec3(6, -29, -15));
  _forthScore->translate(glm::vec3(-6, -29, -15));
  _fifthPos->translate(glm::vec3(10, -31, -15));
  _fifthName->translate(glm::vec3(6, -31, -15));
  _fifthScore->translate(glm::vec3(-6, -31, -15));
  _back->translate(glm::vec3(1.5f, -35, -18));
  strings.push_back(_fpos);
  strings.push_back(_fname);
  strings.push_back(_fscore);
  strings.push_back(_spos);
  strings.push_back(_sname);
  strings.push_back(_sscore);
  strings.push_back(_tpos);
  strings.push_back(_tname);
  strings.push_back(_tscore);
  strings.push_back(_forthPos);
  strings.push_back(_forthName);
  strings.push_back(_forthScore);
  strings.push_back(_fifthPos);
  strings.push_back(_fifthName);
  strings.push_back(_fifthScore);
  strings.push_back(_back);
  return true;
}

const std::string	Menu::getStringInputKey(bool player, InputKey key) const
{
  int	tmp;

  if (player == false)
    tmp = config.getP1Inputs().getKey(key);
  else
    tmp = config.getP2Inputs().getKey(key);
  for (std::vector<std::pair<int, std::string> >::const_iterator pos = keyCode.begin();
       pos != keyCode.end(); ++pos)
    {
      if (tmp == (*pos).first)
	return (*pos).second;
    }
  return NULL;
}

bool	Menu::Inputs()
{
  String	*_p1 = new String("PLAYER 1");
  String	*_p1Up = new String("UP");
  String	*_p1Left = new String("LEFT");
  String	*_p1Right = new String("RIGHT");
  String	*_p1Down = new String("DOWN");
  String	*_p1Bomb = new String("BOMB");
  String	*_p1SBomb = new String("SBOMB");
  String	*_p1UpKey = new String(getStringInputKey(0, UP_KEY));
  String	*_p1LeftKey = new String(getStringInputKey(0, LEFT_KEY));
  String	*_p1RightKey = new String(getStringInputKey(0, RIGHT_KEY));
  String	*_p1DownKey = new String(getStringInputKey(0, DOWN_KEY));
  String	*_p1BombKey = new String(getStringInputKey(0, BOMB_KEY));
  String	*_p1SBombKey = new String(getStringInputKey(0, SWITCHBOMB_KEY));
  String	*_p2 = new String("PLAYER 2");
  String	*_p2Up = new String("UP");
  String	*_p2Left = new String("LEFT");
  String	*_p2Right = new String("RIGHT");
  String	*_p2Down = new String("DOWN");
  String	*_p2Bomb = new String("BOMB");
  String	*_p2SBomb = new String("SBOMB");
  String	*_p2UpKey = new String(getStringInputKey(1, UP_KEY));
  String	*_p2LeftKey = new String(getStringInputKey(1, LEFT_KEY));
  String	*_p2RightKey = new String(getStringInputKey(1, RIGHT_KEY));
  String	*_p2DownKey = new String(getStringInputKey(1, DOWN_KEY));
  String	*_p2BombKey = new String(getStringInputKey(1, BOMB_KEY));
  String	*_p2SBombKey = new String(getStringInputKey(1, SWITCHBOMB_KEY));
  String	*_back = new String("BACK");

  _p1->translate(glm::vec3(10, -22, -15));
  _p2->translate(glm::vec3(-3, -22, -15));
  _p1Up->translate(glm::vec3(10.5f, -24, -16));
  _p1UpKey->translate(glm::vec3(4.7f, -24, -15));
  _p1Left->translate(glm::vec3(10.5f, -25, -15));
  _p1LeftKey->translate(glm::vec3(4.7f, -25, -15));
  _p1Right->translate(glm::vec3(10.5f, -26, -15));
  _p1RightKey->translate(glm::vec3(4.7f, -26, -15));
  _p1Down->translate(glm::vec3(10.5f, -27, -15));
  _p1DownKey->translate(glm::vec3(4.7f, -27, -15));
  _p1Bomb->translate(glm::vec3(10.5f, -28, -15));
  _p1BombKey->translate(glm::vec3(4.7f, -28, -15));
  _p1SBomb->translate(glm::vec3(10.5f, -29, -15));
  _p1SBombKey->translate(glm::vec3(4.7f, -29, -15));
  _p2Up->translate(glm::vec3(-6.7f, -24, -15));
  _p2UpKey->translate(glm::vec3(-1, -24, -15));
  _p2Left->translate(glm::vec3(-6.7f, -25, -15));
  _p2LeftKey->translate(glm::vec3(-1, -25, -15));
  _p2Right->translate(glm::vec3(-6.7f, -26, -15));
  _p2RightKey->translate(glm::vec3(-1, -26, -15));
  _p2Down->translate(glm::vec3(-6.7f, -27, -15));
  _p2DownKey->translate(glm::vec3(-1, -27, -15));
  _p2Bomb->translate(glm::vec3(-6.7f, -28, -15));
  _p2BombKey->translate(glm::vec3(-1, -28, -15));
  _p2SBomb->translate(glm::vec3(-6.7f, -29, -15));
  _p2SBombKey->translate(glm::vec3(-1, -29, -15));
  _back->translate(glm::vec3(1.5f, -32, -15));
  strings.push_back(_p1);
  strings.push_back(_p2);
  strings.push_back(_p1Up);
  strings.push_back(_p1Left);
  strings.push_back(_p1Right);
  strings.push_back(_p1Down);
  strings.push_back(_p1Bomb);
  strings.push_back(_p1SBomb);
  strings.push_back(_p2Up);
  strings.push_back(_p2Left);
  strings.push_back(_p2Right);
  strings.push_back(_p2Down);
  strings.push_back(_p2Bomb);
  strings.push_back(_p2SBomb);
  strings.push_back(_back);
  strings.push_back(_p1UpKey);
  strings.push_back(_p1LeftKey);
  strings.push_back(_p1RightKey);
  strings.push_back(_p1DownKey);
  strings.push_back(_p1BombKey);
  strings.push_back(_p1SBombKey);
  strings.push_back(_p2UpKey);
  strings.push_back(_p2LeftKey);
  strings.push_back(_p2RightKey);
  strings.push_back(_p2DownKey);
  strings.push_back(_p2BombKey);
  strings.push_back(_p2SBombKey);
  return true;
}

bool	Menu::SwitchView()
{
  String	*tmp;

  while (!strings.empty())
    {
      tmp = strings.back();
      strings.pop_back();
      delete tmp;
    }
  return true;
}

const Configuration	&Menu::getConfig() const
{
  return config;
}
