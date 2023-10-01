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

void s21::Renderer::RenderObject(Object object, Transform transform) {
  (void) object;
  (void) transform;
  SetProjectionMatrix();
  // glClearColor(red_bg / 255.0f, green_bg / 255.0f, blue_bg / 255.0f, alpha_bg);

  // set matrix for model view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  // glRotatef(rotationX_, 0, 1, 0);
  // glRotatef(rotationY_, 1, 0, 0);

  // Render your cube using OpenGL functions
  glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glVertex3f(-0.5, 0.5, -0.5); // Top left front
    glVertex3f(0.5, 0.5, -0.5); // Top right front
    glVertex3f(0.5, -0.5, -0.5); // Bottom right front
    glVertex3f(-0.5, -0.5, -0.5); // Bottom left front

    glColor3f(0.0, 0.5, 0.0); // Set the color to green
    glVertex3f(-0.5, 0.5, 0.5); // Top left back
    glVertex3f(0.5, 0.5, 0.5); // Top right back
    glVertex3f(0.5, -0.5, 0.5); // Bottom right back
    glVertex3f(-0.5, -0.5, 0.5); // Bottom left back

    glColor3f(0.0, 0.0, 0.5); // Set the color to blue
    glVertex3f(-0.5, 0.5, -0.5); // Top left front
    glVertex3f(-0.5, -0.5, -0.5); // Bottom left front
    glVertex3f(-0.5, -0.5, 0.5); // Bottom left back
    glVertex3f(-0.5, 0.5, 0.5); // Top left back

    glColor3f(0.5, 0.5, 0.0); // Set the color to yellow
    glVertex3f(0.5, 0.5, -0.5); // Top right front
    glVertex3f(0.5, -0.5, -0.5); // Bottom right front
    glVertex3f(0.5, -0.5, 0.5); // Bottom right back
    glVertex3f(0.5, 0.5, 0.5); // Top right back

    glColor3f(0.5, 0.0, 0.5); // Set the color to magenta
    glVertex3f(-0.5, 0.5, -0.5); // Top left front
    glVertex3f(-0.5, 0.5, 0.5); // Top left back
    glVertex3f(0.5, 0.5, 0.5); // Top right back
    glVertex3f(0.5, 0.5, -0.5); // Top right front

    glColor3f(0.0, 0.5, 0.5); // Set the color to cyan
    glVertex3f(-0.5, -0.5, -0.5); // Bottom left front
    glVertex3f(-0.5, -0.5, 0.5); // Bottom left back
    glVertex3f(0.5, -0.5, 0.5); // Bottom right back
    glVertex3f(0.5, -0.5, -0.5); // Bottom right front
  glEnd();
}