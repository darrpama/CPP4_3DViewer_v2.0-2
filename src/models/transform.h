#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include <cmath>

#include "matrix4x4.h"
#include "object.h"
#include "settings.h"

namespace s21 {

class Transform {
 public:
  explicit Transform(Settings *);
  void UpdateTranslationMatrix();
  void UpdateRotationMatrix();
  void UpdateScaleMatrix();
  Matrix4x4 GetTransformMatrix();

 private:
  Settings *settings_;
  Matrix4x4 translation_matrix_;
  Matrix4x4 rotation_matrix_;
  Matrix4x4 scale_matrix_;
  Matrix4x4 transform_matrix_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H