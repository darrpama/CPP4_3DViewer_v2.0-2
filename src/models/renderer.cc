#include "renderer.h"

void s21::Renderer::InitOpenGL() {
  glEnable(GL_DEPTH_TEST);
}

void s21::Renderer::SetViewPort(int w, int h) {
  glViewport(0, 0, w, h);
  width_ = w;
  height_ = h;
}

void s21::Renderer::SetProjectionMatrix() {
  // set matrix for projection
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1, 10);
  // glFrustum(-1, 1, -1, 1, 0, 10);
  float aspectRatio = static_cast<float>(width_) / height_;
  glFrustum(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, 1.0, 10.0);
}

void s21::Renderer::RenderObject(Object *object) {
  std::cout << "Renderer: " << object->GetVertices().size() << std::endl;

  SetProjectionMatrix();
  // glClearColor(red_bg / 255.0f, green_bg / 255.0f, blue_bg / 255.0f, alpha_bg);

  // set matrix for model view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  
  // Render only vertices of cube using OpenGL functions
  std::vector<s21::Vertex> vertices = object->GetVertices();   
  glEnable(GL_PROGRAM_POINT_SIZE);
  
  glBegin(GL_POINTS);  // TODO: hardcoded type of vertex
  
  glPointSize(10.0f);  // TODO: hardcoded size
  
  glColor3f(1.0, 0.0, 0.0); // TODO: hardcoded color
  
  for (auto& vertex: vertices) {
    glVertex3f(vertex.x, vertex.y, vertex.z);
    std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
  }
  glEnd();
}