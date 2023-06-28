#include "AbstractSubject.h"
#include "AbstractObserver.h"
#include <memory>
#include <vector>

void AbstractSubject::attach(std::shared_ptr<AbstractObserver> obs) {
   observers.emplace_back(obs);
}

void AbstractSubject::detach(std::shared_ptr<AbstractObserver> obs) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == obs) {
      observers.erase(it);
      break;
    }
  }
}
