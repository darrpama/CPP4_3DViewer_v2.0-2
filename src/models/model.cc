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

void Model::SetTranslationX(float val) {
  settings_->SetTranslationX(val);
  transform_->UpdateTranslationMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::SetTranslationY(float val) {
  settings_->SetTranslationY(val);
  transform_->UpdateTranslationMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::SetTranslationZ(float val) {
  settings_->SetTranslationZ(val);
  transform_->UpdateTranslationMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

float Model::GetTranslationX() {
  return settings_->GetTranslationX();
}

float Model::GetTranslationY() {
  return settings_->GetTranslationY();
}

float Model::GetTranslationZ() {
  return settings_->GetTranslationZ();
}

void Model::SetRotationX(float val) {
  settings_->SetRotationX(val);
  transform_->UpdateRotatitionMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::SetRotationY(float val) {
  settings_->SetRotationY(val);
  transform_->UpdateRotatitionMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

void Model::SetRotationZ(float val) {
  settings_->SetRotationZ(val);
  transform_->UpdateRotatitionMatrix();
  render_->SetTransformMatrix(transform_->GetTransformMatrix());
}

float Model::GetRotationX() {
  return settings_->GetRotationX();
}

float Model::GetRotationY() {
  return settings_->GetRotationY();
}

float Model::GetRotationZ() {
  return settings_->GetRotationZ();
}

float Model::GetScale() {
  return settings_->GetScale();
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

void Model::MakeScreenshot(QWidget *widget, ScreenshotType type) {
  ScreenshotContext context;
  if (type == ScreenshotType::BMP) {
    context.SetStrategy(new BmpScreenshotStrategy());
  } else if (type == ScreenshotType::JPG) {
    context.SetStrategy(new JpgScreenshotStrategy());
  } else {
    context.SetStrategy(new JpgScreenshotStrategy());
  }
  context.MakeScreenshot(widget);
}

}  // namespace s21
