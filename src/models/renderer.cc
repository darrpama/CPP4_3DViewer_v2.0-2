#include "renderer.h"

namespace s21 {

Renderer::Renderer() {}

Renderer::~Renderer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteProgram(shader_program);
}

// types:
// 1 - GL_VERTEX_SHADER
// 2 - GL_FRAGMENT_SHADER
unsigned int Renderer::CreateShaderFromSource(int type, const char *source) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  return shader;
}

void Renderer::InitOpenGL(Object *object) {
  object_ = object;
  glEnable(GL_DEPTH_TEST);

  // vertex shader
  const char *vertex_shader_source = "#version 120\n"
    "attribute vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
  unsigned int vertex_shader = CreateShaderFromSource(GL_VERTEX_SHADER, vertex_shader_source);

  // fragment shader
  const char *fragment_shader_source = "#version 120\n"
    "varying vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1.0f, 0.0f, 0.2f, 1.0f);\n"
    "}\0";
  unsigned int fragment_shader = CreateShaderFromSource(GL_FRAGMENT_SHADER, fragment_shader_source);

  // link our shaders to our program
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  // After linkning we do not need a shader objects
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  float *vertices2 = object->GetVerticesAsArray();
  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };

  std::cout << sizeof(vertices) << std::endl;
  std::cout << sizeof(vertices) << std::endl;
  std::cout << object_->GetVertexCount() * sizeof(float) * 3 << std::endl;

  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };  
  // std::vector<Vertex> vertices = object->GetVertices();

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  // glGenBuffers(1, &ebo);
  
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, object_->GetVertexCount() * sizeof(float) * 3, vertices2, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
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
  // SetProjectionMatrix();
  // use our shader program when we want to render an object
  glUseProgram(shader_program);
  glBindVertexArray(vao);

  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  glPointSize(10.0f);

  glDrawArrays(GL_POINTS, 0, object_->GetVertexCount());
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

}  // namespace s21
