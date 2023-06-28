#ifndef __GYM_H__
#define __GYM_H__

#include "Ownable.h"
#include "WatopolyException.h"

class Player;

class Gym: public Ownable {
  public:
    Gym(std::string name, int index, int buyCost);
    void chargeRent(Player* player) override;
    
    void setOwner(Player* player, bool load) override; 
  
    void mortgage() override; 
    
    void unmortgage(bool bankrupt=false) override; 
};

#endif

