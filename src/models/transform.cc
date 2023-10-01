#include "transform.h"

namespace s21 {

Transform::Transform(float translationX, float translationY, float translationZ, 
                     float rotationX,    float rotationY,    float rotationZ, 
                     float scaleX,       float scaleY,       float scaleZ) {
  (void) translationX;
}

void Transform::ApplyTranslation(float, float, float) {}

void Transform::ApplyRotation(float, float) {}

void Transform::ApplyScale(float, float, float) {}

Matrix Transform::GetTransformationMatrix() {
  return Matrix();
}

}  // namespace s21
