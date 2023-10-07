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

namespace s21 {
void Renderer::InitOpenGL() {
  glEnable(GL_DEPTH_TEST);
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
  // glOrtho(-1, 1, -1, 1, -1, 10);
  // glFrustum(-1, 1, -1, 1, 0, 10);
  float aspectRatio = static_cast<float>(width_) / height_;
  glFrustum(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, 1.0, 10.0);

  glTranslatef(0, 0, -5);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderObject(Object *object) {
  SetProjectionMatrix();
  // glClearColor(red_bg / 255.0f, green_bg / 255.0f, blue_bg / 255.0f, alpha_bg);

  // set matrix for model view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(1, 1, 0, 0);
  glRotatef(1, 0, 1, 0);
  
  std::vector<Vertex> vertices = object->GetVertices();
  DrawVertices(&vertices);

}

void Renderer::DrawVertices(std::vector<Vertex> *vertices) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glVertexPointer(3, GL_DOUBLE, 0, vertices->data());
  
  glPushMatrix();
    glScalef(100.0f, 100.0f, 100.0f);
    glColor3f(1.0, 0.0, 0.0); // TODO: hardcoded color
    glPointSize(6);           // TODO: hardcoded size
    glDrawArrays(GL_POINTS, 0, vertices->size());
  glPopMatrix();

  glDisable(GL_PROGRAM_POINT_SIZE);
  glDisableClientState(GL_VERTEX_ARRAY);
}

}  // namespace s21
