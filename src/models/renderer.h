#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H

#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "object.h"
#include "settings.h"
#include "transform.h"
#include "type.h"

namespace s21 {

class Renderer {
 public:
  Renderer(Object *, Transform *, Settings *);
  ~Renderer();
  void InitObjectModel();
  void InitOpenGL();
  void PaintGL();
  void SetViewPort(int, int);

  void SetTransformMatrix(QMatrix4x4 m) { transformation_ = m; };

 private:
  Object *object_;
  Transform *transform_;
  Settings *settings_;
  int width_;
  int height_;

  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  QOpenGLShaderProgram shader_program_;
  QMatrix4x4 view_;
  QMatrix4x4 projection_;
  QMatrix4x4 transformation_;
  QVector3D camera_target_;
  QVector3D camera_pos_;
  QVector3D camera_up_;
  QVector3D move_object_;
  QQuaternion rotation_;

  std::vector<GLfloat> vertices_;
  std::vector<GLuint> faces_;

  QVector3D NormalizeColor(Color);
  void CalculateCamera();
  void SetCamera();
  void InitPaint();
  void DrawLines();
  void DrawPoints();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H
