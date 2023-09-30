#include "controller.h"

namespace s21 {

void Controller::InitOpenGL() {
  model_.InitOpenGL();
}

void Controller::SetViewPort(int w, int h) {
  model_.SetViewPort(w, h);
}

void Controller::RenderObject() {
  model_.RenderObject();
}

} // namespace s21
