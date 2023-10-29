#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include <cmath>
#include <QMatrix4x4>

#include "object.h"

namespace s21 {

class Transform {
 public:
  Transform();
  void UpdateTranslationMatrix(float, float, float);
  void UpdateRotatitionMatrix(float, float, float);
  void UpdateScaleMatrix(float);

  void CalculateTransformMatrix();
  QMatrix4x4 GetTransformMatrix();

 private:
  QMatrix4x4 TranslationMatrix_;
  QMatrix4x4 RotationMatrix_;
  QMatrix4x4 ScaleMatrix_;
  QMatrix4x4 TransformMatrix_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H