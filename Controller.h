#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "Game.h"
#include "Display.h"
#include "OweMoney.h"
#include "AcademicBuilding.h"


class Controller
{
  std::shared_ptr<Game> game;
  std::shared_ptr<Display> display;
  bool testingMode;

public:
  Controller(std::shared_ptr<Game> game, std::shared_ptr<Display> display, bool testingMode = false);

  void trade(std::string name, std::string give, std::string receive); 
  void start(); // add players
  void play(); // begin inputting commands
  void load(std::string fileName);
  void save(std::string fileName);
};

#endif
