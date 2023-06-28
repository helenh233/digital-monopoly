#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>
#include <string>
#include <vector>

#include "AbstractSubject.h"
#include "WatopolyException.h"

struct Roll {
int sum;
bool isDouble;
};

struct NameIsAvailable {
  std::string name;
  bool isAvailable;
};

class Tile; 

class Player: public AbstractSubject {
  static int timCupsTotal; 
  // maps symbol: <Name, available>
  // static std::map<char, NameIsAvailable> availablePieces;
  
  std::string playerName; 
  
  char piece;
  int gymCount;
  int resCount;
  int stuckCount; // number of turns stuck in timsline
  int timsCupCount;
  int totalWorth;
  int savings;
  bool isBankrupt;
  bool isStuck; 
  bool rolled;
  std::vector<std::shared_ptr<Tile>>::iterator curTile;
  std::vector<std::shared_ptr<Tile>>::iterator begin;
  std::vector<std::shared_ptr<Tile>>::iterator end;
  std::vector<std::shared_ptr<Tile>>::iterator tims;

  std::map<std::string, int> propBlockCount;


  public:
    void notifyObservers() override;

    Player(std::string playerName, char piece, std::vector<std::shared_ptr<Tile>>::iterator curTile,
    std::vector<std::shared_ptr<Tile>>::iterator begin, std::vector<std::shared_ptr<Tile>>::iterator end, 
    std::vector<std::shared_ptr<Tile>>::iterator tims);

    Roll roll();
    void move(int moveBy);
    void moveToTimsLine();
    void inTimsLine();
    void moveToOSAP();

    // setters
    void setPlayerStuck();  
    void setPlayerUnstuck();
    void updateGymCount(int amount);
    void updateResCount(int amount); 
    void updateStuckCount(int amount);
    void setTimsCups(int amount);    
    void deposit(int amount);
    void withdraw(int amount);
    void addPropBlockCount(std::string block);
    void subtractPropBlockCount(std::string block);
    void updateTotalWorth(int amount);
    void setBankrupt(); 
    void setRolled(bool r);
    bool isPlayerBankrupt(); 

    // getters
    std::string getName();
    
    bool getIsStuck();
    
    char getPiece();
    int getGymCount();
    int getResCount();
    int getStuckCount();
    int getTimsCupCount();
    int getPropertiesBlockCount(std::string block_name);
    int getTotalWorth();
    int getSavings();
    std::shared_ptr<Tile> getCurTile();
    bool hasRolled();

};

#endif
