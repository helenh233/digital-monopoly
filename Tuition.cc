#include "Tuition.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Tuition::Tuition(std::string name, int index) : Unownable{name, index} {};

void Tuition::actionOnSquare(Player * player){
    // if (!tuitionPaid) {
    //     throw WatopolyException{"You must pay tuition."};
    // }
    string decision; 
    
    cout << "Please select your method of tuition payment. Enter (1/2):" << endl;
    cout << "1. Pay $300" << endl;
    cout << "2. Pay 10% of your net worth" << endl;
    
	while (true) {
        cin >> decision;
        if (decision == "1") {
            payAmount(player); 
            cout << "You paid the BANK $300." << endl; 
            break;
        } else if (decision == "2") {
            payPercent(player);
            cout << "You paid the BANK 10% of your net worth." << endl; 
            break;
        } else {
            cout << "Please enter a valid response: 1 or 2" << endl;
        } 
    };
};

void Tuition::payAmount(Player* player) {
    try {
        player->withdraw(300);
        
    } catch (WatopolyException e) {
        cout << "You owe the BANK $300." << endl;
        cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
        throw OweMoney{player, 300};
    }
}
void Tuition::payPercent(Player* player) {
    
    try {
        player->withdraw(player->getTotalWorth() / 10);
    } catch (WatopolyException e) {
        cout << "You owe the BANK $" << player->getTotalWorth() / 10 << "." << endl;
        cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
        throw OweMoney{player, player->getTotalWorth() / 10};
    }
};


