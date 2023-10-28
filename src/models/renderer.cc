#include "renderer.h"

namespace s21 {
Renderer::~Renderer() {
  vbo_.destroy();
  vao_.destroy();
  ebo_.destroy();
}

void Renderer::InitOpenGL() {
  if (object_ == nullptr) return;

  // colors
  background_color_ = QColor(0,0,0);
  points_color_ = QColor(0,255,255);
  lines_color_ = QColor(255,0,0);

  projection_type_ = true;
  move_object_ = camera_target_ = QVector3D(0.0f, 0.0f, 0.0f);
  scale_factor_ = 1.0f;

  edge_type_ = EdgeType::NONE;

  shader_program_.create();
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":models/shaders/vert.glsl");
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":models/shaders/frag.glsl");
  shader_program_.link();

  vao_.create();

  vbo_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ebo_.create();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  vao_.bind();
  vao_.release();
}

void Renderer::InitObjectModel() {
  vertices_ = object_->GetFlattenedVertices();
  faces_ = object_->GetFlattenedFaces();

  vao_.bind();
  vbo_.bind();
  vbo_.allocate(vertices_.data(), object_->GetVertexCount() * 3 * sizeof(GLfloat));
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  shader_program_.enableAttributeArray("aPos");

  ebo_.bind();
  ebo_.allocate(faces_.data(), sizeof(faces_[0]) * faces_.size());
  
  shader_program_.bind();
  vao_.release();
  ebo_.release();
  vbo_.release();
  shader_program_.release();
}

void Renderer::SetViewPort(int w, int h) {
  glViewport(0, 0, w, h);
  width_ = w;
  height_ = h;
}

void Renderer::InitPaint() {
  glClearColor(
    background_color_.red() / 255.0f,
    background_color_.green() / 255.0f,
    background_color_.blue() / 255.0f,
    1.0f
  );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::PaintGL() {
  if (object_ == nullptr) return;

  InitPaint();
  CalculateCamera();
  shader_program_.bind();
  SetCamera();
  DrawModel();
  shader_program_.release();
}

void Renderer::DrawModel() {
  vertices_ = object_->GetFlattenedVertices();
  vao_.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // GL_FILL

  // Draw lines
  if (edge_type_ != EdgeType::NONE) {
    glLineWidth(static_cast<float>(edge_thikness_));
    if (edge_type_ == EdgeType::SOLID) {
      glEnable(GL_LINE_STRIP);
    }
    if (edge_type_ == EdgeType::DASHED) {
      glLineStipple(1, 0x00FF);
      glEnable(GL_LINE_STIPPLE);
    }
    
    QVector3D lines_color = NormalizeColor(lines_color_);
    shader_program_.setUniformValueArray("FragColor", &lines_color, 1);
    glDrawElements(GL_TRIANGLES, faces_.size(), GL_UNSIGNED_INT, nullptr);
    
    if (edge_type_ == EdgeType::SOLID) {
      glDisable(GL_LINE_STRIP);
    }
    if (edge_type_ == EdgeType::DASHED) {
      glDisable(GL_LINE_STIPPLE);
    }
  }

  // Draw points
  glEnable(GL_POINT_SMOOTH);
    glPointSize(10);
    QVector3D vertex_color = NormalizeColor(points_color_);
    shader_program_.setUniformValueArray("FragColor", &vertex_color, 1);
    glDrawArrays(GL_POINTS, 0, object_->GetVertices().size());
  glDisable(GL_POINT_SMOOTH);

  vao_.release();
}

void Renderer::CalculateCamera() {
  float xx = x_rotation_ * M_PI / 180;
  float yy = y_rotation_ * M_PI / 180;
  
  float r = 3.0f * cos(yy);
  
  // float xpos = camera_target_.x() + r * sin(xx);
  // float ypos = camera_target_.y() + 3.0f * sin(yy);
  // float zpos = camera_target_.z() + r * cos(xx);
  float xpos = camera_target_.x() + 0;
  float ypos = camera_target_.y() + 0;
  float zpos = camera_target_.z() + 2;

  camera_pos_ = QVector3D(xpos, ypos, zpos) + camera_target_;
  camera_up_ = QVector3D(-sin(xx) * sin(yy), cos(yy), -cos(xx) * sin(yy));
}

void Renderer::SetCamera() {
  shader_program_.setUniformValueArray("view", &view_, 1);
  projection_.setToIdentity();
  view_.setToIdentity();
  projection_type_
      ? projection_.perspective(65.0f, (float) height_ / width_, 0.1f, 100.0f)
      : projection_.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  view_.lookAt(camera_pos_, camera_target_, camera_up_);

  shader_program_.setUniformValueArray("projection", &projection_, 1);
}

void Renderer::SetEdgeType(EdgeType type) {
  edge_type_ = type;
}

void Renderer::SetEdgeThikness(int value) {
  edge_thikness_ = value;
}

QVector3D Renderer::NormalizeColor(QColor color) {
    return QVector3D(
      color.red() / 255.0f,
      color.green() / 255.0f,
      color.blue() / 255.0f
    );
}


}  // namespace s21
