#ifndef __UTILS_HPP__
# define __UTILS_HPP__

# include <fstream>
# include <iostream>
# include <iomanip>

namespace Utils
{
  std::vector<std::string>	*readDir(const std::string&, const std::string&);

  template <typename T>
  T	getNumData(std::fstream & data)
  {
    double	tmp;

    data >> tmp;
    if (data.fail())
      throw BomberException("Savegame seems to be corrupted");
    return (static_cast<T>(tmp));
  };
};

#endif /* __UTILS_HPP__ */
