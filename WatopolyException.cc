#include "WatopolyException.h"

WatopolyException::WatopolyException(std::string msg): msg{msg} {};

std::string WatopolyException::getMsg() {
  return msg; 
}
