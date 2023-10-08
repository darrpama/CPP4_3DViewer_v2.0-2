#include "transform.h"

namespace s21 {

void Transform::SetObject(Object *object) {
  object_ = object;
}

void Transform::ApplyTranslationX(double offset) {
  std::cout << "offset: " << offset << std::endl;
  std::vector<Vertex> vertices = object_->GetVertices();
  for (unsigned i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].x += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyTranslationY(double offset) {
  std::cout << "offset: " << offset << std::endl;
  std::vector<Vertex> vertices = object_->GetVertices();
  for (unsigned i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].y += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyTranslationZ(double offset) {
  std::cout << "offset: " << offset << std::endl;
  std::vector<Vertex> vertices = object_->GetVertices();
  for (unsigned i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].z += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyRotation(double x, double y, double z) {
  rotationX = x;
  rotationY = y;
  rotationZ = z;
}

void Transform::ApplyScale(double x, double y, double z) {
  scaleX = x;
  scaleY = y;
  scaleZ = z;
}

// Matrix Transform::GetTransformationMatrix() {
//   return Matrix();
// }

}  // namespace s21
