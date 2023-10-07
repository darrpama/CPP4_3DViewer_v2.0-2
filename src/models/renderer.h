#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H

#define GL_SILENCE_DEPRECATION

#include "type.h"
#include "object.h"
#include "transform.h"

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>

namespace s21 {

class Renderer {
 public:
  void InitOpenGL();
  void SetViewPort(int, int);
  void SetProjectionMatrix();
  void RenderObject(Object *);
  void DrawVertices(std::vector<Vertex> *);

  
 private:
  int width_;
  int height_;
  // QOpenGLShaderProgram program_;
  // QOpenGLVertexArrayObject vao_;
  // QOpenGLBuffer vbo_, ebo_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H