#include "GooseNesting.h"
#include "Player.h"
#include <iostream> 

using namespace std;

GooseNesting::GooseNesting(std::string name, int index) : Unownable{name, index} {};

void GooseNesting::actionOnSquare(Player * player) {
    cout << "You are suddenly swarmed by a flock of geese!" << endl;
    
}

