#include "model.h"
namespace s21 {

// RENDER methods
void Model::InitOpenGL() {
  render_.InitOpenGL(&object_);
}

void Model::SetViewPort(int w, int h) {
  render_.SetViewPort(w, h);
}

void Model::RenderObject() {
  render_.RenderObject();
}

// TRANSFORM methods
void Model::ApplyTranslationX(double offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationX(offset);
}

void Model::ApplyTranslationY(double offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationY(offset);
}

void Model::ApplyTranslationZ(double offset) {
  transform_.SetObject(&object_);
  transform_.ApplyTranslationZ(offset);
}

void Model::ApplyRotation(double x, double y, double z) {
  transform_.ApplyRotation(x, y, z);
}

void Model::ApplyScale(double x, double y, double z) {
  transform_.ApplyScale(x, y, z);
}

void Model::ParseObjFile(std::string &file_path) {
  object_.Clear();
  parser_.SetObject(&object_);
  parser_.SetFilePath(file_path);
  parser_.Parse();
}

}  // namespace s21
