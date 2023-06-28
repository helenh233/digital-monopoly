#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <memory> 


class AcademicBuilding;
class Player; 

class AbstractObserver
{
public:

   // subjects are the 
   virtual void notify(Player* subject) = 0;
   virtual void notify(AcademicBuilding* subject) = 0;
};

#endif
