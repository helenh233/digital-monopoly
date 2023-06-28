#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>


class Player;
class Tile;
class Ownable;
class AcademicBuilding;
class Display;
class Auction;
class OweMoney;

class Game {

  int doublesCount;
  
  std::vector<std::shared_ptr<Player>> players;
  std::vector<std::shared_ptr<Player>>::iterator currentPlayer;
  std::vector<std::shared_ptr<Tile>> tiles;
  std::shared_ptr<Ownable> filterProperty(std::string name, std::shared_ptr<Player> player);
  public:
    Game();
    void attachDisplay(std::shared_ptr<Display> display);
    
    std::shared_ptr<Player> getPlayerByName(std::string name);
    std::shared_ptr<Tile> getTileByName(std::string name);

    // only use posIndex argument when loading a player from save
    std::shared_ptr<Player> addPlayer(std::string playerName, char symbol, int posIndex = 0);
    
    std::shared_ptr<Player> curPlayer(); 
    
    std::string curPlayerName(); 
    
    bool lineStatus(); 
    bool lineTurns(); 
    
    void inTimsLine();
    
    void roll();
    void roll(int die1, int die2); // override roll for testing mode
    void next();
    // where name is the name of the other player
    void trade(std::string name, std::string givePropertyName, int receiveAmount);
    void trade(std::string name, std::string givePropertyName, std::string receivePropertyName);
    void trade(std::string name, int giveAmount, std::string receivePropertyName);
    void buyImprove(std::string propertyName);
    void sellImprove(std::string propertyName);
    void mortgage(std::string propertyName);
    void unmortgage(std::string propertyName);
    
    void bankrupt(OweMoney& debt);
    void assets(std::shared_ptr<Player> player);
    void assets();
    void all();
    void save(std::ofstream& ofs);
    void start();
    void startAuction(Auction& auction);  
    // don't worry about this for now, will have a seperate auction class
};

#endif
