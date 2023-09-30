#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H

#include "type.h"

namespace s21 {

class Renderer {
 public:
  Renderer();
  void InitOpenGL();
  void SetViewPort();
  void SetProjectionMatrix();
  void RenderObject(Object object, Transform transform);
  void HandleInput();
  
 private:
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H