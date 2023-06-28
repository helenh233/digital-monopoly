#ifndef __BANKRUPT_H__
#define __BANKRUPT_H__

#include "WatopolyException.h"
#include <memory>

class Player;

class OweMoney {
  
    Player* owesPlayer; // needs to pay
    Player* owedPlayer;
    int debtAmount;
    bool debtPaid; 
    bool owePlayerDebt;
    
  public:
    OweMoney(Player* owesPlayer, Player* owedPlayer, int debtAmount);
    OweMoney(Player* owesPlayer, int debtAmount);
    void payDebt();

    // getters
    Player* getOwesPlayer();
    Player* getOwedPlayer();
    bool isPaid();
    bool owesAPlayer();
};

#endif

