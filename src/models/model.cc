#include "model.h"

namespace s21 {

// RENDER methods
void Model::InitOpenGL() {
  object_->Clear();
  render_.InitOpenGL();
}

void Model::SetViewPort(int w, int h) {
  render_.SetViewPort(w, h);
}

void Model::PaintGL() {
  render_.PaintGL();
}

// TRANSFORM methods
void Model::ApplyTranslation(float x, float y, float z) {
  transform_.UpdateTranslationMatrix(x, y, z);
  render_.SetTransformMatrix(transform_.GetTransformMatrix());
}

void Model::ApplyRotation(float x, float y, float z) {
  transform_.UpdateRotatitionMatrix(x, y, z);
  render_.SetTransformMatrix(transform_.GetTransformMatrix());
}

void Model::ApplyScale(float f) {
  transform_.UpdateScaleMatrix(f);
  render_.SetTransformMatrix(transform_.GetTransformMatrix());
}

void Model::SetCentralProjection() {
  render_.SetCentralProjection();
}

void Model::SetParallelProjection() {
  render_.SetParallelProjection();
}

// PARSE
void Model::ParseObjFile(std::string &file_path) {
  object_->Clear();
  parser_.SetFilePath(file_path);
  parser_.Parse();
  render_.InitObjectModel();
}

// COLORS
void Model::SetBackgroundColor(QColor color) {
  render_.SetBackgroundColor(color);
  render_.InitObjectModel();
}

void Model::SetPointsColor(QColor color) {
  render_.SetPointsColor(color);
  render_.InitObjectModel();
}

void Model::SetLinesColor(QColor color) {
  render_.SetLinesColor(color);
  render_.InitObjectModel();
}

}  // namespace s21
