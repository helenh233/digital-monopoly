#ifndef __TUITION_H__
#define __TUITION_H__

#include "Unownable.h"
#include "Player.h"
#include "WatopolyException.h"

class Tuition: public Unownable {
  public:
    Tuition(std::string name, int index);
    void actionOnSquare(Player * player) override;
    void payAmount(Player* player); 
    void payPercent(Player* player);
    
};


#endif
