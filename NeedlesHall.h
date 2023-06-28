#ifndef __NEEDLESHALL_H__
#define __NEEDLESHALL_H__

#include <cstdlib>
#include "Unownable.h"
#include "Player.h"

class NeedlesHall: public Unownable {
    public:
    NeedlesHall(std::string name, int index);
    void actionOnSquare(Player * player) override;

};

#endif

