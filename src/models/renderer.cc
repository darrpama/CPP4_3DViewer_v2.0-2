#include "renderer.h"

// DEV VERSION
// NOT READY
// TODO:
//    - fix bug with only dot. It renders only one dot
//    - 
//    - 
//    - 
//    - 
//    - 
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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1, 10);
  // glFrustum(-1, 1, -1, 1, 0, 10);
  float aspectRatio = static_cast<float>(width_) / height_;
  // glFrustum(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, 1.0, 10.0);
  glFrustum(-1, 1, -1, 1, 1, 1000000);

  glTranslatef(0, 0, -5);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void s21::Renderer::RenderObject(Object *object) {
  SetProjectionMatrix();
  // glClearColor(red_bg / 255.0f, green_bg / 255.0f, blue_bg / 255.0f, alpha_bg);

  // set matrix for model view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // glRotatef(1, 1, 0, 0);
  // glRotatef(1, 0, 1, 0);
  
  std::vector<s21::Vertex> vertices = object->GetVertices();
  glVertexPointer(3, GL_DOUBLE, 0, &vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glColor3f(1.0, 0.0, 0.0); // TODO: hardcoded color
  glPointSize(30);  // TODO: hardcoded size
  glDrawArrays(GL_POINTS, 1, vertices.size());
  
  // glEnable(GL_PROGRAM_POINT_SIZE);
  glDisableClientState(GL_VERTEX_ARRAY);
}


