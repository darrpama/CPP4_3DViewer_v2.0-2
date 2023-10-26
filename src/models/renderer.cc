#include "renderer.h"

namespace s21 {
Renderer::~Renderer() {
  vbo_.destroy();
  vao_.destroy();
  ebo_.destroy();
}

void Renderer::InitOpenGL() {
  if (object_ == nullptr) {
    return;
  }
  projection_type_ = false;
  move_object_ = camera_target_ = QVector3D(0.0f, 0.0f, 0.0f);
  scale_factor_ = 1.0f;

  // link our shaders to our program
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

void Renderer::RenderObject() {
  if (object_ == nullptr) return;

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CalculateCamera();

  shader_program_.bind();
  
  QMatrix4x4 model;

  shader_program_.setUniformValueArray("view", &view_, 1);
  projection_.setToIdentity();
  view_.setToIdentity();
  
  projection_.perspective(45.0f, (float) width_ / height_, 0.1f, 100.0f);

  // projection_type_
  //     ? projection.perspective(45.0f, (float) width_ / height_, 0.1f, 100.0f)
  //     : projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  
  view_.lookAt(camera_pos_, camera_target_, camera_up_);

  shader_program_.setUniformValueArray("projection", &projection_, 1);

  model.setToIdentity();
  // model.translate(move_object_);
  // model.rotate(rotation_);
  // model.scale(scale_factor_);
  shader_program_.setUniformValueArray("model", &model, 1);

  // Draw
  DrawModel();

  shader_program_.release();
}

void Renderer::DrawModel() {
  vertices_ = object_->GetFlattenedVertices();
  // PrintFaces();
  vao_.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // GL_FILL
  glLineWidth(5.0f);

  // Draw lines 
  glLineStipple(1, 0x00FF);
  glEnable(GL_LINE_STRIP);
    glDrawElements(GL_TRIANGLES, faces_.size(), GL_UNSIGNED_INT, nullptr);
  glDisable(GL_LINE_STRIP);

  // Draw points
  glEnable(GL_POINT_SMOOTH);
    glPointSize(10);
    QVector3D vertex_color(1.0, 0.0, 0.0);
    shader_program_.setUniformValueArray("FragColor", &vertex_color, 1);
    glDrawArrays(GL_POINTS, 0, object_->GetVertices().size());
  glDisable(GL_POINT_SMOOTH);

  vao_.release();
}

void Renderer::CalculateCamera() {
  float xx = x_rot_ * M_PI / 180;
  float yy = y_rot_ * M_PI / 180;
  
  float r = 3.0f * cos(yy);
  
  float xpos = camera_target_.x() + r * sin(xx);
  float ypos = camera_target_.y() + 3.0f * sin(yy);
  float zpos = camera_target_.z() + r * cos(xx);

  camera_pos_ = QVector3D(xpos, ypos, zpos) + camera_target_;
  camera_up_ = QVector3D(-sin(xx) * sin(yy), cos(yy), -cos(xx) * sin(yy));
}

void Renderer::PrintFaces() {
  int j = 0;
  for (size_t i = 0; i < faces_.size(); i++) {
    unsigned int value = faces_[i];
    std::cout << value << " ";
    j++;
    if (j >= 3) {
      std::cout << std::endl;
      j = 0;
    }
  }
  std::cout << std::endl << std::endl;
}

}  // namespace s21
