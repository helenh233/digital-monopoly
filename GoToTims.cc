#include "GoToTims.h"
#include "Player.h"

GoToTims::GoToTims(std::string name, int index): Unownable{name, index} {}

void GoToTims::actionOnSquare(Player* player) {
    std::cout << "You are sent to the DC Tims line! Please wait in line." << std::endl;
    player->setPlayerStuck();
    player->moveToTimsLine();
}
