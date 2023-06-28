#include <sstream>
#include "DCTimsLine.h"
#include "Player.h"
#include <iostream>
#include <string>
#include "OweMoney.h"

// logic for DC need to clarify, 
// does the player get roll again immediately after exiting Jail? 
using namespace std;

DCTimsLine::DCTimsLine(std::string name, int index) : Unownable{name, index} {};

void DCTimsLine::useTimsCup(Player* player) {
    int timsCups = player->getTimsCupCount();
    
    cout << "You used your tims cup. Time to leave the line." << endl;
    player->setTimsCups(timsCups - 1);
    player->setPlayerUnstuck();
}

// assuming paying doesn't allow you to roll again
void DCTimsLine::payTimsLine(Player* player) {
    if (player->getStuckCount() == 3) { 
        try { 
          player->withdraw(50); 
          cout << "You paid $50. Time to leave the line." << endl;
        }     // player cannot pay
        catch (WatopolyException&) {
            cout << "You do not have enough money to pay the fee." << endl;
            if (player->getTimsCupCount() > 0) {
                cout << "You must use Tims cup since you have one." << endl;
            }
            else {
                throw OweMoney{player, 50};
            }
        }
    }
    // code will not run if exception is thrown 
    player->withdraw(50);
    player->setPlayerUnstuck();
}

void DCTimsLine::rollTimsLine(Player* player) {
    if (player->getStuckCount() == 3) {
        cout << "You must leave Tim's line this turn by paying or using Tims cup." << endl;
            
            if (player->getTimsCupCount() > 0) {
                std::cout << "Please select your method of leaving the line. Enter (1/2): "<< endl;
                std::string decision;
                
                // cin.ignore(); 
                
                while (true) {
                    getline(cin, decision);
                    if (decision == "1") {
                        useTimsCup(player);
                        break;
                    } else if (decision == "2") {
                        payTimsLine(player);
                        break; 
                    } else {
                        cout << "Please enter a valid response: 1 or 2." << std::endl;
                    }
                };
            } else {
                cout << "Since you do not have a tims cup. You must pay the fee." << endl;
                payTimsLine(player);
            }
        } else {
            Roll rolled = player->roll(); 
            if (rolled.isDouble) { 
                cout << "You rolled doubles! Time to leave the line. You are moved by your roll " + to_string(rolled.sum) + "." << endl;
                
                player->move(rolled.sum);
                player->setPlayerUnstuck();
            } else {
                cout << "You did not roll doubles. You continue to stay in the line." << endl;
                player->updateStuckCount(player->getStuckCount() + 1);
            }
        }

}

void DCTimsLine::actionOnSquare(Player* player) {
    if (player->getIsStuck()) {
        cout << "Your options to get out are: " << endl;
        cout << "1. Try to roll doubles" << endl; 
        cout << "2. Use tims cup" << endl;
        cout << "3. Pay $50 to leave" << endl;
        
        cout << endl;
        cout << "Please enter your option (1/2/3): ";
        
        string keyword;
        
        while (true) {
			getline(cin, keyword);
			if (keyword == "1") {
                rollTimsLine(player);
                break;
            } else if (keyword == "2") {
                if (player->getTimsCupCount() <= 0) {
                    cout << "You do not have a tims cup. Please enter a valid option (1/3): " << endl;
                    continue;
                }
                useTimsCup(player);
                break;
            } else if (keyword == "3") {
                payTimsLine(player);
                break;
            } else {
                cout << "Invalid input. Please enter a valid option (1/2/3): " << endl;
            }
	
		};
    }
}

