#include "Game.h"
#include "Player.h"
#include "OweMoney.h"
#include "AcademicBuilding.h"
#include "Player.h"
#include "Tile.h"
#include "Display.h"
#include "Auction.h"
#include "WatopolyException.h"
#include "SLC.h"
#include "CollectOSAP.h"
#include "AcademicBuilding.h"
#include "Tuition.h"
#include "Residence.h"
#include "NeedlesHall.h"
#include "DCTimsLine.h"
#include "Gym.h"
#include "GooseNesting.h"
#include "GoToTims.h"
#include "CoopFee.h"
#include "Utility.h"

using namespace std;

// helper functions

std::shared_ptr<Ownable> Game::filterProperty(std::string name, std::shared_ptr<Player> player) {
  std::shared_ptr<Tile> propTile = getTileByName(name);

  if (propTile == nullptr) {
    throw WatopolyException{"Please enter a valid property name"};
  }

  std::shared_ptr<Ownable> property = std::dynamic_pointer_cast<Ownable>(propTile);
  
  if (property == nullptr) {
    throw WatopolyException{"Can only trade ownable properties"};
  }
  // check if current player is the owner
  if (player.get() != property->getOwner()) {
    throw WatopolyException{"You do not own this property."};
  }
  
  return property;
}

shared_ptr<Player> Game::curPlayer() {
  return *currentPlayer;
}
string Game::curPlayerName() {
  return (*currentPlayer)->getName();
}

bool Game::lineStatus() {
  return (*currentPlayer)->getIsStuck();
}

bool Game::lineTurns() {
  return (*currentPlayer)->getStuckCount();
}

Game::Game() {

    //   AcademicBuilding(std::string name, std::string monopolyBlock,
	  // int buyCost, int improvementCost, vector<int> tuitionCosts);
    //   Residence(std::string name, int buyCost);
    //    Gym(string name, int buyCost);

  std::vector<int> ALTuition = {2, 10 , 30 , 90  , 160 , 250};
  std::vector<int> MLTuition = {4 , 20 , 60 , 180 , 320 , 450};
  std::vector<int> ECHTuition = {6 , 30 , 90 , 270 , 400 , 550 };
  std::vector<int> HHTuition = {8 , 40 , 100, 300 , 450 , 600};
  std::vector<int> RCHTuition = {10, 50 , 150, 450 , 625 , 750 };
  std::vector<int> CPHTuition = {12, 60 , 180, 500 , 700 , 900};
  std::vector<int> LHITuition = {14, 70 , 200, 550 , 750 , 950};
  std::vector<int> OPTTuition = {16, 80 , 220, 600 , 800 , 1000};
  std::vector<int> EV1Tuition = {18, 90 , 250, 700 , 875 , 1050};
  std::vector<int> EV3Tuition = {20, 100, 300, 750 , 925 , 1100};
  std::vector<int> PHYSTuition = {22, 110, 330, 800 , 975 , 1150};
  std::vector<int> B2Tuition = {24, 120, 360, 850 , 1025, 1200};
  std::vector<int> EITTuition = {26, 130, 390, 900 , 1100, 1275};
  std::vector<int> C2Tuition = {28, 150, 450, 1000, 1200, 1400};
  std::vector<int> MCTuition = {35, 175, 500, 1100, 1300, 1500};
  std::vector<int> DCTuition = {50, 200, 600, 1400, 1700, 2000};

  tiles = {
    std::make_shared<CollectOSAP>("COLLECT_OSAP", 0),
    std::make_shared<AcademicBuilding>("AL", "ARTS1", 1, 40, 50, ALTuition),
    std::make_shared<SLC>("SLC", 2),
    std::make_shared<AcademicBuilding>("ML", "ARTS1",	3, 60, 50, MLTuition),
    std::make_shared<Tuition>("TUITION", 4),
    std::make_shared<Residence>("MKV", 5, 200),
    std::make_shared<AcademicBuilding>("ECH", "ARTS2", 6,	100, 50, ECHTuition),
    std::make_shared<NeedlesHall>("NEEDLES_HALL", 7),
    std::make_shared<AcademicBuilding>("PAS", "ARTS2", 8, 100, 50, ECHTuition),
    std::make_shared<AcademicBuilding>("HH", "ARTS2",	9, 120, 50, HHTuition),
    std::make_shared<DCTimsLine>("DC_TIMS_LINE", 10),
    std::make_shared<AcademicBuilding>("RCH",	"ENG", 11, 140, 100, RCHTuition),
    std::make_shared<Gym>("PAC", 12, 150),
    std::make_shared<AcademicBuilding>("DWE",	"ENG", 13, 140, 100, RCHTuition),
    std::make_shared<AcademicBuilding>("CPH",	"ENG", 14,160, 100, CPHTuition),
    std::make_shared<Residence>("UWP", 15, 200),
    std::make_shared<AcademicBuilding>("LHI",	"HEALTH",	16, 180, 100, LHITuition),
    std::make_shared<SLC>("SLC", 17),
    std::make_shared<AcademicBuilding>("BMH",	"HEALTH", 18,	180, 100, LHITuition),
    std::make_shared<AcademicBuilding>("OPT",	"HEALTH",	19, 200, 100, OPTTuition),
    std::make_shared<GooseNesting>("GOOSE_NESTING", 20),
    std::make_shared<AcademicBuilding>("EV1",	"ENV", 21, 220, 150, EV1Tuition),
    std::make_shared<NeedlesHall>("NEEDLES_HALL", 22),
    std::make_shared<AcademicBuilding>("EV2",	"ENV", 23, 220, 150, EV1Tuition),
    std::make_shared<AcademicBuilding>("EV3",	"ENV", 24, 240, 150, EV3Tuition),
    std::make_shared<Residence>("V1", 25, 200),
    std::make_shared<AcademicBuilding>("PHYS",	"SCI1", 26,	260, 150, PHYSTuition),
    std::make_shared<AcademicBuilding>("B1", "SCI1", 27, 260, 150, PHYSTuition),
    std::make_shared<Gym>("CIF", 28, 150),
    std::make_shared<AcademicBuilding>("B2", "SCI1", 29, 280, 150, B2Tuition),
    std::make_shared<GoToTims>("GO_TO_TIMS", 30),
    std::make_shared<AcademicBuilding>("EIT",	"SCI2",	31, 300, 200, EITTuition),
    std::make_shared<AcademicBuilding>("ESC",	"SCI2",	32, 300, 200, EITTuition),
    std::make_shared<SLC>("SLC", 33),
    std::make_shared<AcademicBuilding>("C2", "SCI2", 34, 320, 200, C2Tuition),
    std::make_shared<Residence>("REV", 35, 200),
    std::make_shared<NeedlesHall>("NEEDLES_HALL", 36),
    std::make_shared<AcademicBuilding>("MC", "MATH", 37, 350, 200, MCTuition),
    std::make_shared<CoopFee>("COOP_FEE", 38),
    std::make_shared<AcademicBuilding>("DC", "MATH", 39, 400, 200, DCTuition)
  };

};

std::shared_ptr<Player> Game::getPlayerByName(std::string name) {
  for (auto it = players.begin(); it < players.end(); it++) {
    if ((*it)->getName() == name)
    {
      return *it;
    }
  }
  return nullptr;
}

std::shared_ptr<Tile> Game::getTileByName(std::string name)
{
  for (auto it = tiles.begin(); it < tiles.end(); it++)
  {
    if ((*it)->getName() == name)
    {
      return *it;
    }
  }
  return nullptr;
};


std::shared_ptr<Player> Game::addPlayer(string playerName, char symbol, int posIndex) {

  std::vector<std::shared_ptr<Tile>>::iterator timsTileIt;

  // in the case where player already has a position
  std::vector<std::shared_ptr<Tile>>::iterator curTile = tiles.begin();
  for (int i = 0; i < posIndex; i++) {
    curTile++;
  }

  // find timsLine
  for (auto it = tiles.begin(); it < tiles.end(); it++) {
    if ((*it)->getName() == "DC_TIMS_LINE") {
      timsTileIt = it;
      break;
    }
  }
  // alspo passes in the tims tile at the
  std::shared_ptr<Player> newPlayer = std::make_shared<Player>(playerName, symbol, curTile, tiles.begin(), tiles.end(), timsTileIt);
  players.push_back(newPlayer);
  return newPlayer;
}

void Game::inTimsLine() {
  (*currentPlayer)->inTimsLine();
}
void Game::roll() { // why isn't this working? 
  if ((*currentPlayer)->getIsStuck()) {
    if ((*currentPlayer)->hasRolled()) {
      throw WatopolyException{"You already rolled. Cannot roll again."};
    }
  } else {
    if ((*currentPlayer)->hasRolled() && doublesCount == 0) {
      throw WatopolyException{"You already rolled. Cannot roll again."};
    }
    Roll rolled = (*currentPlayer)->roll();
    cout << "You rolled a " << rolled.sum << "." << endl;
    
    if (rolled.isDouble) {
      doublesCount++;
      if (doublesCount == 3) {
        cout << "Oops, you rolled doubles 3 times. Time to go to Tims Line." << endl;
        (*currentPlayer)->moveToTimsLine();
        doublesCount == 0;
        return;
      } 
      cout << "You rolled a double! You can roll again." << endl; 
    } else {
      doublesCount = 0; 
    }
    (*currentPlayer)->move(rolled.sum);
    if ((*currentPlayer)->getIsStuck()) {
      doublesCount = 0;
    }
    (*currentPlayer)->setRolled(true);
  }
}

// this function missing a lot
void Game::roll(int die1, int die2) { 
  if ((*currentPlayer)->getIsStuck()) {
    if ((*currentPlayer)->hasRolled()) {
      throw WatopolyException{"You already rolled. Cannot roll again."};
    }
  } else {
    if ((*currentPlayer)->hasRolled() && doublesCount == 0) {
      throw WatopolyException{"You already rolled. Cannot roll again."};
    }

    if (die1 == die2) {
      doublesCount++;
      if (doublesCount == 3) {
        cout << "Oops, you rolled doubles 3 times. Time to go to Tims Line." << endl;
        (*currentPlayer)->moveToTimsLine();
        doublesCount = 0; 
        return;
      }
      cout << "You rolled a double! You can roll again unless you land on 'Go To Tims'." << endl;
    } else {
      doublesCount = 0; // didin't roll double
    }
  }
  (*currentPlayer)->move(die1 + die2);
  if ((*currentPlayer)->getIsStuck()) {
    doublesCount = 0;
  }
  (*currentPlayer)->setRolled(true);
    
}

void Game::next()
{
  (*currentPlayer)->setRolled(false);

  if (currentPlayer == players.end() - 1)
  {
    currentPlayer = players.begin();
  }
  else
  {
    currentPlayer++;
  }
}


void Game::trade(std::string name, std::string givePropertyName, int receiveAmount) {
  std::shared_ptr<Player> otherPlayer = getPlayerByName(name);

  if (otherPlayer == *currentPlayer) {
    throw WatopolyException{"Cannot trade with yourself!"};
  }

  if (otherPlayer == nullptr)
  {
    throw WatopolyException { "The player " + name + " does not exist, please provide a valid player name and try again or enter another command." };
  }

  std::shared_ptr<Ownable> property = filterProperty(givePropertyName, (*currentPlayer)); // std::shared_ptr<T> filterProperty(std::string name, std::shared_ptr<Player> player)

  std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);

  if (acBuilding) {
    
    if (acBuilding->getImprovementLevel() != 0) {
      throw WatopolyException{"Trade rejected. Properties in " + givePropertyName + "'s monopoly block have improvements. Please try again or enter another command."};
    }
    if (acBuilding->getMonopolyBlockImprovement() > 0) {
      throw WatopolyException{"Trade rejected. Properties in " + givePropertyName + "'s monopoly block have improvements. Please try again or enter another command."};
    } 
    
  }

  // may throw exception if otherplayer does not have enough money
  try {
    otherPlayer->withdraw(receiveAmount);
  } catch (WatopolyException e) {
    throw WatopolyException{"The other player does not have enough funds. Please propose a valid trade option. Please try again or enter another command."};
  }
  
  property->setOwner(otherPlayer.get(), false);

  // take away the original property's value from current player's net worht 
  (*currentPlayer)->deposit(receiveAmount);
  (*currentPlayer)->updateTotalWorth((*currentPlayer)->getTotalWorth() - property->getAssetValue());
  (*currentPlayer)->subtractPropBlockCount(BUILDING_TO_BLOCK[property->getName()]);
}


void Game::trade(std::string name, std::string givePropertyName, std::string receivePropertyName) {
  std::shared_ptr<Player> otherPlayer = getPlayerByName(name);

  if (otherPlayer == *currentPlayer) {
    throw WatopolyException{"Cannot trade with yourself!"};
  }

  if (otherPlayer == nullptr)
  {
    throw WatopolyException { "The player " + name + " does not exist, please provide a valid player name and try again or enter another command." };
  }

  std::shared_ptr<Ownable> giveProperty = filterProperty(givePropertyName, *currentPlayer);
  std::shared_ptr<Ownable> receiveProperty = filterProperty(receivePropertyName, otherPlayer);

  std::shared_ptr<AcademicBuilding> acBuilding1 = std::dynamic_pointer_cast<AcademicBuilding>(giveProperty);
  std::shared_ptr<AcademicBuilding> acBuilding2 = std::dynamic_pointer_cast<AcademicBuilding>(receiveProperty);

  if (acBuilding1) {
    if (acBuilding1->getMonopolyBlockImprovement() > 0) {
      throw WatopolyException{"Trade rejected. Properties in " + givePropertyName + "'s monopoly block have improvements. Please try again or enter another command."};
    }
  }

  if (acBuilding2) {
    if (acBuilding2->getMonopolyBlockImprovement() > 0) {
      throw WatopolyException{"Trade rejected. Properties in " + receivePropertyName + "'s monopoly block have improvements. Please try again or enter another command."};
    }
  }

  // assetValues are incremented in setOwner for the new owner by the property's buy cost
  giveProperty->setOwner(otherPlayer.get(), false);
  receiveProperty->setOwner((*currentPlayer).get(), false);

  // take away the original property's value from current player's net worht 
  (*currentPlayer)->updateTotalWorth((*currentPlayer)->getTotalWorth() - giveProperty->getAssetValue());
  (*currentPlayer)->subtractPropBlockCount(BUILDING_TO_BLOCK[giveProperty->getName()]);
  otherPlayer->updateTotalWorth(otherPlayer->getTotalWorth() - receiveProperty->getAssetValue());
  otherPlayer->subtractPropBlockCount(BUILDING_TO_BLOCK[receiveProperty->getName()]);
}

void Game::trade(std::string name, int giveAmount, std::string receivePropertyName) {
  std::shared_ptr<Player> otherPlayer = getPlayerByName(name);

  if (otherPlayer == *currentPlayer) {
    throw WatopolyException{"Cannot trade with yourself!"};
  }

  if (otherPlayer == nullptr)
  {
    throw WatopolyException { "The player " + name + " does not exist, please provide a valid player name and try again or enter another command." };
  }

  std::shared_ptr<Ownable> property = filterProperty(receivePropertyName, otherPlayer);

  std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);

  if (acBuilding) {
    if (acBuilding->getMonopolyBlockImprovement() > 0) {
      throw WatopolyException{"Trade rejected. Properties in " + receivePropertyName + "'s monopoly block have improvements. Please try again or enter another command."};
    }
  }

  // may throw exception if otherplayer does not have enough money
  try {
    (*currentPlayer)->withdraw(giveAmount);
    
   } catch (WatopolyException e) {
    throw WatopolyException{"You do not have enough funds. Please propose a valid trade option. Please try again or enter another command."};
  }
  property->setOwner((*currentPlayer).get(), false);

  // take away the original property's value from current player's net worht 
  otherPlayer->deposit(giveAmount);
  otherPlayer->updateTotalWorth(otherPlayer->getTotalWorth() - property->getAssetValue());
  otherPlayer->subtractPropBlockCount(BUILDING_TO_BLOCK[property->getName()]);
}

void Game::buyImprove(std::string propertyName) {
  std::shared_ptr<Ownable> property = filterProperty(propertyName, *currentPlayer);
  std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);
  if (acBuilding == nullptr) {
    throw WatopolyException{"Cannot buy improvements on non academic buildings"};
  }
  acBuilding->buyImprovement();
}

void Game::sellImprove(std::string propertyName) {
  std::shared_ptr<Ownable> property = filterProperty(propertyName, *currentPlayer);
  std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);
  if (acBuilding == nullptr) {
    throw WatopolyException{"Cannot buy improvements on non academic buildings"};
  }
  acBuilding->sellImprovement();
  
}


void Game::mortgage(std::string propertyName) {
  std::shared_ptr<Ownable> property = filterProperty(propertyName, *currentPlayer);
  property->mortgage();
}

void Game::unmortgage(std::string propertyName) {
	std::shared_ptr<Ownable> property = filterProperty(propertyName, *currentPlayer);
  property->unmortgage();
}

// should only be called when Player is forced to be bankrupt? 

void Game::bankrupt(OweMoney& debt) {

  std::cout << "Please enter an action:" << std::endl;
  std::cout << "'pay': Pay Debt" << std::endl;
  std::cout << "'bankrupt': Declare Bankruptcy" << std::endl;

  while (true) {
    std::string action;
    std::cin >> action;
    if (action == "pay") {
      debt.payDebt();
      if (debt.isPaid()) { break; }
    } else if (action == "bankrupt") {
        // TODO: check if they have enough money?? this will be assumed they dont
        
        // transfer ownership or auction player's propertys
      for (auto tile:tiles) { 
        std::shared_ptr<Ownable> ownable = std::dynamic_pointer_cast<Ownable>(tile);

        if (ownable && ownable->getOwner() == debt.getOwesPlayer()) {
          // transfer ownership
          if (debt.owesAPlayer()) {
            ownable->setOwner(debt.getOwedPlayer(), false);
            // should a player receive a mortgaged building they must immediately pay 10%
            // NOTE: player must have enough money to unmortgage, otherwise causing Game;:bankrupt breaks 
            if (ownable->getIsMortgaged()) {
              debt.getOwedPlayer()->withdraw(ownable->getAssetValue() * 0.1);
              std::cout << debt.getOwedPlayer()->getName() << " received a mortgaged property. " << ownable->getAssetValue() * 0.1 << "$ is paid to the bank." << std::endl;
              std::cout << "Player " <<  debt.getOwedPlayer()->getName() << ", would you like to unmortgage " << ownable->getName() << " ?" << std::endl;
              std::cout << "Enter (Y/N), case sensitive" << std::endl;

              // TODO: handle exception here
              while (true) {
                std::string decision;
                cin >> decision;
                if (decision == "Y") {
                  ownable->unmortgage(true);
                  std::cout << ownable->getName() << " has been unmortgaged" << std::endl;
                  break;
                } else if (decision == "N") {
                  std::cout << ownable->getName() << " remains unmortgaged" << std::endl;
                  break;
                } else {
                  std::cout << "Please enter either (Y/N), case sensitive" << std::endl;
                }
              }
            }
          } else {
            // auction property
            std::shared_ptr<Auction> a = std::make_shared<Auction>(ownable.get());
            startAuction(*a);
          }
        }   
      }

      std::cout << debt.getOwesPlayer()->getName() << " declared bankruptcy. They are removed from the game."<< std::endl;
      std::vector<std::shared_ptr<Player>>::iterator nextPlayerIt = currentPlayer;

      // // prepare to reassign current player 
      if (currentPlayer == players.end() - 1) {
        nextPlayerIt = players.begin();
      }
      // TODO: sort out how this is handled?
      // delete bankrupt player
      players.erase(currentPlayer);

      currentPlayer = nextPlayerIt;
      break;

    } else {
      std::cout << "Please enter a valid command (pay/bankrupt)" << std::endl;
    }
  }

  if (players.size() == 1) {
    throw WatopolyException{"ENDGAME"};
  }
}

void Game::assets(std::shared_ptr<Player> player) {
  cout << "===================================================================================================================================" << endl;
  std::cout << player->getName() << "'s assets:" << std::endl;
  std::cout << "Cash: " << player->getSavings() << std::endl;
  std::cout << "Tim Cups: " << player->getTimsCupCount() << std::endl;
  std::cout << "Properties:" << std::endl;


  for (auto tile: tiles) {

    std::shared_ptr<Ownable> own = std::dynamic_pointer_cast<Ownable>(tile);
    if (own && own->getIsMortgaged() && own->getOwner() == player.get()) {
      std::cout << "(Mortgaged) ";
    }

    std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(tile);
    if (acBuilding && acBuilding->getOwner() == player.get()) {
      std::cout << "Academic Building: " << acBuilding->getName() << ", Improvements: " << acBuilding->getImprovementLevel() << std::endl;
      continue;
    }
    std::shared_ptr<Gym> gym = std::dynamic_pointer_cast<Gym>(tile);
    if (gym && gym->getOwner() == player.get()) {
      std::cout << "Gym: " << gym->getName() << std::endl;
      continue;
    }
    std::shared_ptr<Residence> res = std::dynamic_pointer_cast<Residence>(tile);
    if (res && res->getOwner() == player.get()) {
      std::cout << "Residence: " << res->getName() << std::endl;
    }
  }
}

void Game::assets() {
  std::shared_ptr<Player> player = *currentPlayer;
  std::cout << player->getName() << "'s assets:" << std::endl;
  std::cout << "Cash: " << player->getSavings() << std::endl;
  std::cout << "Tim Cups: " << player->getTimsCupCount() << std::endl;
  std::cout << "Properties:" << std::endl;

  for (auto tile: tiles) {
    std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(tile);
    if (acBuilding && acBuilding->getOwner() == player.get()) {
      std::cout << "Academic Building: " << acBuilding->getName() << ", Improvements: " << acBuilding->getImprovementLevel() << std::endl;
      continue;
    }
    std::shared_ptr<Gym> gym = std::dynamic_pointer_cast<Gym>(tile);
    if (gym && gym->getOwner() == player.get()) {
      std::cout << "Gym: " << gym->getName() << std::endl;
      continue;
    }
    std::shared_ptr<Residence> res = std::dynamic_pointer_cast<Residence>(tile);
    if (res && res->getOwner() == player.get()) {
      std::cout << "Residence: " << res->getName() << std::endl;
    }
  }
}

void Game::all() {
  for (auto player: players) {
    assets(player);
  }
}


void Game::save(std::ofstream& ofs)
{
  ofs << players.size() << std::endl;

  for (auto player : players) // need to check for case of TimsLine
  {
    ofs << player->getName() << " " << player->getPiece() << " " << player->getTimsCupCount() << " " << player->getSavings() << " " << player->getCurTile()->getName() << std::endl;
  }

  for (auto tile : tiles)
  {
    std::shared_ptr<Ownable> ownable = std::dynamic_pointer_cast<Ownable>(tile);
  
    if (ownable)
    {
      ofs << ownable->getName() << " ";
      if (ownable->getOwner()) {
        ofs << ownable->getOwner()->getName() << " ";
      }
      else
      {
        ofs << "BANK" << " ";
      }

      std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(ownable);
      if (acBuilding)
      {
        if (acBuilding->getIsMortgaged())
        {
          ofs << "-1" << std::endl;
        }
        else
        {
          ofs << acBuilding->getImprovementLevel() << std::endl;
        }
      }
      else
      { // Residence or Gym
        ofs << "0" << std::endl;
      }
    }
  }
}

void Game::start() {
	currentPlayer = players.begin();

};

void Game::attachDisplay(shared_ptr<Display> display) {
  for (auto player : players) {
    player->attach(display);
    player->notifyObservers();
  }
  for (auto it = this->tiles.begin(); it != this->tiles.end(); ++it) {
    std::shared_ptr<AcademicBuilding> acBuilding = std::dynamic_pointer_cast<AcademicBuilding>(*it);
    if (acBuilding) {
      acBuilding->attach(display);
      acBuilding->notifyObservers();
    }
  } 
}


// must ensure this is called with more than 2 players!! 
void Game::startAuction(Auction& auction) {
  for (auto player: players) { // check that the player isn't the one who decided not to buy the property
    auction.addParticipant(player.get());
  }

  std::cout << "Auction for " << auction.getPropertyName() << " has started" << std::endl;
  std::cout << "To bid, enter a numerical integer amount." << std::endl;

  // TODO: refactor auctions class to make participants private if time permits
  std::vector<Player*>::iterator it = auction.participants.begin();
  
  // NOTE: for 2 player auctions, if the first player withdraws the auction terminates
  while (auction.participants.size() > 1) {
    std::cout << (*it)->getName() << "'s turn. Please enter a bid amount or 'withdraw' in lower case to leave the auction." << std::endl;

    std::string command;
    bool turnEnded;

    while (true) {
        // NOTE: ERROR HANDLING IS NOT IMPLEMENTED HERE, BE CAREFUL WHEN ENTERING AMOUNTS
        std::cin >> command;
        int bid;
        stringstream ss{command};
        if (command == "withdraw") {
          auction.withdrawParticipant(it);
          break;
        } else if (ss >> bid){
          // only end if bid is successful
          if (auction.bid(*it, bid)) {
            break;
          };
        } else {
          std::cout << "Please enter an integer or 'withdraw' " << std::endl;
        } 
    }

    if (it == auction.participants.end() - 1) {
      it = auction.participants.begin();
    } else {
      ++it;
    }
  }
  auction.end();
};
