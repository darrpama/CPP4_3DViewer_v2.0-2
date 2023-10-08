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
  glFrustum(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, 1.0, 20.0);

  glTranslatef(0, 0, -5);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderObject(Object *object) {
  SetProjectionMatrix();

  // set matrix for model view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(1, 1, 0, 0);
  glRotatef(1, 0, 1, 0);
  

  std::vector<Vertex> vertices = object->GetVertices();

  //   float vertices[] = {
  //   -0.5f, -0.5f, 0.0f,
  //    0.5f, -0.5f, 0.0f,
  //    0.0f,  0.5f, 0.0f
  // };


  // Create Vertex buffer object
  unsigned int vbo;
  glGenBuffers(1, &vbo);

  // Create Vertex array object
  unsigned int vao;
  glGenVertexArrays(1, &vao);

  // Set our buffer to specialized type of buffer object. Here we use GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);

  // Set our data to buffer
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  // Now, any buffer calls we make (on the GL_ARRAY_BUFFER target) 
  // will be used to configure the currently bound buffer, which is "vbo"
  

  // CREATE VERTEX SHADER
  // ---------------------------------------------------------------
  // Shader source code
  const char *vertex_shader_source = "#version 120\n"
    "attribute vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

  // Create specified type of shader
  unsigned int vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  // Compile shader
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);


  // CREATE FRAGMENT SHADER
  // ---------------------------------------------------------------
  const char *fragment_shader_source = 
    "#version 120\n"
    "varying vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);


  // CREATE SHADER PROGRAM
  // ---------------------------------------------------------------
  unsigned int shader_program;
  shader_program = glCreateProgram();

  // link our shaders to our program
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  // Activate shader program
  glUseProgram(shader_program);

  // DRAW 
  // ---------------------------------------------------------------
  // After linkning we do not need a shader objects
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  // now we need to explain to vertex shader how to iterpret our data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);
  
  // use our shader program when we want to render an object
  glUseProgram(shader_program);
  
  // use our vao
  glBindVertexArray(vao);

  glDrawArrays(GL_POINTS, 0, vertices.size());
}

}  // namespace s21
