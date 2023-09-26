#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include <iostream>
#include <QtOpenGLWidgets>
#include <vector>
#include <utility>
#include <unordered_map>
#include <QMouseEvent>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
 public:
  explicit Canvas(QWidget *);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int, int) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
 
 private:
  QPoint lastMousePos;
  float rotationX;
  float rotationY;
};

#endif // GRAPHWIDGET_H
