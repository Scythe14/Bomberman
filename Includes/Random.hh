#ifndef __RANDOM_HH__
# define __RANDOM_HH__

class Random
{
  Random();
  ~Random();
 public:
  static void	init(void);
  static int	getRand();
  static int	getRand(int);
};

#endif /* __RANDOM_HH__ */
