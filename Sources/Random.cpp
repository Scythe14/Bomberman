#include <ctime>
#include <cstdlib>
#include "Random.hh"

void	Random::init(void)
{
  srand(time(0));
}

int	Random::getRand()
{
  return random();
}

int	Random::getRand(int mod)
{
  return random() % mod;
}
