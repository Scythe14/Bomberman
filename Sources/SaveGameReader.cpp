#include "SaveGameReader.hh"

SaveGameReader::SaveGameReader(): _dir(NULL), _dirp(NULL)
{}

SaveGameReader::~SaveGameReader()
{
  if (_dir != NULL)
    closedir(_dir);
}

bool	SaveGameReader::openDir(std::string dirName)
{
  if ((_dir = opendir(dirName.c_str())) == NULL)
    {
      if (mkdir(dirName.c_str(), (S_IRWXU + S_IRGRP + S_IXGRP + S_IXOTH)) == -1)
	std::cerr << "cannot access " << dirName << ". No permission to create it"
		  << std::endl;
      return false;
    }
  return true;
}

std::vector<std::string>	SaveGameReader::readDir()
{
  std::vector<std::string>	saves;

  while (_dir != NULL && (_dirp = readdir(_dir)))
    {
      if (_dirp->d_name[0] != '.')
	saves.push_back(_dirp->d_name);
    }
  return saves;
}
