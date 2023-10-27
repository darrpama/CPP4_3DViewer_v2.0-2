
#include "canvas.h"
Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent){}

void Canvas::SetController(s21::Controller *controller) {
  controller_ = controller;
}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  controller_->InitOpenGL();
}

void Canvas::paintGL() {
  controller_->PaintGL();
}

void Canvas::resizeGL(int w, int h) {
  controller_->SetViewPort(w, h);
}

void Canvas::UpdateWidget() {
  update();
}
