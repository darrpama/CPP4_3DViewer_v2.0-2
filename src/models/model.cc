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

// PARSE
void Model::ParseObjFile(std::string &file_path) {
  object_->Clear();
  parser_.SetFilePath(file_path);
  parser_.Parse();
  render_.InitObjectModel();
}

}  // namespace s21
