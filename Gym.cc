#include "Gym.h"
#include "OweMoney.h"
#include "Player.h"
#include <iostream>

using namespace std;

Gym::Gym(string name, int index, int buyCost): Ownable{name, index, buyCost} {}

void Gym::chargeRent(Player* player) {
  
    Roll roll = player->roll();

    int payment = 0;
    if (owner != nullptr && owner != player) {
      if (owner->getGymCount() == 1) {
        payment = roll.sum* 4;
        
      } else if (owner->getGymCount() == 2) {
        payment = roll.sum * 10;
      }
      
      try {
        player->withdraw(payment); 
      } catch (WatopolyException&) {
        cout << "You owe " << "\"" + owner->getName() + "\"" << " $" + payment << "." << endl;
        cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
        throw OweMoney{player, owner, payment};
      }

      // funds are sufficient
      owner->deposit(payment);
      std::cout << "Paid $" << payment << " to gym's owner: \"" << owner->getName() << "\"" << endl;
    }
    
}

void Gym::setOwner(Player* player, bool load) {
	owner = player;
	owner->updateTotalWorth(owner->getTotalWorth() + buyCost);
  owner->updateGymCount(owner->getGymCount() + 1);
}

void Gym::mortgage() {
  if (!isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already unmortgaged."};
  }
		
	//  60% of the cost of the property
	owner->deposit(buyCost / 2);  // take money from owner

  owner->updateGymCount(owner->getGymCount() - 1); // subtract 1 from gym count
	isMortgaged = true;
}

void Gym::unmortgage(bool bankrupt) {
	if (!isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already unmortgaged."};
  }
		
	try {
		owner->withdraw(bankrupt ? 0.5 * buyCost : 0.6 * buyCost); 
	} catch (WatopolyException&) {
		cout << "You do not have enough funds to unmortgage the property." << endl;
		return; // Exit the function immediately after catching the exception
	}
  owner->updateGymCount(owner->getGymCount() + 1);
	isMortgaged = false;
}


