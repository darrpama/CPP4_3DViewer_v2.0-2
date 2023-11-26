#include "renderer.h"

namespace s21 {
Renderer::Renderer(Object *obj, Transform *m, Settings *s)
    : object_(obj), transform_(m), settings_(s), width_(0), height_(0) {}

Renderer::~Renderer() {
  vbo_.destroy();
  vao_.destroy();
  ebo_.destroy();
}

void Renderer::InitObjectModel() {
  if (object_ == nullptr) return;
  vertices_ = object_->GetFlattenedVertices();
  faces_ = object_->GetFlattenedFaces();
  vao_.bind();
  vbo_.bind();
  vbo_.allocate(vertices_.data(), vertices_.size() * sizeof(GLfloat));
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3,
                                     3 * sizeof(GLfloat));
  shader_program_.enableAttributeArray("aPos");
  ebo_.bind();
  ebo_.allocate(faces_.data(), sizeof(GLuint) * faces_.size());
  vao_.release();
  ebo_.release();
  vbo_.release();
}

void Renderer::InitOpenGL() {
  if (object_ == nullptr) return;
  shader_program_.create();
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":models/shaders/vert.glsl");
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":models/shaders/frag.glsl");
  shader_program_.link();
  vao_.create();
  vbo_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ebo_.create();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void Renderer::PaintGL() {
  if (object_ == nullptr) return;
  InitPaint();
  CalculateCamera();
  shader_program_.bind();
  SetCamera();
  vao_.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (settings_->GetEdgeType() != EdgeType::NO_EDGE) {
    DrawLines();
  }
  if (settings_->GetVerticeType() != VerticeType::NO_VERTICE) {
    DrawPoints();
  }
  vao_.release();
  shader_program_.release();
}

void Renderer::InitPaint() {
  Color bg_color = settings_->GetColor(ColorType::BG_COLOR);
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawLines() {
  glLineWidth(static_cast<float>(settings_->GetEdgeThickness()));
  if (settings_->GetEdgeType() == EdgeType::SOLID) {
    glEnable(GL_LINE_STRIP);
  }
  if (settings_->GetEdgeType() == EdgeType::DASHED) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  }
  QVector3D lines_color =
      NormalizeColor(settings_->GetColor(ColorType::EDGE_COLOR));
  shader_program_.setUniformValueArray("transformation", &transformation_, 1);
  shader_program_.setUniformValueArray("FragColor", &lines_color, 1);
  if (object_->GetRenderType() == RenderType::TRIANGLE_RENDER) {
    glDrawElements(GL_TRIANGLES, faces_.size(), GL_UNSIGNED_INT, nullptr);
  } else {
    glDrawElements(GL_LINES, faces_.size(), GL_UNSIGNED_INT, nullptr);
  }
  if (settings_->GetEdgeType() == EdgeType::SOLID) {
    glDisable(GL_LINE_STRIP);
  }
  if (settings_->GetEdgeType() == EdgeType::DASHED) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void Renderer::DrawPoints() {
  if (settings_->GetVerticeType() == VerticeType::CIRCLE) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(settings_->GetVerticeSize());
  QVector3D vertex_color =
      NormalizeColor(settings_->GetColor(ColorType::VERTICE_COLOR));
  shader_program_.setUniformValueArray("transformation", &transformation_, 1);
  shader_program_.setUniformValueArray("FragColor", &vertex_color, 1);
  glDrawArrays(GL_POINTS, 0, object_->GetVertexCount());
  if (settings_->GetVerticeType() == VerticeType::CIRCLE) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void Renderer::CalculateCamera() {
  float xx = 1 * M_PI / 180;
  float yy = 1 * M_PI / 180;
  float r = 3.0f * cos(yy);
  float xpos = camera_target_.x() + r * sin(xx);
  float ypos = camera_target_.y() + 3.0f * sin(yy);
  float zpos = camera_target_.z() + r * cos(xx);
  camera_pos_ = QVector3D(xpos, ypos, zpos) + camera_target_;
  camera_up_ = QVector3D(-sin(xx) * sin(yy), cos(yy), -cos(xx) * sin(yy));
}

void Renderer::SetViewPort(int w, int h) {
  glViewport(0, 0, w, h);
  width_ = w;
  height_ = h;
  SetCamera();
}

void Renderer::SetCamera() {
  shader_program_.setUniformValueArray("view", &view_, 1);
  projection_.setToIdentity();
  view_.setToIdentity();
  if (settings_->GetProjectionType() == ProjectionType::CENTRAL) {
    projection_.perspective(45.0f, (float)width_ / height_, 0.1f, 100000.0f);
  } else {
    float left = -width_ / 100.0f;
    float right = width_ / 100.0f;
    float bottom = -height_ / 100.0f;
    float top = height_ / 100.0f;
    float near_plane = 0.0001f;
    float far_plane = 1000000.0f;
    projection_.ortho(left, right, bottom, top, near_plane, far_plane);
  }
  view_.lookAt(camera_pos_, camera_target_, camera_up_);
  shader_program_.setUniformValueArray("projection", &projection_, 1);
}

QVector3D Renderer::NormalizeColor(Color color) {
  return QVector3D(color.redF(), color.greenF(), color.blueF());
}

}  // namespace s21
