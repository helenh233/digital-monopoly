#include "CollectOSAP.h"
#include "Player.h"

CollectOSAP::CollectOSAP(std::string name, int index) : Unownable{name, index} {};

void CollectOSAP::actionOnSquare(Player* player) {
    player->deposit(200);
    std::cout << "You get $200 for landing/passing OSAP!" << std::endl;
}
