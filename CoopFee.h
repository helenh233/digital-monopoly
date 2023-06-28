#ifndef __COOP_FEE_H__
#define __COOP_FEE_H__

#include "Unownable.h"

class CoopFee: public Unownable {
  public:
    CoopFee(std::string name, int index);
    void actionOnSquare(Player * player) override;
};

#endif

