#include "renderer.h"

namespace s21 {

void Renderer::InitOpenGL() {
  if (object_ == nullptr) {
    return;
  }
  projection_type_ = false;
  move_object = camera_target_ = QVector3D(0.0f, 0.0f, 0.0f);
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

  // ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  // ebo_.create();
  // ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void Renderer::InitObjectModel() {
  vertices_ = object_->GetVerticesAsArray();

  // unsigned int indices[] = {  // note that we start from 0!
  //     0, 1, 3,   // first triangle
  //     1, 2, 3    // second triangle
  // };

  vao_.bind();
  vbo_.bind();
  
  vbo_.allocate(vertices_, object_->GetVertexCount() * 3 * sizeof(float));
  
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  shader_program_.enableAttributeArray("aPos");

  // ebo_.bind();
  // ebo_.allocate(indices, sizeof(indices));
  // ebo_.allocate(&indices, sizeof(indices));

  shader_program_.bind();
  
  vao_.release();
  // ebo_.release();
  vbo_.release();
  shader_program_.release();
}

void Renderer::SetViewPort(int w, int h) {
  glViewport(0, 0, w, h);
  width_ = w;
  height_ = h;
}

void Renderer::RenderObject() {
  if (object_ == nullptr) {
    return;
  }
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CalculateCamera();

  shader_program_.bind();

  shader_program_.setUniformValueArray("view", &view, 1);
  projection.setToIdentity();
  
  projection.perspective(45.0f, (float) width_ / height_, 0.1f, 100.0f);

  // projection_type_
  //     ? projection.perspective(45.0f, (float) width_ / height_, 0.1f, 100.0f)
  //     : projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  
  view.setToIdentity();
  view.lookAt(camera_pos_, camera_target_, camera_up_);

  shader_program_.setUniformValueArray("projection", &projection, 1);

  QMatrix4x4 model;
  model.setToIdentity();
  model.translate(move_object);
  model.rotate(rotation_);
  model.scale(scale_factor_);
  shader_program_.setUniformValueArray("model", &model, 1);

  // Draw
  vao_.bind();
  // glLineStipple(1, 0x00FF);
  // glEnable(GL_POINT_SMOOTH);

  glPointSize(10);
  
  QVector3D v_col(1.0, 0.0, 0.0);
  shader_program_.setUniformValueArray("FragColor", &v_col, 1);
  
  std::cout << "vertex count: " << object_->GetVertexCount() << std::endl;

  glDrawArrays(GL_POINTS, 0, object_->GetVertexCount());
  
  // glDisable(GL_POINT_SMOOTH);
  
  // vao_.release();
  // shader_program_.release();
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

}  // namespace s21
