#include "SLC.h"
#include "Player.h"

#include <iostream>


using namespace std;

SLC::SLC(std::string name, int index): Unownable{name, index} {};

// repeat cycle -> move calls land on Square
// land on square calls action on square
// action on square calls move

void SLC::actionOnSquare(Player * player) {
	int prob = rand() % 24 + 1;
  cout << prob << endl;
	if (prob >= 1 && prob <= 3){
		cout << "You move back three tiles." << endl;
		player->move(-3 + 40);
    
	} else if (prob >= 4 && prob <= 7) {
		cout << "You move back two tiles." << endl;
		player->move(-2 + 40);
    
	} else if (prob >= 8 && prob <= 11){
		//Back 1
		cout << "You move back a tile." << endl;
		player->move(-1 + 40);
    
	} else if (prob >= 12 && prob <= 14){
		//Forward 1
		cout << "You move forward a tile." << endl;
		player->move(1);
    
	} else if (prob >= 15 && prob <= 18) {
		
		cout << "You move forward two tiles." << endl;
		//Forward 2
		player->move(2);    
	} else if (prob >= 19 && prob <= 22) {
		//Forward 3
		cout << "You move forward three tiles." << endl;
		player->move(3);
    
 	} else if (prob == 23){
		//Go to DC Tims Line
		cout << "You move to DC Tims Line." << endl;
		player->moveToTimsLine();
    
    
	} else if (prob == 24){
		//Advance to Collect OSAP
		cout << "You move to Collect OSAP." << endl;
		player->moveToOSAP();
	}
}
