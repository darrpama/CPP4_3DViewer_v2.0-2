#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBSERVABLE_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBSERVABLE_H

#include "observer.h"

#include <vector>

namespace s21 {

class Observable {
 public:
  void AddObserver(Observer *);
  void NotifyUpdate();

 private: 
  std::vector<Observer*> _observers;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBSERVABLE_H