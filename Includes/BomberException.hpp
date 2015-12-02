#ifndef BOMBEREXCEPTION_HH_
# define BOMBEREXCEPTION_HH_

# include <string>
# include <exception>
# include <sstream>

class BomberException : public std::exception {

private:
  std::string		message;

public:
  BomberException(const char * msg)
    : message(msg) {}

  ~BomberException() throw() {}

  const char	*what() const throw() {
    return (this->message.c_str());
  }
};

#endif /* !BOMBEREXCEPTION_HH_ */
