#include "Tile.h"
#include "Ownable.h"
#include "Player.h"
#include <iostream>


using namespace std; 

Ownable::Ownable(string name, int index, int buyCost): Tile{name, index}, buyCost{buyCost}, owner{nullptr}, isMortgaged{false} {};

void Ownable::actionOnSquare(Player* player) {
	if (owner == nullptr) {
		std::cout << "Would you like to buy " << name << "? Enter (Y/N): " << endl;
		std::string decision;
		
		// cin.ignore(); 
		// std::getline(std::cin, decision);
		
		while (true) {
			getline(cin, decision);
			if (decision == "Y" || decision == "y") {
				buy(player);
				break;
			} else if (decision == "N" || decision == "n") {
				throw Auction{this};
				break;
			} else {
				std::cout << "Please enter a valid response: Y or N." << std::endl;
			}
		};
	} else if (owner != player) {
		chargeRent(player);
	}
}

void Ownable::buy(Player* player) {
	player->withdraw(buyCost); // withdraw should have an exception
	cout << "Bought \"" + name + "\"!\n" << endl;
	setOwner(player, false); // set property with new owner
}

void Ownable::auctionBuy(Player* player, int purchaseCost) {
	player->withdraw(purchaseCost); // withdraw should have an exception
	cout << "Bought \"" + name + "\"!\n" << endl;
	setOwner(player, false); // set property with new owner
}


bool Ownable::getIsMortgaged() {
	return isMortgaged;
}

void Ownable::setIsMortgaged(bool mortgaged) {
	isMortgaged = mortgaged;
}

Player* Ownable::getOwner() {
	return owner;
};
 
int Ownable::getAssetValue() {
	return buyCost; 
}

void Ownable::setImprovementLevel(int level) { 
  improvementLevel = level;
}
