#include <iostream>
#include "OweMoney.h"
#include "Player.h"
#include "WatopolyException.h"

using namespace std; 

OweMoney::OweMoney(Player* owesPlayer, Player* owedPlayer, int debtAmount) :
    owesPlayer{owesPlayer}, owedPlayer{owedPlayer}, debtAmount{debtAmount}, debtPaid{false}, owePlayerDebt{true} {}

// if no player oweto passedin, it means player owes bank 

OweMoney::OweMoney(Player* owesPlayer, int debtAmount) :
    owesPlayer{owesPlayer}, owedPlayer{nullptr}, debtAmount{debtAmount}, debtPaid(false), owePlayerDebt{false} {}

// OweMoney::OweMoney() : owedFrom{nullptr}, owedTo{nullptr}, owed{0} {}



void OweMoney::payDebt() {
    try {
        owesPlayer->withdraw(debtAmount); // throw exception if fails 
    } catch (WatopolyException e) {
        cout << "Funds are not enough to pay off debt. Please move your assets or declare bankruptcy." << endl;
        return;
    }

    if (owedPlayer != nullptr) { // means that there's a player that is owed instead of bank
      owedPlayer->deposit(debtAmount); // else add cash to bank
      cout << "Payed " << debtAmount << " to " << owedPlayer->getName() << endl;
    } else {
        cout << "Payed " << debtAmount << " to the bank." << endl;
    }

    debtPaid = true;
}


bool OweMoney::isPaid() {
    return debtPaid;
}

bool OweMoney::owesAPlayer() {
    return owePlayerDebt;
}

Player* OweMoney::getOwesPlayer() {
    return owesPlayer;
}

Player * OweMoney::getOwedPlayer() {
    return owedPlayer;
}
