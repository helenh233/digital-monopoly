#ifndef __GOOSE_NESTING_H__
#define __GOOSE_NESTING_H__

#include "Unownable.h"

class GooseNesting : public Unownable {
  public:
    GooseNesting(std::string name, int index);
    void actionOnSquare(Player * player) override;
};

#endif

