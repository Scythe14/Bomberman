#ifndef MENU_HH_
# define MENU_HH_

# include <iostream>
# include <vector>
# include <sstream>
# include <utility>
# include <SFML/Audio.hpp>
# include <SFML/System.hpp>
# include "Configuration.hh"
# include "Object.hh"
# include "PlayerInput.hh"
# include "Score.hh"
# include "String.hh"
# include "MenuBox.hpp"
# include "Art.hh"
# include "SaveGame.hh"
# include "Skybox.hh"
# include "utils.hpp"

class Menu {

private:
  typedef bool	(Menu::*fptr)();
  typedef void	(Menu::*ufptr)();
  typedef void	(Menu::*vfptr)(bool);

  // GDL REQUIREMENT
  gdl::SdlContext	context;
  gdl::Clock		clock;
  gdl::Input		inputs;
  gdl::BasicShader	shader;

  // CAMERA ATTRIBUTE
  glm::mat4		projection;
  glm::mat4		transformation;

  // DISPLAYS OBJECTS
  std::vector<Object*>	obj;
  std::vector<String*>	strings;

  // PARAMETERS ATTRIBUTE
  std::stringstream	ssVol;
  std::stringstream	ssIA;
  std::stringstream	ssTime;
  int			nb_player;

  // POINTER TO MEMBER FUNCTIONS ARRAYS
  fptr			MenuUpdate[6];
  fptr			MenuView[6];

  // UPDATE FUNCTIONS AND PTR TO MEMBERS FUNCTIONS ARRAYS
  std::vector<std::pair<int, ufptr> >	HomeUpdateVec;
  void			HomeUpUpdate();
  void			HomeDownUpdate();
  void			HomeReturnUpdate();

  std::vector<std::pair<int, ufptr> >	NGUpdateVec;
  void			NGUpUpdate();
  void			NGDownUpdate();
  void			NGLeftUpdate();
  vfptr			NGRedirect[5];
  void			NGMultiplayer(bool);
  void			NGTimeLimit(bool);
  void			NGNbIA(bool);
  void			NGMapCursor(bool);
  void			NGSkinCursor(bool);
  void			NGRightUpdate();
  void			NGReturnUpdate();
  void			NGQUpdate();
  void			NGDUpdate();

  std::vector<std::pair<int, ufptr> >	LGUpdateVec;
  void			LGUpUpdate();
  void			LGDownUpdate();
  void			LGLeftUpdate();
  void			LGRightUpdate();
  void			LGReturnUpdate();

  std::vector<std::pair<int, ufptr> >	ConfigUpdateVec;
  void			ConfigUpUpdate();
  void			ConfigDownUpdate();
  void			ConfigLeftUpdate();
  void			ConfigRightUpdate();
  void			ConfigReturnUpdate();

  std::vector<std::pair<int, ufptr> > InputUpdateVec;
  void			InputUpUpdate();
  void			InputDownUpdate();
  void			InputReturnUpdate();


  // VARIOUS ID
  int			prev_id;
  int			id_menu; // 0 - Main Menu || 1 NEW GAME || 2 LOAD || 3 CONFIG || 4 RANKING || 5 inputs
  // GENERAL ID ARRAYS
  int			sel[6]; // 0 - New Game | 1 - Load | 2 - Config | 3 - Ranking | 4 - EXIT
  int			pSel[6];
  // BOOL TRIGGERS
  bool			_ng;
  bool			chInput;
  bool			_endintro;
  // CONFIGURATION INSTANCE
  Configuration		&config;
  // DATA CONTAINERS AND ASSOCIATES CURSOR
  std::vector<std::string>	*mapSelec;
  int				mapCursor;
  std::vector<std::string>	savesFiles;
  int				saveCursor;
  std::vector<std::string>	*skinSelec;
  int				skinP1Cursor;
  int				skinP2Cursor;
  Score				highScore;
  // AUDIO VARIABLES
  sf::Music		menuTheme;
  sf::SoundBuffer	soundBuf;
  sf::Sound		selecSound;
  // MISC
  std::vector<std::pair<int, std::string> >	keyCode;

  // SWITCH PARAMETERS FUNCTIONS
  const std::string	&switchMap() const;
  const std::string	&switchSave() const;
  const std::string	&switchSkin(bool) const;
  // DISPLAY NEW STRINGS FUNCTIONS
  void	printNewMap(const std::string&);
  void	printNewSave(const std::string&);
  void	newSkinP1(const std::string&);
  void	newSkinP2(const std::string&);
  void	printNewSkin(const std::string&, bool);
  void	printTime();
  void	printNbIA();
  const std::string	getRankingName(int) const;
  const std::string	getRankingScore(int) const;
public:
  Menu(Configuration&);
  ~Menu();

  // INIT
  void	initKeyCode();
  bool	initialize(bool);

  // UPDATE AND DRAW PROCESS
  bool	update();
  void	draw();

  bool	intro();
  bool	checkNG() const;
  const std::string getStringInputKey(bool, InputKey) const;
  // UPDATES FUNCTIONS
  bool	HomeUpdate();
  bool	NGUpdate();
  bool	LGUpdate();
  bool	ConfigUpdate();
  bool	InputsUpdate();
  void	setInput();
  bool	volumeMod(bool);
  bool	RankUpdate();
  // INIT FUNCTIONS
  bool	HomeMenu();
  bool	NewGame();
  bool	LoadGame();
  bool	Config();
  bool	Ranking();
  bool	Inputs();
  // SWITCH BETWEEN MENU SELECTION
  bool	SwitchView();
  // GETTER FOR CONFIGURATION OBJECT
  const Configuration	&getConfig() const;
};

#endif /* !MENU_HH_ */
