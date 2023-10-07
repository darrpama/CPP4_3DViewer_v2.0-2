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

void Controller::ApplyRotation(double x, double y, double z) {
  model_.ApplyRotation(x, y, z);
}

void Controller::ApplyScale(double x, double y, double z) {
  model_.ApplyScale(x, y, z);
}

void Controller::ParseObjFile(std::string &file_path) {
  model_.ParseObjFile(file_path);
}

} // namespace s21
