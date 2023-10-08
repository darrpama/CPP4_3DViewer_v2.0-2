#include "transform.h"

namespace s21 {

void Transform::SetObject(Object *object) {
  object_ = object;
}

void Transform::ApplyTranslationX(double offset) {
  std::vector<Vertex> vertices = object_->GetVertices();
  for (size_t i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].x += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyTranslationY(double offset) {
  std::vector<Vertex> vertices = object_->GetVertices();
  for (size_t i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].y += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyTranslationZ(double offset) {
  std::vector<Vertex> vertices = object_->GetVertices();
  for (size_t i = 0; i < object_->GetVertexCount(); ++i) {
    vertices[i].z += offset;
  }
  object_->SetVertices(vertices);
}

void Transform::ApplyRotationX(double angle) {

}

void Transform::ApplyRotationY(double angle) {

}

void Transform::ApplyRotationZ(double angle) {

}

void Transform::ApplyScale(double x, double y, double z) {
  
}

// Matrix Transform::GetTransformationMatrix() {
//   return Matrix();
// }

}  // namespace s21
