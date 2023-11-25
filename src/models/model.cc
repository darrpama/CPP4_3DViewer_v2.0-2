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
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::SetTranslationY(float val) {
  settings_->SetTranslationY(val);
  transform_->UpdateTranslationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::SetTranslationZ(float val) {
  settings_->SetTranslationZ(val);
  transform_->UpdateTranslationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::SetRotationX(float val) {
  settings_->SetRotationX(val);
  transform_->UpdateRotatitionMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::SetRotationY(float val) {
  settings_->SetRotationY(val);
  transform_->UpdateRotatitionMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::SetRotationZ(float val) {
  settings_->SetRotationZ(val);
  transform_->UpdateRotatitionMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void Model::ApplyScale(float f) {
  settings_->SetScale(f);
  transform_->UpdateScaleMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
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

void Model::SetColor(ColorType type, const QColor &qcolor) {
  Color color = Color(qcolor.red(), qcolor.green(), qcolor.blue());
  settings_->SetColor(type, color);
}

QColor Model::GetColor(const ColorType &type) {
  Color color = settings_->GetColor(type);
  return QColor(color.red, color.green, color.blue);
}

// PARSE
void Model::ParseObjFile(QString &file_path) {
  auto start = std::chrono::high_resolution_clock::now();
  
  object_->Clear();
  parser_->SetFilePath(file_path.toStdString());
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

QMatrix4x4 Model::ConvertToQMatrix(Matrix4x4 m) {
  return QMatrix4x4(
    m.at(0,0), m.at(1,0), m.at(2,0), m.at(3,0), 
    m.at(0,1), m.at(1,1), m.at(2,1), m.at(3,1), 
    m.at(0,2), m.at(1,2), m.at(2,2), m.at(3,2), 
    m.at(0,3), m.at(1,3), m.at(2,3), m.at(3,3)
  );
}

}  // namespace s21
