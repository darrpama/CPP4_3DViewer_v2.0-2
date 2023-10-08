#include "controller.h"

namespace s21 {

// Render endpoints
void Controller::InitOpenGL() {
  model_.InitOpenGL();
}

void Controller::SetViewPort(int w, int h) {
  model_.SetViewPort(w, h);
}

void Controller::RenderObject() {
  model_.RenderObject();
}

// Transform endpoints
void Controller::ApplyTranslationX(double offset) {
  model_.ApplyTranslationX(offset);
}

void Controller::ApplyTranslationY(double offset) {
  model_.ApplyTranslationY(offset);
}

void Controller::ApplyTranslationZ(double offset) {
  model_.ApplyTranslationZ(offset);
}

void Controller::ApplyRotationX(double angle) {
  model_.ApplyRotationX(x, y, z);
}

void Controller::ApplyRotationY(double angle) {
  model_.ApplyRotationY(x, y, z);
}

void Controller::ApplyRotationZ(double angle) {
  model_.ApplyRotationZ(x, y, z);
}


void Controller::ApplyScale(double x, double y, double z) {
  model_.ApplyScale(x, y, z);
}

void Controller::ParseObjFile(std::string &file_path) {
  model_.ParseObjFile(file_path);
}

} // namespace s21
