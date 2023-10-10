#include "renderer.h"

namespace s21 {

void Renderer::InitOpenGL(Object *object) {
  object_ = object;

  // link our shaders to our program
  shader_program_.create();
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":models/shaders/vert.glsl");
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":models/shaders/frag.glsl");
  shader_program_.link();

  float *vertices2 = object->GetVerticesAsArray();
  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };

  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };  
  // std::vector<Vertex> vertices = object->GetVertices();

  vao_.create();

  vbo_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  ebo_.create();
  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  vao_.bind();
  vbo_.bind();
  vbo_.allocate(vertices, sizeof(vertices));
  
  shader_program_.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 0);
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

void Renderer::SetProjectionMatrix() {
  // set matrix for projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glFrustum(-1, 1, -1, 1, 0, 1000);
  float aspectRatio = static_cast<float>(width_) / height_;
  glFrustum(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, 0.1, 1000000.0);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderObject() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader_program_.bind();
  // Draw
  vao_.bind();
  glLineStipple(1, 0x00FF);
  
  glEnable(GL_POINT_SMOOTH);
  
  glPointSize(10);
  QVector3D v_col(1.0, 0.0, 0.0);

  shader_program_.setUniformValueArray("FragColor", &v_col, 1);
  glDrawArrays(GL_POINTS, 1, 6);
  
  glDisable(GL_POINT_SMOOTH);
  
  vao_.release();
  
  shader_program_.release();
}

}  // namespace s21
