#ifndef __UNOWNABLE_H__
#define __UNOWNABLE_H__

#include "Tile.h"
#include <string>
#include <memory>

class Player;

class Unownable : public Tile {
  
  public: 
    Unownable(std::string name, int index);
    // virtual void actionOnSquare(Player * player);
    // virtual ~Unownable() = 0;
  	
};

#endif
