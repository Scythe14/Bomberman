# include "Time.hh"

time_t		Time::getCurrentTime()
{
  return time(0);
}

std::string	Time::getCurrentDate()
{
  time_t		t(time(0));
  std::stringstream	date;
  struct tm *		now = localtime(&t);

  date << (now->tm_mday ) << 'd'
       << now->tm_mon << 'M'
       << now->tm_hour << 'h'
       << now->tm_min << "m"
       << now->tm_sec << "s";
  return (date.str());
}
