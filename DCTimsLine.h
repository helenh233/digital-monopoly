
#ifndef __DCTIMSLINE_H__
#define __DCTIMSLINE_H__

#include "Unownable.h"
#include "WatopolyException.h"

class DCTimsLine : public Unownable {
  
  public:
    DCTimsLine(std::string name, int index);
    
    void actionOnSquare(Player* player) override;

    void useTimsCup(Player* player);
    void payTimsLine(Player* player);
    void rollTimsLine(Player* player);
    
    std::string getMsg(Player* player); 
    
    
};

#endif

