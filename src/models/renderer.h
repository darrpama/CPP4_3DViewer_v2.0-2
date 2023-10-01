#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H

#include "type.h"
#include "Object.h"
#include "transform.h"

#include <QtOpenGLWidgets>

namespace s21 {

class Renderer {
 public:
  void InitOpenGL();
  void SetViewPort(int, int);
  void SetProjectionMatrix();
  void RenderObject(Object object, Transform transform);
  void HandleInput();
  
 private:
  int width_;
  int height_;
  
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H