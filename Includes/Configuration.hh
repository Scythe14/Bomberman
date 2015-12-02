#ifndef CONFIGURATION_HH_
# define CONFIGURATION_HH_

# include <string>
# include "PlayerInput.hh"

class Configuration
{
private:
  bool		multiPlayer;
  unsigned int	globalVolume;
  std::string	map;
  std::string	skinP1;
  std::string	skinP2;
  std::string	saveFile;
  PlayerInput	p1Inputs;
  PlayerInput	p2Inputs;
  unsigned int	timeLimit;
  unsigned int	nbIA;

public:
  Configuration();
  Configuration(const Configuration&);
  ~Configuration();

  bool		getMultiPlayer() const;
  unsigned int	getGlobalVolume() const;
  PlayerInput	getP1Inputs() const;
  PlayerInput	getP2Inputs() const;
  std::string	getMap() const;
  std::string	getSkinP1() const;
  std::string	getSkinP2() const;
  std::string	getSave() const;
  unsigned int	getTimeLimit() const;
  unsigned int	getNbIA() const;

  void	setSave(const std::string&);
  void	setMultiPlayer(bool);
  void	setGlobalVolume(unsigned int);
  void	setP1InputKey(InputKey, int);
  void	setP2InputKey(InputKey, int);
  void	setMap(const std::string&);
  void	setSkinP1(const std::string&);
  void	setSkinP2(const std::string&);
  void	setTimeLimit(unsigned int);
  void	setNbIA(unsigned int);
};

#endif /* !CONFIGURATION_HH_ */
