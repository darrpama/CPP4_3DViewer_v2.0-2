#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TRANSFORM_H

#include <cmath>

#include "object.h"
#include "type.h"

namespace s21 {

class Transform {
 public:
  Transform(Object *obj) : object_(obj) {};
  void ApplyTranslationX(float offset);
  void ApplyTranslationY(float offset);
  void ApplyTranslationZ(float offset);

  void ApplyRotationX(float angle);
  void ApplyRotationY(float angle);
  void ApplyRotationZ(float angle);

  void ApplyScale(float k);
  void SetObject(Object *);
  
 private:
  Object *object_;

};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_TRANSFORM_H