#include "controller.h"

namespace s21 {

// RENDER
void Controller::InitOpenGL() {
  model_->InitOpenGL();
}

void Controller::SetViewPort(int w, int h) {
  model_->SetViewPort(w, h);
}

void Controller::PaintGL() {
  model_->PaintGL();
}

// TRANSFORM
void Controller::ApplyTranslationX(float offset) {
  model_->ApplyTranslationX(offset);
}

void Controller::ApplyTranslationY(float offset) {
  model_->ApplyTranslationY(offset);
}

void Controller::ApplyTranslationZ(float offset) {
  model_->ApplyTranslationZ(offset);
}

void Controller::ApplyRotationX(float angle) {
  model_->ApplyRotationX(angle);
}

void Controller::ApplyRotationY(float angle) {
  model_->ApplyRotationY(angle);
}

void Controller::ApplyRotationZ(float angle) {
  model_->ApplyRotationZ(angle);
}

void Controller::ApplyScale(float x) {
  model_->ApplyScale(x);
}

// PARSE
void Controller::ParseObjFile(std::string &file_path) {
  model_->ParseObjFile(file_path);
}

// PROJECTION
void Controller::SetCentralProjection() {
  model_->SetCentralProjection();
}

void Controller::SetParallelProjection() {
  model_->SetParallelProjection();
}

// COLORS
void Controller::SetBackgroundColor(QColor color) {
  model_->SetBackgroundColor(color);
}

void Controller::SetPointsColor(QColor color) {}
void Controller::SetLinesColor(QColor color) {}

} // namespace s21
