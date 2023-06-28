#include "AbstractObserver.h"
#include "Display.h"
#include "AcademicBuilding.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

Display::Display(size_t width, size_t height) : width{width}, height{height},
                                                theDisplay{
                                                    "_________________________________________________________________________________________",
                                                    "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |",
                                                    "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |",
                                                    "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |",
                                                    "|       |       |       |       |       |       |       |       |       |       |       |",
                                                    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|",
                                                    "|       |                                                                       |       |",
                                                    "|-------|                                                                       |-------|",
                                                    "|OPT    |                                                                       |EIT    |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|       |                                                                       |       |",
                                                    "|-------|                                                                       |-------|",
                                                    "|BMH    |                                                                       |ESC    |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|SLC    |                                                                       |SLC    |",
                                                    "|       |                                                                       |       |",
                                                    "|       |                                                                       |       |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|       |                                                                       |       |",
                                                    "|-------|                                                                       |-------|",
                                                    "|LHI    |                                                                       |C2     |",
                                                    "|       |            _____________________________________________              |       |",
                                                    "|_______|           |                                             |             |_______|",
                                                    "|UWP    |           |  #   #  ##  #####  ###  ###   ###  #  #   # |             |REV    |",
                                                    "|       |           |  #   # #  #   #   #   # #  # #   # #  #   # |             |       |",
                                                    "|       |           |  # # # ####   #   #   # ###  #   # #   # #  |             |       |",
                                                    "|       |           |  # # # #  #   #   #   # #    #   # #    #   |             |       |",
                                                    "|_______|           |  ##### #  #   #    ###  #     ###  ###  #   |             |_______|",
                                                    "|       |           |_____________________________________________|             |NEEDLES|",
                                                    "|-------|                                                                       |HALL   |",
                                                    "|CPH    |                                                                       |       |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|       |                                                                       |       |",
                                                    "|-------|                                                                       |-------|",
                                                    "|DWE    |                                                                       |MC     |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|PAC    |                                                                       |COOP   |",
                                                    "|       |                                                                       |FEE    |",
                                                    "|       |                                                                       |       |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|                                                                       |_______|",
                                                    "|       |                                                                       |       |",
                                                    "|-------|                                                                       |-------|",
                                                    "|RCH    |                                                                       |DC     |",
                                                    "|       |                                                                       |       |",
                                                    "|_______|_______________________________________________________________________|_______|",
                                                    "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|",
                                                    "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |",
                                                    "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |",
                                                    "|       |       |       |       |       |       |       |       |       |       |       |",
                                                    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|",
                                                },
                                                coordinates{
                                                    {{20, {0, 0}}, // For player positions: {row * height + 4 , col * width + 1} to get exact coordinate
                                                     {21, {0, 1}}, // For improvements: {row * height + 1 , col * width + 1}
                                                     {22, {0, 2}},
                                                     {23, {0, 3}},
                                                     {24, {0, 4}},
                                                     {25, {0, 5}},
                                                     {26, {0, 6}},
                                                     {27, {0, 7}},
                                                     {28, {0, 8}},
                                                     {29, {0, 9}},
                                                     {30, {0, 10}},
                                                     {19, {1, 0}},
                                                     {31, {1, 10}},
                                                     {18, {2, 0}},
                                                     {32, {2, 10}},
                                                     {17, {3, 0}},
                                                     {33, {3, 10}},
                                                     {16, {4, 0}},
                                                     {34, {4, 10}},
                                                     {15, {5, 0}},
                                                     {35, {5, 10}},
                                                     {14, {6, 0}},
                                                     {36, {6, 10}},
                                                     {13, {7, 0}},
                                                     {37, {7, 10}},
                                                     {12, {8, 0}},
                                                     {38, {8, 10}},
                                                     {11, {9, 0}},
                                                     {39, {9, 10}},
                                                     {10, {10, 0}},
                                                     {9, {10, 1}},
                                                     {8, {10, 2}},
                                                     {7, {10, 3}},
                                                     {6, {10, 4}},
                                                     {5, {10, 5}},
                                                     {4, {10, 6}},
                                                     {3, {10, 7}},
                                                     {2, {10, 8}},
                                                     {1, {10, 9}},
                                                     {0, {10, 10}}}}
{
}

// When receiving notifications from Players about position changes
void Display::notify(Player* sender) {
   char piece = sender->getPiece();
   // if player already placed
   if (position.count(piece))
   {
      std::string &oldRow = theDisplay.at(position[piece].first);
      // replace old position with a blank
      oldRow[position[piece].second] = ' ';
   }

   if (!sender->isPlayerBankrupt())
   { // place player symbol in new position
      int building = sender->getCurTile()->getIndex();
      // update row #
      position[piece].first = coordinates[building].first * height + 4;
      std::string &newRow = theDisplay.at(position[piece].first);

      // place player in blank col within building tile
      size_t hor = coordinates[building].second * width + 1;
      for (size_t i = hor; i < hor + 7; ++i)
      {
         if (newRow[i] == ' ') // blank col
         {
            // place player symbol
            newRow[i] = piece;
            // update position
            position[piece].second = i;
            break;
         }
      }
   }
}

// When receiving notifications from AcademicBuildings about Improvement Levels
// Can buy up to 5 improvements
// Can also sell
void Display::notify(AcademicBuilding* sender)
{
   int building = sender->getIndex();
   int level = sender->getImprovementLevel();
   size_t ver = coordinates[building].first * height + 1;
   size_t hor = coordinates[building].second * width + 1;
   // Left-aligned "I"s representing each improvement
   for (size_t i = 0; i < level; ++i)
   {
      theDisplay.at(ver)[hor + i] = 'I';
   }
   // Followed by spaces
   for (size_t i = level; i < 7; ++i)
   {
      theDisplay.at(ver)[hor + i] = ' ';
   }
}

// Prints current state of the board, showing positions of each player and the improvement levels of each building
std::ostream &operator<<(std::ostream &out, const Display &d)
{
   for (const auto &row : d.theDisplay)
   {
      out << row << std::endl;
   }
   return out;
}
