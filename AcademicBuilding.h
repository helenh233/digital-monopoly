#ifndef __ACADEMICBUILDING_H__
#define __ACADEMICBUILDING_H__

#include "Ownable.h"
#include "AbstractSubject.h"

#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <string>

class Player;

class AcademicBuilding : public Ownable, public AbstractSubject {

  int improvementCost;
  std::vector<int> tuitionCosts;
  std::string monopolyBlock;
  static std::map<std::string, int> monopolyBlockImprovement;

public:
  // constructor
  AcademicBuilding(std::string name, std::string monopolyBlock, int index,
    int buyCost, int improvementCost, std::vector<int> tuitionCosts);
  void setOwner(Player* player, bool load) override; // override the virtual function from ownable
  
  void mortgage() override;
  void unmortgage(bool bankrupt=false) override;

  void buyImprovement();
  void sellImprovement();

  int getMonopolyBlockImprovement();

  int getIndex();
  
  void setImprovementLevel(int level) override;

  int getImprovementLevel();

  int getAssetValue() override;

  void chargeRent(Player* player) override;

  void notifyObservers() override;
};

#endif
