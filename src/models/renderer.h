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
#include <QOpenGLShaderProgram>

namespace s21 {

class Renderer {
 public:
  void InitOpenGL(Object *);
  void SetViewPort(int, int);
  void SetProjectionMatrix();
  void RenderObject();
  void DrawVertices(std::vector<Vertex> *);
  
 private:
  Object *object_;
  int width_;
  int height_;

  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_, ebo_;
  QOpenGLShaderProgram shader_program_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H