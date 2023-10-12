#include "model.h"

namespace s21 {

// RENDER methods
void Model::InitOpenGL() {
  render_.InitOpenGL();
}

void Model::SetViewPort(int w, int h) {
  render_.SetViewPort(w, h);
}

void Model::RenderObject() {
  render_.RenderObject();
}

// TRANSFORM methods
void Model::ApplyTranslationX(float offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationX(offset);
}

void Model::ApplyTranslationY(float offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationY(offset);
}

void Model::ApplyTranslationZ(float offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationZ(offset);
}

void Model::ApplyRotationX(float angle) {
  transform_.SetObject(&object_);
  transform_.ApplyRotationX(angle);
}

void Model::ApplyRotationY(float angle) {
  transform_.SetObject(&object_);
  transform_.ApplyRotationY(angle);
}

void Model::ApplyRotationZ(float angle) {
  transform_.SetObject(&object_);
  transform_.ApplyRotationZ(angle);
}

void Model::ApplyScale(float k) {
  transform_.SetObject(&object_);
  transform_.ApplyScale(k);
}

void Model::ParseObjFile(std::string &file_path) {
  object_.Clear();
  parser_.SetObject(&object_);
  parser_.SetFilePath(file_path);
  parser_.Parse();
  render_.SetObject(&object_);
}

}  // namespace s21
