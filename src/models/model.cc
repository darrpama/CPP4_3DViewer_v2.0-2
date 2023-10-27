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

void Model::PaintGL() {
  render_.PaintGL();
}

// TRANSFORM methods
void Model::ApplyTranslationX(float offset) {
  transform_.ApplyTranslationX(offset);
  render_.InitObjectModel();
}

void Model::ApplyTranslationY(float offset) {
  transform_.ApplyTranslationY(offset);
  render_.InitObjectModel();
}

void Model::ApplyTranslationZ(float offset) {
  transform_.ApplyTranslationZ(offset);
  render_.InitObjectModel();
}

void Model::ApplyRotationX(float angle) {
  transform_.ApplyRotationX(angle);
  render_.InitObjectModel();
}

void Model::ApplyRotationY(float angle) {
  transform_.ApplyRotationY(angle);
  render_.InitObjectModel();
}

void Model::ApplyRotationZ(float angle) {
  transform_.ApplyRotationZ(angle);
  render_.InitObjectModel();
}

void Model::ApplyScale(float k) {
  transform_.ApplyScale(k);
  render_.InitObjectModel();
}

void Model::SetCentralProjection() {
  render_.SetCentralProjection();
}

void Model::SetParallelProjection() {
  render_.SetParallelProjection();
}


void Model::ParseObjFile(std::string &file_path) {
  object_->Clear();
  parser_.SetFilePath(file_path);
  parser_.Parse();
  render_.InitObjectModel();
}

}  // namespace s21
