#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include "object.h"
#include "type.h"
#include "matrix.h"

namespace s21 {

class Transform {
 public:
  Transform() {};
  void ApplyTranslationX(double offset);
  void ApplyTranslationY(double offset);
  void ApplyTranslationZ(double offset);

  void ApplyRotation(double, double, double);
  void ApplyScale(double, double, double);
  void SetObject(Object *);
  // Matrix GetTransformationMatrix();
  
 private:
  Object *object_;
  double translationX{};
  double translationY{};
  double translationZ{};
  double rotationX{};
  double rotationY{};
  double rotationZ{};
  double scaleX{};
  double scaleY{};
  double scaleZ{};

};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H