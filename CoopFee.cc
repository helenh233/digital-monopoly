#include "CoopFee.h"
#include "Player.h"

#include <iostream>

using namespace std;

CoopFee::CoopFee(std::string name, int index) : Unownable{name, index} {};

void CoopFee::actionOnSquare(Player* player) {
    try {
        player->withdraw(150);
        
    } catch (WatopolyException&) {
        cout << "You do not have enough money to pay the coop fee!" << endl;
        cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
        // OweMoney debt = OweMoney(player, 150); 
        return;
    }
    cout << "You paid $150 for coop!" << endl;
}

