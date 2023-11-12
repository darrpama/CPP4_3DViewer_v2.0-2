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
void Controller::NormalizeObject() {
  model_->NormalizeObject();
}

void Controller::ApplyTranslation(float x, float y, float z) {
  model_->ApplyTranslation(x, y, z);
}

void Controller::ApplyRotation(float x, float y, float z) {
  model_->ApplyRotation(x, y ,z);
}

void Controller::ApplyScale(float x) {
  model_->ApplyScale(x);
}

// PARSE
void Controller::ParseObjFile(QString &file_path) {
  model_->ParseObjFile(file_path);
}

// PROJECTION
void Controller::SetProjectionType(const ProjectionType &type) {
  model_->SetProjectionType(type);
}

const ProjectionType &Controller::GetProjectionType() {
  return model_->GetProjectionType();
}

// COLORS
void Controller::SetColor(ColorType type, const QColor &color) {
  model_->SetColor(type, color);
}

const QColor &Controller::GetColor(const ColorType &type) {
  return model_->GetColor(type);
}

// EDGE
void Controller::SetEdgeType(EdgeType type) {
  model_->SetEdgeType(type);
}

void Controller::SetEdgeThikness(int position) {
  model_->SetEdgeThikness(position);
}

// VERTICES
void Controller::SetVerticeType(VerticeType type) {
  model_->SetVerticeType(type);
}

void Controller::SetVerticeSize(int size) {
  model_->SetVerticeSize(size);
}

unsigned Controller::GetVertexCount() {
  return model_->GetVertexCount();
}

unsigned Controller::GetFaceCount() {
  return model_->GetFaceCount();
}

unsigned Controller::GetEdgeCount() {
  return model_->GetEdgeCount();
}

} // namespace s21
