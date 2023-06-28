#ifndef __GO_TO_TIMS_H__
#define __GO_TO_TIMS_H__

#include "Unownable.h"


class GoToTims : public Unownable {
  public:
    GoToTims(std::string name, int index);
    void actionOnSquare(Player * player) override;
};

#endif

