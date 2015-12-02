#include <exception>
#include <iostream>
#include "Engine.hh"
#include "String.hh"
#include "SaveGame.hh"

int	main()
{
  Engine	_engine;

  try {
    if (_engine.initialize() == false)
      return (1);
    while (_engine.update() == true)
      _engine.draw();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
