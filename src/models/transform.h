#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H

#include "type.h"
#include "matrix.h"

namespace s21 {

class Transform {
 public:
  Transform(float, float, float, float, float, float, float, float, float);
  void ApplyTranslation(float, float, float);
  void ApplyRotation(float, float);
  void ApplyScale(float, float, float);
  Matrix GetTransformationMatrix();
  
 private:
  float translationX;
  float translationY;
  float translationZ;
  float rotationX;
  float rotationY;
  float rotationZ;
  float scaleX;
  float scaleY;
  float scaleZ;

};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H