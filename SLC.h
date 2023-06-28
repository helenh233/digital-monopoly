#ifndef __SLC_H__
#define __SLC_H__

#include "Unownable.h"

class Player;

class SLC : public Unownable {
  public:
    SLC(std::string name, int index);
    void actionOnSquare(Player * player) override;
};

#endif

