#include "Player.h"
#include "Tile.h"
#include "Utility.h"
#include "OweMoney.h"
#include <algorithm>
#include "AbstractObserver.h"
// static fields, since they need to be declared

using namespace std;

int Player::timCupsTotal = 4;

// std::map<char, NameIsAvailable> Player::availablePieces = {
//   {'G', NameIsAvailable{"Goose", true}},
//   {'B', NameIsAvailable{"GRT Bus", true}},
//   {'D', NameIsAvailable{"Tim Hortons Doughnut", true}},
//   {'P', NameIsAvailable{"Professor", true}}, 
//   {'S', NameIsAvailable{"Student", true}}, 
//   {'M', NameIsAvailable{"Money", true}},
//   {'L', NameIsAvailable{"Laptop", true}},
//   {'T', NameIsAvailable{"Pink tie", true}}
// };

Player::Player(std::string playerName, char piece, std::vector<std::shared_ptr<Tile>>::iterator curTile,
    std::vector<std::shared_ptr<Tile>>::iterator begin, std::vector<std::shared_ptr<Tile>>::iterator end, 
    std::vector<std::shared_ptr<Tile>>::iterator tims) 
    : playerName{playerName}, piece{piece}, curTile{curTile}, begin{begin}, end{end}, tims{tims}, gymCount{0},
    resCount{0}, stuckCount{0}, timsCupCount{0}, totalWorth{1500}, savings{1500}, isBankrupt{false}, isStuck{false}, rolled{false} 
  
    {
      propBlockCount = {{"Arts1", 0}, {"Arts2", 0}, {"Eng", 0}, {"Health", 0},
	    {"Env", 0}, {"Sci1", 0}, {"Sci2", 0}, {"Math", 0}};
};

bool Player::getIsStuck() {
  return isStuck;
};

void Player::setPlayerStuck() {
  isStuck = true;
  stuckCount = 0;
};

void Player::setPlayerUnstuck() {
  isStuck = false;
  stuckCount = 0;
};

Roll Player::roll() {
  int roll1 = genRandom(1, 6);
  int roll2 = genRandom(1, 6);
  rolled = true;
  return Roll{roll1 + roll2, roll1 == roll2};
};


void Player::move(int moveBy) {
  
  if (moveBy < 0) {
    for (int i = -1 * moveBy; i > 0; i--) {
      if (curTile == begin) {
        curTile = end - 1;
      } else {
        curTile--;
      }
    }
  } else {
    for (int i = 0; i < moveBy; i++) {
      if (curTile == end - 1) {
        // player passes OSAP
        curTile = begin;
        deposit(200);
      } else {
        curTile++;
      }
    }
  }
  (*curTile)->landOnSquare(this);
  notifyObservers();
}

// void Player::moveFromSLC(int moveBy) {
//   for (int i = 0; i < moveBy; i++) {
//     if (curTile == end - 1) {
//       // player passes OSAP
//       curTile = begin;
//       deposit(200);
//     } else {
//       curTile++;
//     }
//   }
//   (*curTile)->landOnSquare(this);
//   notifyObservers();
// 

void Player::moveToTimsLine() {
  curTile = tims;

  (*curTile)->landOnSquare(this);
  rolled = true;
  
  notifyObservers();
}

void Player::inTimsLine() {
  (*curTile)->actionOnSquare(this);
  rolled = true;

  notifyObservers();
}

void Player::moveToOSAP() {
  curTile = begin;
}

void Player::updateGymCount(int amount) { gymCount = amount; }

void Player::updateResCount(int amount) { resCount = amount; }

void Player::updateStuckCount(int amount) { 
  stuckCount = amount; 
}

void Player::setTimsCups(int amount) { timsCupCount = amount; }

void Player::deposit(int amount) { 
  savings += amount;
  totalWorth += amount;
}

void Player::withdraw(int amount) { 
  
  if (savings < amount) {
    throw WatopolyException{"You do not have enough money."};
  }
  savings -= amount;
  totalWorth -= amount;
}

void Player::addPropBlockCount(std::string block) {
  ++propBlockCount[block];
}

void Player::subtractPropBlockCount(std::string block) {
  --propBlockCount[block];
}

void Player::updateTotalWorth(int amount) { totalWorth = amount; }

void Player::setBankrupt() {
  // game handles the actual part of removing player.
  isBankrupt = true;
} // not sure how to handle bankruptcy


void Player::setRolled(bool r) {
  rolled = r;
}
bool Player::isPlayerBankrupt() {
  return isBankrupt;
} 


std::string Player::getName() {
  return playerName; 
  // return availablePieces[piece].name;
}

char Player::getPiece() {
  return piece;
}

int Player::getGymCount() {
  return gymCount;
}

int Player::getResCount() {
  return resCount;
}

int Player::getStuckCount() {
  return stuckCount;
}

int Player::getTimsCupCount() {
  return timsCupCount;
}

int Player::getPropertiesBlockCount(std::string block) {
  return propBlockCount[block];
}

int Player::getTotalWorth() {
  return totalWorth;
}

int Player::getSavings() {
  return savings;
}

std::shared_ptr<Tile> Player::getCurTile() { return *curTile; }


bool Player::hasRolled() { return rolled; };

void Player::notifyObservers() {
  for (auto ob : observers)
      ob->notify(this);
}
