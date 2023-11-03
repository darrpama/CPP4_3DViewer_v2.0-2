#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_RENDERER_H

#define GL_SILENCE_DEPRECATION

#include "object.h"
#include "transform.h"
#include "type.h"

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

namespace s21 {

class Renderer {
 public:
  Renderer(Object*, Transform*);
  ~Renderer();
  void InitObjectModel();
  void InitOpenGL();
  void PaintGL();
  void SetViewPort(int, int);

  void SetProjectionType(s21::ProjectionType type) { projection_type_ = type; }
  void SetBackgroundColor(QColor color) { bg_color_ = color; }
  void SetPointsColor(QColor color) { points_color_ = color; }
  void SetLinesColor(QColor color) { lines_color_ = color; }
  void SetEdgeType(EdgeType type) { edge_type_ = type; }
  void SetVerticeType(VerticeType type) { vertice_type_ = type; }
  void SetEdgeThikness(int value) { edge_thikness_ = value; }
  void SetVerticeSize(int value) { vertice_size_ = value; }
  void SetTransformMatrix(QMatrix4x4 m) { transformation_ = m; };

 private:
  Object *object_;
  Transform *transform_;
  int width_;
  int height_;
  
  QColor bg_color_;
  QColor points_color_;
  QColor lines_color_;
  ProjectionType projection_type_;
  EdgeType edge_type_;
  VerticeType vertice_type_;
  int edge_thikness_;
  int vertice_size_;
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
  
  QVector<GLfloat> vertices_; 
  QVector<GLuint> faces_;

  QVector3D NormalizeColor(QColor);
  void CalculateCamera();
  void SetCamera();
  void InitPaint();
  void DrawLines();
  void DrawPoints();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_RENDERER_H
