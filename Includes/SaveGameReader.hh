#ifndef SAVEGAMEREADER_HH__
# define SAVEGAMEREADER_HH__

# include <iostream>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <vector>

class SaveGameReader
{
  DIR                           *_dir;
  struct dirent                 *_dirp;

public:
  SaveGameReader();
  ~SaveGameReader();
  bool  openDir(std::string dirName);
  std::vector<std::string>  readDir();
};

#endif /* !DIREREADER_HH_ */
