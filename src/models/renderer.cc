#include "renderer.h"

void s21::Renderer::InitOpenGL() {
  glEnable(GL_DEPTH_TEST);
}

void s21::Renderer::SetViewPort(int w, int h) {
  glViewport(0, 0, w, h);
}

void s21::Renderer::RenderObject(Object object, Transform transform) {
  
}