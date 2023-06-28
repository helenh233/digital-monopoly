#ifndef DISPLAY_H
#define DISPLAY_H


#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>


#include "AbstractObserver.h"

class Display : public AbstractObserver
{
   size_t width;
   size_t height;
   std::vector<std::string> theDisplay;
   // {Tile name : (row, col)}
   std::map<int, std::pair<size_t, size_t>> coordinates;
   // {Player symbol : (ver, hor)}
   std::map<char, std::pair<size_t, size_t>> position;

public:
   Display(size_t width = 8, size_t height = 5);
   void notify(Player* subject) override;
   void notify(AcademicBuilding* subject) override;
   
   friend std::ostream &operator<<(std::ostream &out, const Display &display);
};

#endif
