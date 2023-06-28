#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <stdexcept>

#include "AbstractObserver.h"
#include "Controller.h"

using namespace std;

// Colour Constants
int GLOBAL_COLOUR = 0;

const string ANSI_START{"\033["};
const string START_COLOUR_PREFIX{"1;"};
const string START_COLOUR_SUFFIX{"m"};
const string STOP_COLOUR{"\033[0m"};
// the decimal code for escape character is 27
const char esc_char = 27;

const unsigned int COLOUR_IGNORE{0};
const unsigned int COLOUR_BLACK{30};
const unsigned int COLOUR_RED{31};
const unsigned int COLOUR_GREEN{32};
const unsigned int COLOUR_YELLOW{33};
const unsigned int COLOUR_BLUE{34};
const unsigned int COLOUR_MAGENTA{35};
const unsigned int COLOUR_CYAN{36};
const unsigned int COLOUR_WHITE{37};

Controller::Controller(std::shared_ptr<Game> game, std::shared_ptr<Display> display, bool testingMode) : game{game}, display{display}, testingMode{testingMode} {};

void Controller::start() {
  cout << endl;
  cout << ANSI_START << START_COLOUR_PREFIX << COLOUR_GREEN << START_COLOUR_SUFFIX << esc_char << "[1m";
  cout << "===================================================================================================================================" << endl;
  cout << endl;
  cout << "██╗    ██╗ █████╗ ████████╗ ██████╗ ██████╗  ██████╗ ██╗  ██╗   ██╗" << endl;
  cout << "██║    ██║██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗██╔═══██╗██║  ╚██╗ ██╔╝" << endl;
  cout << "██║ █╗ ██║███████║   ██║   ██║   ██║██████╔╝██║   ██║██║   ╚████╔╝" << endl;
  cout << "██║███╗██║██╔══██║   ██║   ██║   ██║██╔═══╝ ██║   ██║██║    ╚██╔╝" << endl;
  cout << "╚███╔███╔╝██║  ██║   ██║   ╚██████╔╝██║     ╚██████╔╝███████╗██║" << endl;
  cout << endl;
  cout << "===================================================================================================================================" << endl;
  cout << "Welcome, intrepid players, to the exhilarating world of Watopoly!" << endl;
  cout << "As you step into the vibrant Waterloo campus, you are about to" << endl;
  cout << "embark on a thrilling adventure where strategy, cunning, and a" << endl;
  cout << "little bit of luck will determine your fate. I wish you all the best." << endl;
  cout << endl;
  cout << "- Sincerely quack truly, Mr. Goose" << endl;
  cout << endl;
  cout << "                                  ___" << endl;
  cout << "                               ,-''   `." << endl;
  cout << "                           ,'  _   e )`-._" << endl;
  cout << "                            /  ,' `-._<.===-'" << endl;
  cout << "                           /  /" << endl;
  cout << "                          /  ;" << endl;
  cout << "              _          /   ;" << endl;
  cout << " (`._    _.-'' ''--..__,'    |" << endl;
  cout << " <_  `-''                     \\" << endl;
  cout << "  <`-         MR.GOOSE          :" << endl;
  cout << "   (__   <__.                  ;" << endl;
  cout << "     `-.   '-.__.      _.'    /" << endl;
  cout << "        \\      `-.__,-'    _,'" << endl;
  cout << "         `._    ,    /__,-'" << endl;
  cout << "           ''._\\__,'< <____" << endl;
  cout << "                 | |  `----.`." << endl;
  cout << "                 | |        \\ `." << endl;
  cout << "                 ; |___      \\-``" << endl;
  cout << "                 \\   --<" << endl;
  cout << "                  `.`.<" << endl;
  cout << "                    `-'" << endl;

  cout << "===================================================================================================================================" << endl;
  cout << esc_char << "[0m" << STOP_COLOUR << endl;
  
  cout << "Would you like to choose a colour theme for your game? (Beware of choosing a blinding colour at your own risk!)" << endl;
  cout << "Enter (Y/N): ";
  
  char colourTheme; 

  while (true) {
    cin >> colourTheme;
    if (colourTheme == 'Y') {
      cout << endl;
      cout << "Please select one of the following colour themes: " << endl; 
      cout << "1. Default" << endl;
      cout << "2. Black" << endl;
      cout << "3. Red" << endl;
      cout << "4. Green" << endl;
      cout << "5. Yellow" << endl;
      cout << "6. Blue" << endl;
      cout << "7. Magenta" << endl;
      cout << "8. Cyan" << endl;
      cout << "9. White" << endl;
      cout << endl;
      cout << "Enter the digit to select your colour: " << endl;
      cin >> colourTheme;
      
      // please complete the rest if statements
      if (colourTheme == '1') {
        GLOBAL_COLOUR = COLOUR_IGNORE;
        break; 
      } else if (colourTheme == '2') {
        GLOBAL_COLOUR = COLOUR_BLACK;
        break; 
      } else if (colourTheme == '3') {
        GLOBAL_COLOUR = COLOUR_RED;
        break; 
      } else if (colourTheme == '4') {
        GLOBAL_COLOUR = COLOUR_GREEN;
        break; 
      } else if (colourTheme == '5') {
        GLOBAL_COLOUR = COLOUR_YELLOW;
        break; 
      } else if (colourTheme == '6') {
        GLOBAL_COLOUR = COLOUR_BLUE;
        break; 
      } else if (colourTheme == '7') {
        GLOBAL_COLOUR = COLOUR_MAGENTA;
        break; 
      } else if (colourTheme == '8') {
        GLOBAL_COLOUR = COLOUR_CYAN;
        break; 
      } else if (colourTheme == '9') {
        GLOBAL_COLOUR = COLOUR_WHITE;
        break; 
      } else {
        cout << "Please enter a valid input (1-9): " << endl;
      }
    } else if (colourTheme == 'N') {
      break;
    } else {
      cout << endl;
      cout << "Please enter a valid input (Y/N): " << endl;
    }
  }

  cout << endl;
  cout << "How many players are playing?" << endl;
  size_t numPlayers = 0;

  while (!(2 <= numPlayers && numPlayers <= 8)) {
    cout << "Please enter a number between 2-8: " << endl;
    cin >> numPlayers;

    if (cin.fail()) {
      cin.clear();
      cin.ignore();
    }
  }

  // Available pieces
  bool G = true;
  bool B = true;
  bool D = true;
  bool P = true;
  bool S = true;
  bool M = true;  // $
  bool L = true;
  bool T = true;

  // Each player chooses their piece
  for (size_t i = 1; i <= numPlayers; ++i) {
    string playerName; 
    cout << endl;
    cout << "Player " << i << ", please enter your name:" << endl;
    cin >> playerName;
    
    while (playerName == "BANK") {
      cout << "Invalid Name is entered. Please enter a different name:" << endl;
      cin >> playerName;
    }
    cout << endl;
    cout << "Player " << playerName << ", choose your piece:" << endl;
    if (G) {
      cout << "(G) Goose" << endl;
    }
    if (B) {
      cout << "(B) GRT Bus" << endl;
    }
    if (D) {
      cout << "(D) Tim Hortons Doughnut" << endl;
    }
    if (P) {
      cout << "(P) Professor" << endl;
    }
    if (S) {
      cout << "(S) Student" << endl;
    }
    if (M) {
      cout << "($) Money" << endl;
    }
    if (L) {
      cout << "(L) Laptop" << endl;
    }
    if (T) {
      cout << "(T) Pink Tie" << endl;
    }

    char piece = '0';
    while (!(piece == 'G' || piece == 'B' || piece == 'D' || piece == 'P' 
          || piece == 'S' || piece == '$' || piece == 'L' || piece == 'T')) {
      cout << endl;
      cout << "Please enter one of the above characters: " << endl;
      cin >> piece;

      if (cin.fail()) {
        cin.clear();
        cin.ignore();
      }
    }
    switch (piece) {
      case 'G':
        G = false;
        break;
      case 'B':
        B = false;
        break;
      case 'D':
        D = false;
        break;
      case 'P':
        P = false;
        break;
      case 'S':
        S = false;
        break;
      case '$':
        M = false;
        break;
      case 'L':
        L = false;
        break;
      case 'T':
        T = false;
        break;
    }
    // Create player and add to game
    shared_ptr<Player> p = game->addPlayer(playerName, piece);
  }
}

void Controller::play() {
  cout << endl;
  cout << "Game begins! \nAvailable commands are: \n'roll' \n'next' \n'trade <name> <give money/property> <receive property/money>' \n'improve <property> buy/sell' \n'mortgage/unmortgage <property>' \n'bankrupt' \n'assets' \n'all' \n'save <filename>'" << endl;
  if (testingMode) {
    cout << "'roll' <die1> <die2>" << endl;
  }
  game->start();
  game->attachDisplay(display);
  
  cout << ANSI_START << START_COLOUR_PREFIX << GLOBAL_COLOUR << START_COLOUR_SUFFIX << esc_char << "[1m";
  cout << *display << endl;
  cout << esc_char << "[0m" << STOP_COLOUR << endl;
  
  bool isFirstTurn = true;
  // bool rollDc = false; 
  while (true) {
    cout << endl;
    if (!isFirstTurn) {
      cout << "Player " + game->curPlayerName() + "'s turn:" << endl;
      cout << "===================================================================================================================================" << endl;
    }
    // cout << "Player " + game->curPlayerName() + "'s turn:" << endl;
    // cout << "===================================================================================================================================" << endl;
    
    // if (game->lineStatus()) {
    //     cout << "Status: In Tims Line (for " << game->curPlayer()->getStuckCount() << " turns)" << endl;
    //     game->curPlayer()->inTimsLine();
    //     // continue;
    // } else 
    if (game->lineStatus() && !game->curPlayer()->hasRolled()) {
        cout << "Status: In Tims Line (for " << game->curPlayer()->getStuckCount() << " turns)" << endl;
        game->inTimsLine(); 
        // game->curPlayer()->inTimsLine();
        continue;
    } 
    else if (game->lineStatus()) {
        cout << "Status: In Tims Line (for " << game->curPlayer()->getStuckCount() << " turns)" << endl;
    }
    
    // if (game->lineStatus()) {
    //   game->inTimsLine();
    // }
    try {
    // /cin.ignore(1, '\n');
      string line;
      getline(cin, line);
      istringstream iss{line};
      string keyword;
      iss >> keyword;
      
      if (keyword == "roll") {
        if (!iss.eof() && testingMode) {
            int die1, die2;
            iss >> die1 >> die2;
            game->roll(die1, die2);  // testing mode
            
            cout << ANSI_START << START_COLOUR_PREFIX << GLOBAL_COLOUR << START_COLOUR_SUFFIX << esc_char << "[1m";
            cout << *display << endl;
            cout << esc_char << "[0m" << STOP_COLOUR << endl;
          } else {
            game->roll();  // regular
            cout << ANSI_START << START_COLOUR_PREFIX << GLOBAL_COLOUR << START_COLOUR_SUFFIX << esc_char << "[1m";
            cout << *display << endl;
            cout << esc_char << "[0m" << STOP_COLOUR << endl;
          }
      }

      else if (keyword == "next") {
        game->next();
      }

      else if (keyword == "trade") {
        string player;
        iss >> player;
        
        string give, recieve; 
        iss >> give; 
        iss >> recieve; 
        
        trade(player, give, recieve);

      }

      else if (keyword == "improve") {
        string property;
        iss >> property;

        string action;
        iss >> action;

        if (action == "buy") {
          game->buyImprove(property);
          
          cout << ANSI_START << START_COLOUR_PREFIX << GLOBAL_COLOUR << START_COLOUR_SUFFIX << esc_char << "[1m";
          cout << *display << endl;
          cout << esc_char << "[0m" << STOP_COLOUR << endl;
        }
        if (action == "sell") {
          game->sellImprove(property);
          
          cout << ANSI_START << START_COLOUR_PREFIX << GLOBAL_COLOUR << START_COLOUR_SUFFIX << esc_char << "[1m";
          cout << *display << endl;
          cout << esc_char << "[0m" << STOP_COLOUR << endl;
        }
      }

      else if (keyword == "mortgage") {
        string property;
        iss >> property;
        game->mortgage(property);
        cout << "You have successfully mortgaged " << property << endl; 
      }

      else if (keyword == "unmortgage") {
        string property;
        iss >> property;
        game->unmortgage(property);
        cout << "You have successfully unmortgaged " << property << endl; 
      }

      else if (keyword == "assets") {
        game->assets();
      } else if (keyword == "all") {
        game->all();
      }

      else if (keyword == "save") {
        string filename;
        iss >> filename;
        save(filename);
      }
    } catch (WatopolyException e) {

      cout << e.getMsg() << endl;

    
    } catch (OweMoney& debt) {

      try {
        game->bankrupt(debt);
      } catch (WatopolyException e) {
        if (e.getMsg() == "ENDGAME") {
          // Game ends here
          cout << game->curPlayerName() << " wins the game! Thank you for playing" << endl;
          break;
        }
      }
    } catch (Auction& auction) {
      game->startAuction(auction);
    }
    isFirstTurn = false;
  }
}

void Controller::load(std::string fileName) {
  ifstream ifs{fileName};

  cout << "Loading game..." << endl;
  
  int numPlayers;
  ifs >> numPlayers;
  string line;
  getline(ifs, line);
  
  for (int i = 0; i < numPlayers; ++i) {
    getline(ifs, line);
    istringstream iss{line};

    string playerName;
    iss >> playerName;

    char piece;
    iss >> piece;

    int TimCups;
    iss >> TimCups;

    int money;
    iss >> money;

    int position;
    iss >> position;
    
    shared_ptr<Player> p = game->addPlayer(playerName, piece, position);
    
    if (position == 10) {
      bool inTimsLine; // either 1 or 0 
      iss >> inTimsLine;
      
      if (inTimsLine) {
        p->setPlayerStuck();
        
        int stuckCount;
        iss >> stuckCount;
        p->updateStuckCount(stuckCount);
      }
    }
    p->setTimsCups(TimCups);
    p->deposit(money - 1500);
  }
  // now go through properties 
  
  while (!getline(ifs, line).eof()) {
    istringstream iss{line};

    string building;
    iss >> building;
    
    shared_ptr<Tile> property = game->getTileByName(building);

    shared_ptr<Ownable> ownableBuilding = dynamic_pointer_cast<Ownable>(property);

    string playerName;
    iss >> playerName;
    
    if (!(playerName == "BANK")) {
      // updates player block count in setowner 
      ownableBuilding->setOwner(game->getPlayerByName(playerName).get(), true);
      // cout << ownableBuilding->getName() << endl;
    }
    
    int improvementLevel;
    iss >> improvementLevel;
    
    if (improvementLevel == -1) { // -1 indicates it's mortgaged
      ownableBuilding->setIsMortgaged(true);
    } else {
      ownableBuilding->setImprovementLevel(improvementLevel);
    }
  }

}

void Controller::save(std::string fileName) {
  ofstream ofs{fileName};
  game->save(ofs);
}


void Controller::trade(string name, string give, string receive) {
	
  bool giveIsProp = true; 
  bool recieveIsProp = true; 

  // check if give is a property
  for (char i : give) {
    if (isdigit(i)) {
      giveIsProp = false; 
      break; 
    }
  }
  
  // check if receive is a property
  for (char i : receive) {
    if (isdigit(i)) {
      recieveIsProp = false; 
      break; 
    }
  }

  // if all chars -> user likely to input a property
  if (!giveIsProp && !recieveIsProp) {
			cout << "Sorry, that is an invalid trade. You cannot trade cash with cash." << endl;
	} else {
    // get descision from other player
    // while (true) { // while loop to catch error
      cout << endl;
      cout << "Player " + name + ", what is your response? Enter (accept/reject):" << endl;
      
      string decision;
      cin >> decision;
      
      if (decision == "accept") {
        
        if (giveIsProp && !recieveIsProp) {
          game->trade(name, give, stoi(receive));
          cout << "Trade successful! You receive $" << receive << " and " << name << " receives " << give << endl;  
        } else if (!giveIsProp && recieveIsProp) {
          game->trade(name, stoi(give), receive);
          cout << "Trade successful! You receive " << receive << " and " << name << " receives $" << give << endl;
        } else if (giveIsProp && recieveIsProp) {
          game->trade(name, give, receive);
          cout << "Trade successful! You receive " << receive << " and " << name << " receives " << give << endl;
        }
        // break;
      } else if (decision == "reject") {
        cout << "The trade has been rejected. Please propose another trade or enter another command." << endl;
        // break;
      } else {
        cout << "Please enter a valid command (accept/reject), case sensitive." << endl;
      }
    }
}
    
