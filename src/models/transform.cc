#include "transform.h"

namespace s21 {
void Transform::ApplyTranslation(double x, double y, double z) {
  translationX = x;
  translationY = y;
  translationZ = z;
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

Matrix Transform::GetTransformationMatrix() {
  return Matrix();
}

}  // namespace s21
