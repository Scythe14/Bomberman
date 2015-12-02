#include <iostream>
#include "StringConversion.hh"
#include "GenerateMap.hh"
#include "Random.hh"

int	main(int ac, char **av)
{
  if (ac != 3)
    {
      std::cerr
	<< "Wrong parameters. Usage : ./generator [width] [height]"
	<< std::endl
	<< "Parameter must be greater than 1."
	<< std::endl;
      return 1;
    }
  Random::init();
  GenerateMap::gen(stringToType<int>(av[1]),stringToType<int>(av[2]));
  return 0;
}
