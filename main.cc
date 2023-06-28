#include <string>
#include <memory>
#include "Game.h"
#include "Display.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
   bool loadGame = false;
   bool testingMode = false;
   std::string fileName;

   for (int i = 1; i < argc; ++i)
   {
      if (argv[i] == std::string("-load"))
      {
         loadGame = true;
         fileName = argv[i + 1];
      }
      else if (argv[i] == std::string("-testing"));
      {
         testingMode = true;
      }
   }

   std::shared_ptr<Game> game = std::make_shared<Game>();
   std::shared_ptr<Display> display = std::make_shared<Display>();

   Controller c = Controller(game, display, testingMode);
   if (loadGame) {
      c.load(fileName);
   } else {
      c.start();
   }

    c.play();

};
