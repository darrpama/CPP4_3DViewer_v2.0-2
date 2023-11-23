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

void Controller::SetTranslationX(float val) {
  model_->SetTranslationX(val);
}

void Controller::SetTranslationY(float val) {
  model_->SetTranslationY(val);
}

void Controller::SetTranslationZ(float val) {
  model_->SetTranslationZ(val);
}

float Controller::GetTranslationX() {
  return model_->GetTranslationX();
}
float Controller::GetTranslationY() {
  return model_->GetTranslationY();
}
float Controller::GetTranslationZ() {
  return model_->GetTranslationZ();
}

void Controller::SetRotationX(float val) {
  model_->SetRotationX(val);
}

void Controller::SetRotationY(float val) {
  model_->SetRotationY(val);
}

void Controller::SetRotationZ(float val) {
  model_->SetRotationZ(val);
}

float Controller::GetRotationX() {
  return model_->GetRotationX();
}
float Controller::GetRotationY() {
  return model_->GetRotationY();
}
float Controller::GetRotationZ() {
  return model_->GetRotationZ();
}

void Controller::ApplyScale(float x) {
  model_->ApplyScale(x);
}

float Controller::GetScale() {
  return model_->GetScale();
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

QColor Controller::GetColor(const ColorType &type) {
  return model_->GetColor(type);
}

// EDGE
void Controller::SetEdgeType(EdgeType type) {
  model_->SetEdgeType(type);
}

const EdgeType &Controller::GetEdgeType() {
  return model_->GetEdgeType();
}

void Controller::SetEdgeThickness(int position) {
  model_->SetEdgeThickness(position);
}

int Controller::GetEdgeThickness() {
  return model_->GetEdgeThickness();
}

// VERTICES
void Controller::SetVerticeType(VerticeType type) {
  model_->SetVerticeType(type);
}
const VerticeType &Controller::GetVerticeType() {
  return model_->GetVerticeType();
}

void Controller::SetVerticeSize(int size) {
  model_->SetVerticeSize(size);
}

int Controller::GetVerticeSize() {
  return model_->GetVerticeSize();
}

// OBJECT
unsigned Controller::GetVertexCount() {
  return model_->GetVertexCount();
}

unsigned Controller::GetFaceCount() {
  return model_->GetFaceCount();
}

unsigned Controller::GetEdgeCount() {
  return model_->GetEdgeCount();
}

void Controller::MakeScreenshot(QWidget *widget, ScreenshotType type) {
  model_->MakeScreenshot(widget, type);
}

} // namespace s21
