#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H

#define GL_SILENCE_DEPRECATION

#include "type.h"
#include "object.h"
#include "transform.h"

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

namespace s21 {

enum EdgeType {NONE, SOLID, DASHED};

class Renderer {
 public:
  Renderer(Object *obj) : object_(obj) {};
  ~Renderer();
  void InitObjectModel();
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();
  void InitPaint();
  void DrawModel();
  void CalculateCamera();
  void SetCamera();
  void SetCentralProjection() {projection_type_ = true;}
  void SetParallelProjection() {projection_type_ = false;}
  void SetBackgroundColor(QColor color) {background_color_ = color; }
  void SetPointsColor(QColor color) {points_color_ = color; }
  void SetLinesColor(QColor color) {lines_color_ = color; }
  void SetEdgeType(EdgeType);
  QVector3D NormalizeColor(QColor color);

 private:
  Object *object_;
  int width_;
  int height_;
  bool projection_type_;
  float x_rotation_, y_rotation_, start_y_, start_x_;
  float scale_factor_;
  QVector<GLfloat> vertices_;
  QVector<GLuint> faces_;

  // COLORS
  QColor background_color_;
  QColor points_color_;
  QColor lines_color_;

  // EDGE TYPES
  EdgeType edge_type_;
  
  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_, ebo_;
  QOpenGLShaderProgram shader_program_;
  QMatrix4x4 view_, projection_;
  QVector3D camera_target_, camera_pos_, camera_up_, move_object_;
  QQuaternion rotation_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H