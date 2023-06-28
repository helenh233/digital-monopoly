#ifndef __TILE_H__
#define __TILE_H__

#include <memory> // for share pointers
#include <string>

#include "WatopolyException.h"
#include "Auction.h"
#include "OweMoney.h"

class Player;// class Player forward declaration

class Tile {
  protected: // sign to use for subclasses 
    std::string name;
    int index;
    
  public:
    Tile(std::string name, int index); // constructor
    void landOnSquare(Player* player);
    virtual void actionOnSquare(Player* player);
    std::string getName();
    int getIndex();
};

#endif

