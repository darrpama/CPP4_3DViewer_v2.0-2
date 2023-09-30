#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H

#include "type.h"
#include "Object.h"
#include "transform.h"
#include "renderer.h"

namespace s21 {

class Model {
 public:
  Model() : render_(), object_(), transform_() {}

  void InitOpenGL();
  void SetViewPort(int, int);
  void RenderObject();
  Object TestObject();
  
 private:
  Renderer render_;
  Object object_;
  Transform transform_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H