#include "renderer.h"

namespace s21 {

// TODO BUG: need to fix a crash when obj file uploaded
void Renderer::InitObjectModel() {
//  float *vertices = object_->GetVerticesAsArray();
  float vertices[] = {
    // front face
    -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // back face
    -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f
  };

  unsigned int indices[] = {
    // front face
    0, 1, 2,
    2, 3, 0,
    // back face
    4, 5, 6,
    6, 7, 4,
    // top face
    3, 2, 6,
    6, 7, 3,
    // bottom face
    0, 1, 5,
    5, 4, 0,
    // left face
    0, 3, 7,
    7, 4, 0,
    // right face
    1, 2, 6,
    6, 5, 1
  };


  vao_.create();
  vao_.bind();
  vbo_.create();
  vbo_.bind();
  vbo_.allocate(vertices, 8 * 3 * sizeof(float));
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  shader_program_.enableAttributeArray("aPos");
  ebo_.create();
  ebo_.bind();
  ebo_.allocate(indices, 36 * sizeof(unsigned int));
  vao_.release();
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

  vao_.create();

  vbo_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ebo_.create();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
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
  ebo_.bind();
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  ebo_.release();
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