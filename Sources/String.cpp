#include "BomberException.hpp"
#include "String.hh"

String::String(const std::string &src)
  : text(src)
{
  int	space = 0;
  int	ct = 0;

  for (std::string::iterator it = text.begin(); it != text.end(); ++it)
    {
      if (*it != ' ')
	{
	  graphic.push_back(new Char(*it));
	  if (graphic[ct]->initialize() == false)
	    throw BomberException("Unable to load Char texture");
	  graphic[ct]->translate(glm::vec3(-(space * 1), 0, 0));
	  ++ct;
	}
      ++space;
    }
}

String::String(const std::string &src, int n, int x, int y)
  : text(src)
{
  int	space = 0;
  int	ct = 0;
  glm::vec3 tmp;

  for (std::string::iterator it = text.begin(); it != text.end(); ++it)
    {
      if (*it != ' ')
	{
	  graphic.push_back(new Char(*it));
	  if (graphic[ct]->initialize() == false)
	    throw BomberException("Unable to load Char texutre");
	  tmp = graphic[ct]->getRotation();
	  tmp.z += 180.0f;
	  graphic[ct]->setRotation(tmp);
	  graphic[ct]->MoveAtPos(glm::vec3(x + (space * n), y, 1));
	  ++ct;
	}
      ++space;
    }
}

String::~String()
{
  Char	*tmp;
  while (!graphic.empty())
    {
      tmp = graphic.back();
      graphic.pop_back();
      delete tmp;
    }
}

void	String::translate(glm::vec3 const &v)
{
  for (std::vector<Char*>::iterator it = graphic.begin(); it != graphic.end(); ++it)
    (*it)->translate(v);
}

void	String::MoveChar(float x, float y, float z)
{
  int	pos = 0;

  for (std::vector<Char*>::iterator it = graphic.begin(); it != graphic.end(); ++it) {
    (*it)->MoveAtPos(glm::vec3(x + pos, y, z));
    pos += 20;
  }
}

void	String::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  for (std::vector<Char*>::iterator it = graphic.begin(); it != graphic.end(); ++it)
    (*it)->draw(shader, clock);
}

void	String::scale(glm::vec3 const &v)
{
  for (std::vector<Char*>::iterator it = graphic.begin(); it != graphic.end(); ++it)
    (*it)->scale(v);
}

std::string	String::getText() const
{
  return text;
}
