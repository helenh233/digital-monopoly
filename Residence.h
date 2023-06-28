#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include <memory>

#include "Ownable.h"
#include "WatopolyException.h"
#include <string>

class Residence : public Ownable {
  public: 
  Residence(std::string name, int index, int buyCost);
  
  void chargeRent(Player* player) override; 
  
  void setOwner(Player* player, bool load) override; 
  
  void mortgage() override; 
  
  void unmortgage(bool bankrupt=false) override; 
  
};

#endif
