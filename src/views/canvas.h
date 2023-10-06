#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_GRAPHWIDGET_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_GRAPHWIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include "../controllers/controller.h"

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit Canvas(QWidget *);
  void SetController(s21::Controller *);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int, int) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
 
 private:
  QPoint lastMousePos_;
  float rotationX_;
  float rotationY_;
  s21::Controller *controller_;
};

#endif // GRAPHWIDGET_H
