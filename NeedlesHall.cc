#include "NeedlesHall.h"
#include "Utility.h"

using namespace std;

NeedlesHall::NeedlesHall(std::string name, int index): Unownable{name, index} {};

void NeedlesHall::actionOnSquare(Player * player) {
  
	int prob = genRandom(0, 18);
	int timCups = player->getTimsCupCount();
  
  int rollUp = rand() % 100;
	
  // The amount of money gained or lost is determined by the following table:
  // -200 : 1/18 
  // -100 : 2/18
  // -50 : 3/18
  // 25 : 6/18
  // 50 : 3/18
  // 100 : 2/18
  // 200 : 1/18
  
	if (rollUp == 1 && timCups < 4) {
		player->setTimsCups(timCups + 1);
		cout << "Congratulations! You just won a Roll the Rims Cup." << endl;
	}

			// std::cout << "You owe the bank money." << endl;
      // std::cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
      // throw OweMoney{player, 100};
	if (prob == 0) {
		cout << "Oh no! You lose $200 at Needles Hall." << endl;
		try { 
    	player->withdraw(200); 
  	} catch (WatopolyException&) { 
			
			std::cout << "You owe the BANK $200." << endl;
			std::cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
			
			throw OweMoney(player, 200);
		}
	} else if (prob == 1 || prob == 2) {
		
		cout << "Oh no! You lose $100 at Needles Hall." << endl;
		try { 
    	player->withdraw(100); 
  	} catch (WatopolyException&) { 
			
			std::cout << "You owe the BANK $100." << endl;
			std::cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
			
			throw OweMoney(player, 100);
		}
    
	} else if (prob >= 3 && prob <= 5) {
		cout << "Oh no! You lose $50 at Needles Hall." << endl;
		try { 
    	player->withdraw(50); 
			
  	} catch (WatopolyException&) { 
			
			std::cout << "You owe the BANK $50." << endl;
			std::cout << "Find a way to pay by moving your assets or declare bankruptcy." << endl;
			
			throw OweMoney(player, 50);
		}
    
	} else if (prob >= 6 && prob <= 11) {
		player->deposit(25);

		cout << "You win $25 at Needles Hall!" << endl;
    
	} else if (prob >= 12 && prob <= 14) {
		player->deposit(50);
    
		cout << "You win $50 at Needles Hall!" << endl;
    
	} else if (prob == 15 || prob == 16) {
		player->deposit(100);
		cout << "You win $100 at Needles Hall!" << endl;
    
	} else if (prob == 17) {
		player->deposit(200);
		cout << "You win $200 at Needles Hall!" << endl;
	}

}

