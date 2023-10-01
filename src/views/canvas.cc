#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent)
    , rotationX_(0.0f)
    , rotationY_(0.0f) {}

void Canvas::SetController(s21::Controller &controller) {
  controller_ = controller;
}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  controller_.InitOpenGL();
}

void Canvas::paintGL() {
  controller_.RenderObject();
}

void Canvas::resizeGL(int w, int h) {
  controller_.SetViewPort(w, h);
}

void Canvas::mousePressEvent(QMouseEvent* mouse) {
  lastMousePos_ = mouse->pos();
}

void Canvas::mouseMoveEvent(QMouseEvent* mouse) {
  QPoint currentMousePos = mouse->pos();
  int deltaX = currentMousePos.x() - lastMousePos_.x();
  int deltaY = currentMousePos.y() - lastMousePos_.y();

  // Update rotation angles based on mouse movement
  rotationX_ += deltaX;
  rotationY_ += deltaY;

  // Update camera transformations based on rotation angles
  lastMousePos_ = currentMousePos;
  update(); // Trigger a redraw
}

void Canvas::mouseReleaseEvent(QMouseEvent* /* event */) {
    // Handle mouse release event if needed
}
