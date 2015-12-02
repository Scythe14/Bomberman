#include "Configuration.hh"

Configuration::Configuration()
  : multiPlayer(false), globalVolume(100), map("Maps/sample1.map"), skinP1("Includes/GDL_lib/assets/Players/gold.fbx"), skinP2("Includes/GDL_lib/assets/Players/gold.fbx"), saveFile(""), p1Inputs(false), p2Inputs(true), timeLimit(2), nbIA(0) {}

Configuration::Configuration(const Configuration &ref)
  : multiPlayer(ref.getMultiPlayer()), globalVolume(ref.getGlobalVolume()),
    map(ref.getMap()), skinP1(ref.getSkinP1()), skinP2(ref.getSkinP2()), saveFile(""),
    p1Inputs(ref.getP1Inputs()), p2Inputs(ref.getP2Inputs()) {}

Configuration::~Configuration() {}

std::string	Configuration::getSave() const
{
  return saveFile;
}

bool		Configuration::getMultiPlayer() const
{
  return multiPlayer;
}

unsigned int	Configuration::getGlobalVolume() const
{
  return globalVolume;
}

std::string	Configuration::getMap() const
{
  return map;
}

std::string	Configuration::getSkinP1() const
{
  return skinP1;
}

std::string	Configuration::getSkinP2() const
{
  return skinP2;
}
PlayerInput	Configuration::getP1Inputs() const
{
  return p1Inputs;
}

PlayerInput	Configuration::getP2Inputs() const
{
  return p2Inputs;
}

unsigned int	Configuration::getTimeLimit() const
{
  return timeLimit;
}

unsigned int	Configuration::getNbIA() const
{
  return nbIA;
}

void	Configuration::setMultiPlayer(bool value)
{
  multiPlayer = value;
}
void	Configuration::setGlobalVolume(unsigned int volume)
{
  globalVolume = volume;
}

void	Configuration::setSave(const std::string &ref)
{
  saveFile = ref;
}

void	Configuration::setMap(const std::string &ref)
{
  map = ref;
}

void	Configuration::setSkinP1(const std::string &ref)
{
  skinP1 = ref;
}

void	Configuration::setSkinP2(const std::string &ref)
{
  skinP2 = ref;
}

void	Configuration::setP1InputKey(InputKey key, int val)
{
  p1Inputs.setKeyValue(key, val);
}

void	Configuration::setP2InputKey(InputKey key, int val)
{
  p2Inputs.setKeyValue(key, val);
}

void	Configuration::setTimeLimit(unsigned int val)
{
  timeLimit = val;
}

void	Configuration::setNbIA(unsigned int val)
{
  nbIA = val;
}
