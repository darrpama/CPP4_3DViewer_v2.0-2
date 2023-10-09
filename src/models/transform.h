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

  void ApplyRotationX(double angle);
  void ApplyRotationY(double angle);
  void ApplyRotationZ(double angle);

  void ApplyScale(double k);
  void SetObject(Object *);
  
 private:
  Object *object_;

};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H