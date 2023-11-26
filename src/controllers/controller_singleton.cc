#include "controller_singleton.h"

namespace s21 {

// RENDER
void ControllerSingleton::InitOpenGL() { model_->InitOpenGL(); }
void ControllerSingleton::SetViewPort(int w, int h) {
  model_->SetViewPort(w, h);
}
void ControllerSingleton::PaintGL() { model_->PaintGL(); }
// TRANSFORM
void ControllerSingleton::NormalizeObject() { model_->NormalizeObject(); }
void ControllerSingleton::SetTranslationX(float val) {
  model_->SetTranslationX(val);
}
void ControllerSingleton::SetTranslationY(float val) {
  model_->SetTranslationY(val);
}
void ControllerSingleton::SetTranslationZ(float val) {
  model_->SetTranslationZ(val);
}
float ControllerSingleton::GetTranslationX() {
  return model_->GetTranslationX();
}
float ControllerSingleton::GetTranslationY() {
  return model_->GetTranslationY();
}
float ControllerSingleton::GetTranslationZ() {
  return model_->GetTranslationZ();
}
void ControllerSingleton::SetRotationX(float val) { model_->SetRotationX(val); }
void ControllerSingleton::SetRotationY(float val) { model_->SetRotationY(val); }
void ControllerSingleton::SetRotationZ(float val) { model_->SetRotationZ(val); }
float ControllerSingleton::GetRotationX() { return model_->GetRotationX(); }
float ControllerSingleton::GetRotationY() { return model_->GetRotationY(); }
float ControllerSingleton::GetRotationZ() { return model_->GetRotationZ(); }
void ControllerSingleton::ApplyScale(float x) { model_->ApplyScale(x); }
float ControllerSingleton::GetScale() { return model_->GetScale(); }
// PARSE
void ControllerSingleton::ParseObjFile(QString &file_path) {
  model_->ParseObjFile(file_path);
}

// PROJECTION
void ControllerSingleton::SetProjectionType(const ProjectionType &type) {
  model_->SetProjectionType(type);
}

const ProjectionType &ControllerSingleton::GetProjectionType() {
  return model_->GetProjectionType();
}

// COLORS
void ControllerSingleton::SetColor(ColorType type, const QColor &color) {
  model_->SetColor(type, color);
}

QColor ControllerSingleton::GetColor(const ColorType &type) {
  return model_->GetColor(type);
}

// EDGE
void ControllerSingleton::SetEdgeType(EdgeType type) {
  model_->SetEdgeType(type);
}

const EdgeType &ControllerSingleton::GetEdgeType() {
  return model_->GetEdgeType();
}

void ControllerSingleton::SetEdgeThickness(int position) {
  model_->SetEdgeThickness(position);
}

int ControllerSingleton::GetEdgeThickness() {
  return model_->GetEdgeThickness();
}

// VERTICES
void ControllerSingleton::SetVerticeType(VerticeType type) {
  model_->SetVerticeType(type);
}
const VerticeType &ControllerSingleton::GetVerticeType() {
  return model_->GetVerticeType();
}

void ControllerSingleton::SetVerticeSize(int size) {
  model_->SetVerticeSize(size);
}

int ControllerSingleton::GetVerticeSize() { return model_->GetVerticeSize(); }

// OBJECT
unsigned ControllerSingleton::GetVertexCount() {
  return model_->GetVertexCount();
}

unsigned ControllerSingleton::GetFaceCount() { return model_->GetFaceCount(); }

unsigned ControllerSingleton::GetEdgeCount() { return model_->GetEdgeCount(); }

void ControllerSingleton::MakeScreenshot(QWidget *widget, ScreenshotType type) {
  model_->MakeScreenshot(widget, type);
}

}  // namespace s21
