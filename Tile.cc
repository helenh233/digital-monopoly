#include "Tile.h"
#include <iostream>
using namespace std; 

Tile::Tile(string name, int index) : name{name}, index{index} {}

void Tile::landOnSquare(Player* player) {
    cout << "Landed on tile: " + name + "\n" << endl;
    actionOnSquare(player);
}

void Tile::actionOnSquare(Player* player) {}

string Tile::getName() { 
  return name; 
}

int Tile::getIndex() { 
  return index; 
}

