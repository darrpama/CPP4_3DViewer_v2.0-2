#include "renderer.h"

namespace s21 {

// TODO BUG: need to fix a crash when obj file uploaded

void Renderer::SetObject(Object *object) {
  object_ = object;
  std::cout << "Face count: " << object_->GetFaceCount() << std::endl;
  std::cout << "Edge count: " << object_->GetEdgeCount() << std::endl;
  std::cout << "Vertex count: " << object_->GetVertexCount() << std::endl;
}

void Renderer::InitOpenGL() {
  if (object_ == nullptr) {
    return;
  }

  projection_type = true;  // todo change to enum
  move_object = camera_target_ = QVector3D(0.0f, 0.0f, 0.0f);
  scale_factor = 1.0f;

  // link our shaders to our program
  shader_program_.create();
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":models/shaders/vert.glsl");
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":models/shaders/frag.glsl");
  shader_program_.link();

  float *vertices = object_->GetVerticesAsArray();
  // float vertices[] = {
  //   0.050000, -0.050000, -0.050000,
  //   0.050000, -0.050000, 0.050000,
  //   -0.050000, -0.050000, 0.050000,
  //   -0.050000, -0.050000, -0.050000,
  //   0.050000, 0.050000, -0.050000,
  //   0.050000, 0.050000, 0.050000,
  //   -0.050000, 0.050000, 0.050000,
  //   -0.050000, 0.050000, -0.050000
  // };

  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };

  vao_.create();

  vbo_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ebo_.create();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  vao_.bind();
  vbo_.bind();
  
  vbo_.allocate(vertices, object_->GetVertexCount() * 3 * sizeof(float));
  // vbo_.allocate(&vertices, sizeof(vertices));
  
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  shader_program_.enableAttributeArray("aPos");

  ebo_.bind();
  ebo_.allocate(indices, sizeof(indices));

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
  if (object_ == nullptr) {
    return;
  }
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CalculateCamera();

  shader_program_.bind();

  QMatrix4x4 model;
  shader_program_.setUniformValueArray("view", &view, 1);
  projection.setToIdentity();
  view.setToIdentity();

  projection_type
      ? projection.perspective(45.0f, (float) width_ / height_, 0.1f, 100.0f)
      : projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  
  view.lookAt(camera_pos_, camera_target_, camera_up_);

  shader_program_.setUniformValueArray("projection", &projection, 1);

  model.setToIdentity();
  model.translate(move_object);
  model.rotate(rotation_);
  model.scale(scale_factor);
  shader_program_.setUniformValueArray("model", &model, 1);


  // Draw
  vao_.bind();
  // glLineStipple(1, 0x00FF);

  glEnable(GL_POINT_SMOOTH);
  glPointSize(15);
  
  QVector3D v_col(1.0, 0.0, 0.0);
  shader_program_.setUniformValueArray("FragColor", &v_col, 1);
  
  glDrawArrays(GL_POINTS, 0, object_->GetVertexCount() / 3);  // TODO BUG: program crashes here
  // glDrawArrays(GL_POINTS, 0, 8);
  
  glDisable(GL_POINT_SMOOTH);
  
  vao_.release();
  shader_program_.release();
}

void Renderer::CalculateCamera() {
  float r = 3.0f * cos(y_rot_ * M_PI / 180);
  camera_pos_ = QVector3D(camera_target_.x() + r * sin(x_rot_ * M_PI / 180),
                          camera_target_.y() + 3.0f * sin(y_rot_ * M_PI / 180),
                          camera_target_.z() + r * cos(x_rot_ * M_PI / 180)) +
                camera_target_;

  camera_up_ = QVector3D(-sin(x_rot_ * M_PI / 180) * sin(y_rot_ * M_PI / 180),
                         cos(y_rot_ * M_PI / 180),
                         -cos(x_rot_ * M_PI / 180) * sin(y_rot_ * M_PI / 180));
}

}  // namespace s21
