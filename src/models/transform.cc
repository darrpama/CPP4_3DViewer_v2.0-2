#include "transform.h"

namespace s21 {

Transform::Transform() {
  TranslationMatrix_.setToIdentity();
  RotationMatrix_.setToIdentity();
  ScaleMatrix_.setToIdentity();
};

void Transform::UpdateTranslationMatrix(float dx, float dy, float dz) {
  TranslationMatrix_.setToIdentity();
  TranslationMatrix_.translate(dx, dy, dz);
}

void Transform::UpdateRotatitionMatrix(float angleX, float angleY, float angleZ) {
  RotationMatrix_.setToIdentity();
  RotationMatrix_.rotate(angleX, 1.0f, 0.0f, 0.0f);
  RotationMatrix_.rotate(angleY, 0.0f, 1.0f, 0.0f);
  RotationMatrix_.rotate(angleZ, 0.0f, 0.0f, 1.0f);
}

void Transform::UpdateScaleMatrix(float scale) {
  ScaleMatrix_.setToIdentity();
  ScaleMatrix_.scale(scale);
}

QMatrix4x4 Transform::GetTransformMatrix() {
  TransformMatrix_ = TranslationMatrix_ * RotationMatrix_ * ScaleMatrix_;
  return TransformMatrix_;
}

}  // namespace s21
