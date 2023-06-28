#ifndef __AUCTION_H__
#define __AUCTION_H__

#include <iostream>
#include <vector>
#include <memory>
#include <string>


class Ownable;
class Player;

class Auction {
  private:
    int winningAmount;
    Ownable* property;
    Player* winningBidder;
    
  public:
    std::vector<Player*> participants;
    Auction(Ownable* property);
    std::string getPropertyName();
    void addParticipant(Player* player);
    void withdrawParticipant(std::vector<Player*>::iterator playerIt);
    bool bid(Player* player, int amount);
    void end();
};

#endif
