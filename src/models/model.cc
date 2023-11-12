#include "model.h"
#include <chrono>
#include <iostream>

namespace s21 {

// RENDER methods
void Model::InitOpenGL() {
  object_->Clear();
  render_->InitOpenGL();
}

void Model::SetViewPort(int w, int h) {
  render_->SetViewPort(w, h);
}

void Model::PaintGL() {
  render_->PaintGL();
}

void Model::SetProjectionType(const ProjectionType &type) {
  settings_->SetProjectionType(type);
}

const ProjectionType &Model::GetProjectionType() {
  return settings_->GetProjectionType();
}

// TRANSFORM methods
void Model::NormalizeObject() {
  object_->Normalize();
  render_->InitObjectModel();
}

void Model::ApplyTranslation(float x, float y, float z) {
  settings_->SetTranslation(x, y, z);
  transform_->UpdateTranslationMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::ApplyRotation(float x, float y, float z) {
  settings_->SetRotation(x, y, z);
  transform_->UpdateRotatitionMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::ApplyScale(float f) {
  settings_->SetScale(f);
  transform_->UpdateScaleMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::SetColor(ColorType type, const QColor &color) {
  settings_->SetColor(type, color);
}

const QColor &Model::GetColor(const ColorType &type) {
  return settings_->GetColor(type);
}

// PARSE
void Model::ParseObjFile(QString &file_path) {
  auto start = std::chrono::high_resolution_clock::now();
  
  object_->Clear();
  parser_->SetFilePath(file_path);
  parser_->Parse();
  render_->InitObjectModel();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  // Print the execution time
  std::cout << "ParseObjFile() Execution time: " << duration << " milliseconds" << std::endl;

}

}  // namespace s21
