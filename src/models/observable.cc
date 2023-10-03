#include "observable.h"

namespace s21 {

void Observable::AddObserver(Observer *observer) {
  _observers.push_back(observer);
}

void Observable::NotifyUpdate() {
  int size = _observers.size();
  for (int i = 0; i < size; i++) {
      _observers[i]->update();
  }
}

}  // namespace s21
