// During an auction, each player is given the option 
// to raise the current bid or withdraw from the auction. 
// When only one player left in auction, must pay their last bid.

#include <sstream>
#include "Auction.h"
#include "Player.h"
#include "Ownable.h"

using namespace std;

// auction takes in a vector of pointers to the players
Auction::Auction(Ownable* property) : winningAmount{0} , property{property}, winningBidder{nullptr} {}

void Auction::addParticipant(Player* player) {

    // property only has owner during bankruptcy auctions
    if (property->getOwner() != player) {
        participants.push_back(player);
    }
}

std::string Auction::getPropertyName() {
    return property->getName();
}

bool Auction::bid(Player* player, int amount) {

    if (player->getSavings() < amount) {
        std::cout << "You do not have enough savings for this bid. Enter another bid or withdraw";
        return false;
    }   

    if (amount > winningAmount) {
        winningBidder = player;
        winningAmount = amount;
        std::cout << player->getName() << " is now the highest bidder, with bid: " << winningAmount << std::endl;
        return true;
    } else {
        std::cout << "Must enter an amount higher than the current highest bid of " << winningAmount << ". Enter another bid or withdraw" << std::endl;
        return false;
    }
    
}

void Auction::withdrawParticipant(std::vector<Player*>::iterator playerIt) {
    std::cout << (*playerIt)->getName() << " has withdrawn from the auction" << std::endl;
    participants.erase(playerIt);
}


void Auction::end() {

    if (winningBidder) {
        std::cout << "---------The auction for " << property->getName() << " has ended.---------" << std::endl;
        std::cout << winningBidder->getName() << " wins the auction by bidding " <<  winningAmount << std::endl;
        winningBidder->withdraw(winningAmount);
        property->setOwner(winningBidder, false);
    } else {
        // case where 1 player left, other players withdrew but current player hasn't bid
        std::cout << "Would you like to bid or withdraw from the auction? Note you automatically win by placing any bid greater than 0." << std::endl;
        std::cout << "Please enter an integer or 'withdraw'. " << endl;
        std::vector<Player*>::iterator remainingPlayer = participants.begin();

        while (true) {
            // NOTE: ERROR HANDLING IS NOT IMPLEMENTED HERE, BE CAREFUL WHEN ENTERING AMOUNTS
            std::string command;
            std::cin >> command;
            int bid;
            stringstream ss{command};

            if (command == "withdraw") {
                this->withdrawParticipant(remainingPlayer);
                std::cout << "There is no winner to this auction" << std::endl;
                break;
            } else if (ss >> bid) {
                // only end if bid is successful
                if (this->bid(*remainingPlayer, bid)) {
                    std::cout << winningBidder->getName() << " wins the auction by bidding " <<  winningAmount << std::endl;
                    break;
                }
            } else {
                std::cout << "Please enter an integer or 'withdraw' " << std::endl;
            } 
        }

    }
    std::cout << "------------------------------------------------" << std::endl;
};

