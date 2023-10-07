#include "transform.h"

namespace s21 {
void Transform::ApplyTranslationX(double offset, Object &object) {
  std::vector<Vertex> vertices = object.GetVertices();
  for (unsigned i = 0; i < object.GetVertexCount(); ++i) {
    vertices[i].x += offset;
  }
  object.SetVertices(vertices);
}

void Transform::ApplyTranslationY(double offset, Object &object) {
  std::vector<Vertex> vertices = object.GetVertices();
  for (unsigned i = 0; i < object.GetVertexCount(); ++i) {
    vertices[i].y += offset;
  }
  object.SetVertices(vertices);
}

void Transform::ApplyTranslationZ(double offset, Object &object) {
  std::vector<Vertex> vertices = object.GetVertices();
  for (unsigned i = 0; i < object.GetVertexCount(); ++i) {
    vertices[i].z += offset;
  }
  object.SetVertices(vertices);
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
