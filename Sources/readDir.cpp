#include <dirent.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

namespace Utils
{
  std::vector<std::string>	*readDir(const std::string &path, const std::string &extension)
  {
    DIR *				rep = opendir(path.c_str());
    std::stringstream		ss;
    std::vector<std::string>	*tab;

    if (rep != NULL)
      {
	struct dirent *lecture;
	tab = new std::vector<std::string>;
	while ((lecture = readdir(rep)))
	  {
	    ss.str("");
	    ss <<  lecture->d_name;
	    std::string s = ss.str();
	    if (s.size() > 4)
	      if (s.compare(s.size() - 4, 4, extension) == 0)
		{
		  s.erase(s.end() - extension.size(), s.end());
		  tab->push_back(s);
		}
	  }
	closedir(rep);
      }
    return tab;
  }
}
