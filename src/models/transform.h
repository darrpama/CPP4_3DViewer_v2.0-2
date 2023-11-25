#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include "object.h"
#include "settings.h"
#include "matrix4x4.h"

#include <cmath>

namespace s21 {

class Transform {
 public:
  Transform(Settings *);
  void UpdateTranslationMatrix();
  void UpdateRotationMatrix();
  void UpdateScaleMatrix();

  Matrix4x4 GetTransformMatrix();

 private:
  Settings *settings_;
  Matrix4x4 TranslationMatrix_;
  Matrix4x4 RotationMatrix_;
  Matrix4x4 ScaleMatrix_;
  Matrix4x4 TransformMatrix_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H