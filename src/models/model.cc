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
  render_.RenderObject(object_, transform_);
}

Object Model::TestObject() {
  Object object = Object();
  object.AddVertex();
  return object;
}

}  // namespace s21
