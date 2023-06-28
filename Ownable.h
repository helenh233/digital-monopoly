#ifndef __OWNABLE_H__
#define __OWNABLE_H__

#include <iostream>
#include "Tile.h"


class Player;

class Ownable : public Tile {
  protected:
    Player* owner;
    int buyCost;
    int improvementLevel = 0;
    bool isMortgaged;

  public:
    // constructor
    Ownable(std::string name, int index, int buyCost);
  
    void buy(Player* player);
    
    void auctionBuy(Player* player, int purchaseCost);
    
    virtual void setOwner(Player* player, bool load) = 0;
    
    virtual void mortgage() = 0;
    virtual void unmortgage(bool bankrupt = false) = 0;
    
    bool getIsMortgaged();
    void setIsMortgaged(bool mortgaged);
    
    Player* getOwner();
    
    virtual void setImprovementLevel(int level);
    virtual int getAssetValue(); // virtual methods to be overriden
    virtual void chargeRent(Player* player) = 0;
    void actionOnSquare(Player * player);
};

#endif
