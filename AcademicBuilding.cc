#include "Player.h"
#include "AcademicBuilding.h"
#include "Utility.h"

#include <map>
#include <iostream>

using namespace std; 

std::map<std::string, int> AcademicBuilding::monopolyBlockImprovement = {
		{"Arts1", 0}, {"Arts2", 0}, {"Eng", 0}, {"Health", 0},
		{"Env", 0}, {"Sci1", 0}, {"Sci2", 0}, {"Math", 0}
}; 

// constructor
AcademicBuilding::AcademicBuilding(string name, string monopolyBlock, int index,
  int buyCost, int improvementCost, vector<int> tuitionCosts) :
  Ownable{name, index, buyCost}, improvementCost{improvementCost}, tuitionCosts{tuitionCosts}, monopolyBlock{monopolyBlock} {}
  
int AcademicBuilding::getAssetValue() {
	return buyCost + improvementLevel * improvementCost; 
}

int AcademicBuilding::getMonopolyBlockImprovement() {
	// building to block is from uilties 
	// maps building to corresponding monopoly block
  return monopolyBlockImprovement[monopolyBlock];
}

void AcademicBuilding::setOwner(Player* player, bool load) {
	if (load == false) {
			owner = player;

	// remove improvement levels in the event of transferring properties in bankruptcy
			// monopolyBlockImprovement[monopolyBlock] -= improvementLevel;
			// improvementLevel = 0; 

			owner->updateTotalWorth(owner->getTotalWorth() + buyCost);

			owner->addPropBlockCount(BUILDING_TO_BLOCK[name]); 
			// owner->addPropBlockCount(this->monopolyBlock); --> for some reason this doesn't work? 
			if (owner->getPropertiesBlockCount(BUILDING_TO_BLOCK[name]) == BLOCK_PROP_COUNT[BUILDING_TO_BLOCK[name]]) {
			//if (owner->getPropertiesBlockCount(this->monopolyBlock) == BLOCK_PROP_COUNT[this->monopolyBlock]) {
				cout << "Congratulations! You have a monopoly, and can start building improvements on the properties in the block." << endl;
			}
		
	} else {
			owner = player;

			owner->updateTotalWorth(owner->getTotalWorth() + buyCost);

			owner->addPropBlockCount(BUILDING_TO_BLOCK[name]); 
			// owner->addPropBlockCount(this->monopolyBlock); --> for some reason this doesn't work? 
			if (owner->getPropertiesBlockCount(BUILDING_TO_BLOCK[name]) == BLOCK_PROP_COUNT[BUILDING_TO_BLOCK[name]]) {
			//if (owner->getPropertiesBlockCount(this->monopolyBlock) == BLOCK_PROP_COUNT[this->monopolyBlock]) {
				cout << "Congratulations! You have a monopoly, and can start building improvements on the properties in the block." << endl;
			}
	}
}

// Note: Improvements can only be purchased when there's a monopoly
void AcademicBuilding::chargeRent(Player* player) {

  int payment = 0;
  if (owner != nullptr && owner != player) {
		// check if theres a monopoly 
    if (owner->getPropertiesBlockCount(this->monopolyBlock) == BLOCK_PROP_COUNT[this->monopolyBlock]) {
			// means there's a monopoly
      if (improvementLevel == 0) {
        // has monopoly but no improvements
        payment = tuitionCosts[0] * 2;
      } else {
        // has monopoly and improvements
        payment = tuitionCosts[improvementLevel];
      }
    } else {
      // if no monopoly, just pay regular rent 
      payment = tuitionCosts[0]; 
    }

		try { 
    	player->withdraw(payment);
			std::cout << "You landed on " << owner->getName() << "'s property. " << std::endl;
  	} catch (WatopolyException&) { 
			std::cout << "You owe " << "\"" + owner->getName() + "\"" << " $" << payment << "." << endl;
			std::cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
			throw OweMoney(player, owner, payment);
		}
		owner->deposit(payment);
  }
}

void AcademicBuilding::mortgage() {
		// can't mortgage if already
	if (isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already mortgaged."};
  }
		
	if (improvementLevel >= 1) {
		throw WatopolyException{"Can't mortgage an academic building with improvements"};
	}
	owner->deposit(buyCost / 2); 
	
	owner->subtractPropBlockCount(this->monopolyBlock); // add money to owner
	isMortgaged = true;
}

void AcademicBuilding::unmortgage(bool bankrupt) {
	if (!isMortgaged) {
    throw WatopolyException{"\"" + name + "\" is already unmortgaged."};
  }
	//  60% of the cost of the property
	try {
		owner->withdraw(0.6 * buyCost); 
		
	} catch (WatopolyException&) {
		cout << "You do not have enough funds to unmortgage the property." << endl;
		return; // Exit the function immediately after catching the exception
	}
	owner->addPropBlockCount(this->monopolyBlock); 
	isMortgaged = false;
}

void AcademicBuilding::buyImprovement() {
	if (owner == nullptr || owner->getPropertiesBlockCount(this->monopolyBlock) <  BLOCK_PROP_COUNT[this->monopolyBlock]) {
    throw WatopolyException{"Cannot buy improvements, player needs a monopoly first"};
  }
	else if (improvementLevel >= 5) {
    	throw WatopolyException{"\"" + name + "\" is at max improvement level: 5"};
  }

	try {
		owner->withdraw(improvementCost); 
	}
	catch (WatopolyException&) { 
		cout << "You do not have enough funds to buy improvements." << endl;
	}
	improvementLevel += 1;
  monopolyBlockImprovement[this->monopolyBlock] += 1;
  
	this->notifyObservers();
	cout << "Bought improvement on \"" + name + "\"." << endl;
}

void AcademicBuilding::sellImprovement() {
	if (improvementLevel < 1) {
		throw WatopolyException{"\"" + name + "\" has no improvements."};
  }
	improvementLevel -= 1;
	monopolyBlockImprovement[this->monopolyBlock] -= 1; // subtract from the overall num improvements in the monopoly block
	owner->deposit(improvementCost / 2); 
	
	this->notifyObservers();
	cout << "Sold improvement on \"" + name + "\"." << endl;
}

int AcademicBuilding::getImprovementLevel() { 
  return improvementLevel; 
}

int AcademicBuilding::getIndex() { 
  return index;
}

void AcademicBuilding::notifyObservers() {
  for (auto &ob : observers) {
      ob->notify(this);
	}
}

void AcademicBuilding::setImprovementLevel(int level) {
	improvementLevel = level;
	this->notifyObservers();
}
