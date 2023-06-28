#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

#include "AbstractObserver.h"

class AbstractObserver;
class Player;
class AcademicBuilding;

class AbstractSubject
{
    protected:
    std::vector<std::shared_ptr<AbstractObserver>> observers;

public:
    void attach(std::shared_ptr<AbstractObserver> obs);
    void detach(std::shared_ptr<AbstractObserver> obs);
    virtual void notifyObservers() = 0;
    // virtual ~AbstractSubject() = 0;
};

#endif
