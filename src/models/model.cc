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
  std::cout << "Model::RenderObject: " << object_.GetVertices().size() << std::endl;
  render_.RenderObject(&object_);
}

// TRANSFORM methods
void Model::ApplyTranslation(double x, double y, double z) {
  transform_.ApplyTranslation(x, y, z);
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
  std::cout << "Model::ParseObjFile: " << object_.GetVertices().size() << std::endl;
}

}  // namespace s21
