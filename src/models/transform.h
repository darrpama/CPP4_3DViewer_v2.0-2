#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include "object.h"
#include "settings.h"

#include <cmath>
#include <QMatrix4x4>

namespace s21 {

class Transform {
 public:
  Transform(Settings *);
  void UpdateTranslationMatrix();
  void UpdateRotatitionMatrix();
  void UpdateScaleMatrix();

  QMatrix4x4 GetTransformMatrix();

 private:
  Settings *settings_;
  QMatrix4x4 TranslationMatrix_;
  QMatrix4x4 RotationMatrix_;
  QMatrix4x4 ScaleMatrix_;
  QMatrix4x4 TransformMatrix_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H