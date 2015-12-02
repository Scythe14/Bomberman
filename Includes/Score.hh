//
// Score.hh for nibbler in /home/joliva_d/rendu/cpp_nibbler/Srcs/Nibbler/Game
// 
// Made by Jolivald Dorian
// Login   <joliva_d@epitech.net>
// 
// Started on  Sat Apr  4 16:44:45 2015 Jolivald Dorian
// Last update Sun Apr  5 17:42:31 2015 Jolivald Dorian
//

#ifndef __SCORE_HH_
# define __SCORE_HH_

# include <string>
# include <cstdlib>
# include <vector>
# include <utility>

class Score
{
public:
  class Person
  {
  private:
    std::string				_name;
    size_t				_score;
  public:
    Person(const std::string & name, size_t score);
    ~Person();
    const std::string			&getName() const;
    size_t				getScore() const;
  };

public:
  Score();
  ~Score();
  const std::vector<Person *>		&getHighScore(void) const;
  std::pair<const std::string, size_t>	getHighScore(int pos) const;
  void					addHighScore(const std::string & name, size_t score) const;
  void					loadHighScore(void);

private:
  void					parseHighscore(const std::string & line);
  void					sortHighScore(void);

  const std::string			FILEPATH;
  std::vector<Person *>			_highScore;

  struct sortFunctor
  {
    bool operator()(const Score::Person *a, const Score::Person *b)
    {
      if (a->getScore() > b->getScore())
	return true;
      return false;
    }
  };
};

#endif
