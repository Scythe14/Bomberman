#ifndef TIME_HH_
# define TIME_HH_

# include <ctime>
# include <sstream>

class Time
{
public:
  static time_t getCurrentTime();
  static std::string getCurrentDate();
};

#endif /* !TIME_HH_ */
