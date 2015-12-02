#ifndef __STRINGCONVERSION_HH__
# define __STRINGCONVERSION_HH__

# include <iostream>
# include <iomanip>
# include <sstream>

template <typename T>
T			stringToType(std::string const& str)
{
  T			res;
  std::istringstream	ss(str);

  ss >> res;
  return (res);
}

template <typename T>
std::string		typeToString(T const& type)
{
  std::ostringstream	ss;

  ss << std::fixed << type;
  return (ss.str());
}

#endif /* !__STRINGCONVERSION_HH__ */
