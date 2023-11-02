
#include "canvas.h"
Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent){}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  s21::Controller::GetInstance().InitOpenGL();
}

void Canvas::paintGL() {
  s21::Controller::GetInstance().PaintGL();
}

void Canvas::resizeGL(int w, int h) {
  s21::Controller::GetInstance().SetViewPort(w, h);
}

void Canvas::UpdateWidget() {
  update();
}
