#ifndef __OSAP_H__
#define __OSAP_H__
#include "Unownable.h"

class Player;

class CollectOSAP: public Unownable {
  public:
    CollectOSAP(std::string name, int index);
    void actionOnSquare(Player * player) override;
};

#endif

