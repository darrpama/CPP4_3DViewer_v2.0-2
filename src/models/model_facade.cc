#include "model_facade.h"

namespace s21 {

void ModelFacade::InitOpenGL() {
  object_->Clear();
  render_->InitOpenGL();
}

void ModelFacade::SetViewPort(int w, int h) { render_->SetViewPort(w, h); }

void ModelFacade::PaintGL() { render_->PaintGL(); }

void ModelFacade::SetProjectionType(const ProjectionType &type) {
  settings_->SetProjectionType(type);
}

const ProjectionType &ModelFacade::GetProjectionType() {
  return settings_->GetProjectionType();
}

void ModelFacade::NormalizeObject() {
  object_->Normalize();
  render_->InitObjectModel();
}

void ModelFacade::SetTranslationX(float val) {
  settings_->SetTranslationX(val);
  transform_->UpdateTranslationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::SetTranslationY(float val) {
  settings_->SetTranslationY(val);
  transform_->UpdateTranslationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::SetTranslationZ(float val) {
  settings_->SetTranslationZ(val);
  transform_->UpdateTranslationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::SetRotationX(float val) {
  settings_->SetRotationX(val);
  transform_->UpdateRotationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::SetRotationY(float val) {
  settings_->SetRotationY(val);
  transform_->UpdateRotationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::SetRotationZ(float val) {
  settings_->SetRotationZ(val);
  transform_->UpdateRotationMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

void ModelFacade::ApplyScale(float f) {
  settings_->SetScale(f);
  transform_->UpdateScaleMatrix();
  QMatrix4x4 qmatrix = ConvertToQMatrix(transform_->GetTransformMatrix());
  render_->SetTransformMatrix(qmatrix);
}

float ModelFacade::GetTranslationX() { return settings_->GetTranslationX(); }

float ModelFacade::GetTranslationY() { return settings_->GetTranslationY(); }

float ModelFacade::GetTranslationZ() { return settings_->GetTranslationZ(); }

float ModelFacade::GetRotationX() { return settings_->GetRotationX(); }

float ModelFacade::GetRotationY() { return settings_->GetRotationY(); }

float ModelFacade::GetRotationZ() { return settings_->GetRotationZ(); }

float ModelFacade::GetScale() { return settings_->GetScale(); }

void ModelFacade::SetColor(ColorType type, const QColor &qcolor) {
  Color color = Color(qcolor.red(), qcolor.green(), qcolor.blue());
  settings_->SetColor(type, color);
}

QColor ModelFacade::GetColor(const ColorType &type) {
  Color color = settings_->GetColor(type);
  return QColor(color.red, color.green, color.blue);
}

void ModelFacade::ParseObjFile(QString &file_path) {
  object_->Clear();
  parser_->SetFilePath(file_path.toStdString());
  parser_->Parse();
  render_->InitObjectModel();
}

void ModelFacade::MakeScreenshot(QWidget *widget, ScreenshotType type) {
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

QMatrix4x4 ModelFacade::ConvertToQMatrix(Matrix4x4 m) {
  return QMatrix4x4(m.at(0, 0), m.at(1, 0), m.at(2, 0), m.at(3, 0), m.at(0, 1),
                    m.at(1, 1), m.at(2, 1), m.at(3, 1), m.at(0, 2), m.at(1, 2),
                    m.at(2, 2), m.at(3, 2), m.at(0, 3), m.at(1, 3), m.at(2, 3),
                    m.at(3, 3));
}

}  // namespace s21
