#ifndef STRING_HH_
# define STRING_HH_

# include <string>
# include <vector>
# include "Char.hh"
# include "Object.hh"

class String : public Object {

private:
  std::string		text;
  std::vector<Char*>	graphic;

public:
  String(const std::string&);
  String(const std::string&, int, int, int);
  virtual	~String();
  virtual void	draw(gdl::AShader &, gdl::Clock const&);
  virtual void	translate(glm::vec3 const&);
  virtual void	scale(glm::vec3 const&);
  bool		resetString(const std::string&);
  void		MoveChar(float, float, float);
  std::string	getText() const;
};

#endif /* !STRING_HH_ */
