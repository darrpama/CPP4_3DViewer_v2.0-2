#include "transform.h"

namespace s21 {

  Transform::Transform() {
    TranslationMatrix.setToIdentity();
    RotationMatrix.setToIdentity();
    ScaleMatrix.setToIdentity();
  };

  void Transform::UpdateTranslationMatrix(float dx, float dy, float dz) {
    TranslationMatrix.setToIdentity();
    TranslationMatrix.translate(dx, dy, dz);
  }

  void Transform::UpdateRotatitionMatrix(float angleX, float angleY, float angleZ) {
    RotationMatrix.setToIdentity();
    RotationMatrix.rotate(angleX, 1.0f, 0.0f, 0.0f);
    RotationMatrix.rotate(angleY, 0.0f, 1.0f, 0.0f);
    RotationMatrix.rotate(angleZ, 0.0f, 0.0f, 1.0f);
  }

  void Transform::UpdateScaleMatrix(float scale) {
    ScaleMatrix.setToIdentity();
    ScaleMatrix.scale(scale);
  }

  void Transform::CalculateTransformMatrix() {
    TransformMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
  }

  QMatrix4x4 Transform::GetTransformMatrix() {
    return TransformMatrix;
  }

}  // namespace s21
