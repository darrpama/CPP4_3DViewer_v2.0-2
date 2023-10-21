#include "model.h"

namespace s21 {

// RENDER methods
void Model::InitOpenGL() {
  // object_->Clear();
  // parser_.SetFilePath("/Users/myregree/Desktop/projects/CPP4_3DViewer_v2.0-2/src/assets/objects/cube4.obj");
  // parser_.Parse();
  render_.InitOpenGL();
  // render_.InitObjectModel();
}

void Model::SetViewPort(int w, int h) {
  render_.SetViewPort(w, h);
}

void Model::RenderObject() {
  render_.RenderObject();
}

// TRANSFORM methods
void Model::ApplyTranslationX(float offset) {
  transform_.ApplyTranslationX(offset);
}

void Model::ApplyTranslationY(float offset) {
  transform_.ApplyTranslationY(offset);
}

void Model::ApplyTranslationZ(float offset) {
  transform_.ApplyTranslationZ(offset);
}

void Model::ApplyRotationX(float angle) {
  transform_.ApplyRotationX(angle);
}

void Model::ApplyRotationY(float angle) {
  transform_.ApplyRotationY(angle);
}

void Model::ApplyRotationZ(float angle) {
  transform_.ApplyRotationZ(angle);
}

void Model::ApplyScale(float k) {
  transform_.ApplyScale(k);
}

void Model::ParseObjFile(std::string &file_path) {
  object_->Clear();
  parser_.SetFilePath(file_path);
  parser_.Parse();
  render_.InitObjectModel();
}

}  // namespace s21
