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
  
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

  // Check if shader compilation is succesfull
  int  vertex_shader_success;
  char vertex_info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_success);

  if(!vertex_shader_success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, vertex_info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_info_log << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
  }


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

  int  fragment_shader_success;
  char fragment_info_log[512];
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_success);

  if(!fragment_shader_success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << fragment_info_log << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
  }


  // CREATE SHADER PROGRAM
  // ---------------------------------------------------------------
  unsigned int shader_program;
  shader_program = glCreateProgram();

  // link our shaders to our program
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  // Check if linkings successfully
  int  shader_program_success;
  char program_info_log[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_success);
  if(!shader_program_success) {
    glGetProgramInfoLog(shader_program, 512, NULL, program_info_log);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << fragment_info_log << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
  }

  // Activate shader program
  glUseProgram(shader_program);


  // DRAW 
  // After linkning we do not need a shader objects
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // now we need to explain to vertex shader how to iterpret our data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  // use our shader program when we want to render an object
  glUseProgram(shader_program);
  
  // use our vao
  glBindVertexArray(vao);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::DrawVertices(std::vector<Vertex> *vertices) {
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glEnable(GL_PROGRAM_POINT_SIZE);
  // glVertexPointer(3, GL_DOUBLE, 0, vertices->data());
  
  // glPushMatrix();
  //   glScalef(100.0f, 100.0f, 100.0f);
  //   glColor3f(1.0, 0.0, 0.0); // TODO: hardcoded color
  //   glPointSize(6);           // TODO: hardcoded size
  //   glDrawArrays(GL_POINTS, 0, vertices->size());
  // glPopMatrix();

  // glDisable(GL_PROGRAM_POINT_SIZE);
  // glDisableClientState(GL_VERTEX_ARRAY);
}

}  // namespace s21
