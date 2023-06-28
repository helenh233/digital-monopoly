#include "Residence.h"
#include "Player.h"
#include <iostream>

using namespace std;

Residence::Residence(string name, int index, int buyCost) : Ownable{name, index, buyCost} {}
  
void Residence::chargeRent(Player* player) {
  
  // The Residences, MKV, UWP, V1, and REV, each cost $200. 
  // Rather than paying Tuition visitors will pay Rent to the residence owner. 
  // Rent is calculated based on the number of residences a player owns. 
  // The rent when one residence is owned is $25, two
  // residences $50, three residences $100, and four residences $200.

  int payment = 0;
  if (owner != nullptr && owner != player) {
    if (owner->getResCount() == 1) {
      payment = 25;
    } 
    else if (owner->getResCount() == 2) {
      payment = 50;
    }
    else if (owner->getResCount() == 3) {
      payment = 100;
    }
    else if (owner->getResCount() == 4) {
      payment = 200;
    }

    try {
      player->withdraw(payment); 
      
    } catch (WatopolyException&) {
      cout << "You owe " << "\"" + owner->getName() + "\"" << " $" + payment << "." << endl;
      cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
      throw OweMoney{player, owner, payment};
    }

    owner->deposit(payment);
    std::cout << "Paid $" << payment << " for rent to owner: \"" << owner->getName() << "\"" << std::endl;
  }
}


void Residence::setOwner(Player* player, bool load) {
	owner = player;
	
	owner->updateTotalWorth(owner->getTotalWorth() + buyCost);
  owner->updateResCount(owner->getResCount() + 1);
}

void Residence::mortgage() {
  if (!isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already unmortgaged."};
  }
		
	owner->deposit(buyCost / 2);
  
  owner->updateResCount(owner->getResCount() - 1); // subtract 1 from gym count
	isMortgaged = true;
}

void Residence::unmortgage(bool bankrupt) {
	if (!isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already unmortgaged."};
  }
		
	try {
		owner->withdraw(bankrupt ? 0.5 * buyCost : 0.6 * buyCost); 
		
	} catch (WatopolyException&) {
		cout << "You do not have enough funds to unmortgage the property." << endl;
		return; // Exit the function immediately after catching the exception
	}
  
  owner->updateResCount(owner->getResCount() + 1);
	isMortgaged = false;
}
