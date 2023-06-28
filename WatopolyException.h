#ifndef _WATOPOLY_EXCEPTION_H
#define _WATOPOLY_EXCEPTION_H

#include <string>

class WatopolyException {
protected:
  std::string msg;

public:
  WatopolyException(std::string msg);
  virtual std::string getMsg();
};

#endif
