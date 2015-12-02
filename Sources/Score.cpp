//
// Score.cpp for Nibbler in /home/joliva_d/rendu/cpp_nibbler/Srcs/Nibbler/Game
// 
// Made by Jolivald Dorian
// Login   <joliva_d@epitech.net>
// 
// Started on  Sat Apr  4 16:44:58 2015 Jolivald Dorian
// Last update Sun Apr  5 17:42:39 2015 Jolivald Dorian
//

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Score.hh"
#include "StringConversion.hh"

Score::Score():
  FILEPATH("./Resources/scoreFile")
{
}

Score::~Score()
{
  while (!_highScore.empty())
    {
      Person *tmp = _highScore.back();
      _highScore.pop_back();
      delete tmp;
    }
}

void		Score::addHighScore(const std::string & name, size_t score) const
{
  std::ofstream	file(FILEPATH.c_str(), std::ios_base::app);
  std::string	highscore(name);

  if (!file.is_open())
    {
      std::cerr << "Sorry, cant open highscore, can't save your." << std::endl;
      return;
    }
  highscore += ":";
  highscore += typeToString(score);
  file << std::endl << highscore;
  file.close();
}

void		Score::parseHighscore(const std::string & line)
{
  std::string	name;
  size_t	score;
  size_t	pos;

  if ((pos = line.find(":")) == std::string::npos)
    return;
  name = line.substr(0, pos);
  score = stringToType<size_t>(line.substr(pos + 1));
  _highScore.push_back(new Person(name, score));
}

void		Score::loadHighScore(void)
{
  std::fstream	file(FILEPATH.c_str());
  std::string	line;

  if (!file.is_open())
    {
      std::cerr << "Sorry, cant open highscore, can't save your." << std::endl;
      return;
    }

  while (!_highScore.empty())
    {
      Person *tmp = _highScore.back();
      _highScore.pop_back();
      delete tmp;
    }

  while (getline(file, line))
    this->parseHighscore(line);
  file.close();
  this->sortHighScore();
}

void		Score::sortHighScore(void)
{
  sortFunctor f;

  std::sort(_highScore.begin(), _highScore.end(), f);
}

const std::vector<Score::Person *>	&Score::getHighScore(void) const
{
  return _highScore;
}

std::pair<const std::string, size_t>	Score::getHighScore(int i) const
{
  if (static_cast<size_t>(i) >= _highScore.size())
    return std::pair<const std::string, size_t>("ANON", 0);

  Person *p = _highScore[i];
  std::pair<const std::string, size_t> score(p->getName().substr(0, 6), p->getScore());
  return score;
}

Score::Person::Person(const std::string & name, size_t score):
  _name(name),
  _score(score)
{
}

Score::Person::~Person()
{
}

const std::string	&Score::Person::getName() const
{
  return _name;
}

size_t		Score::Person::getScore() const
{
  return _score;
}
