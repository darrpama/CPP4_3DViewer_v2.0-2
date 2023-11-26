#include <gtest/gtest.h>

#include <filesystem>

#include "../models/obj_parser.h"

TEST(OBJParserTest, Parse_Positive_first) {
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer,
                                   &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/objects/cube.obj");

  parser.SetFilePath(parent_path);
  parser.Parse();

  std::vector<GLfloat> correct_vertices = {1, -1, -1, 1,  -1, 1,  -1, -1,
                                           1, -1, -1, -1, 1,  1,  -1, 1,
                                           1, 1,  -1, 1,  1,  -1, 1,  -1};

  std::vector<GLuint> correct_faces = {2, 3, 4, 8, 7, 6, 5, 6, 2, 6, 7, 3,
                                       3, 7, 8, 1, 4, 8, 1, 2, 4, 5, 8, 6,
                                       1, 5, 2, 2, 6, 3, 4, 3, 8, 5, 1, 8};
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 8;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 12;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++) {
    EXPECT_EQ(faces[i], correct_faces[i] - 1);
  }
  object.CountEdges();
  size_t correct_edges_num = 18;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);

  size_t correct_triangle_buffer_size = 0;
  EXPECT_EQ(object.GetTriangleBufferSize(), correct_triangle_buffer_size);

  std::vector<s21::Face> faces2 = object.GetFaces();
  size_t correct_faces_size = 12;
  EXPECT_EQ(faces2.size(), correct_faces_size);

  object.Normalize();
  std::vector<GLfloat> vertices_normalized = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices_normalized.size(); i++) {
    EXPECT_FLOAT_EQ(vertices_normalized[i], correct_vertices[i]);
  }

  object.Clear();
}

TEST(OBJParserTest, Parse_Positive_second) {
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer,
                                   &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/objects/cube_no_last_line.obj");

  parser.SetFilePath(parent_path);
  parser.Parse();

  std::vector<GLfloat> correct_vertices = {1, -1, -1, 1,  -1, 1,  -1, -1,
                                           1, -1, -1, -1, 1,  1,  -1, 1,
                                           1, 1,  -1, 1,  1,  -1, 1,  -1};

  std::vector<GLuint> correct_faces = {2, 3, 4, 8, 7, 6, 5, 6, 2, 6, 7, 3,
                                       3, 7, 8, 1, 4, 8, 1, 2, 4, 5, 8, 6,
                                       1, 5, 2, 2, 6, 3, 4, 3, 8, 5, 1, 8};
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 8;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 12;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++) {
    EXPECT_EQ(faces[i], correct_faces[i] - 1);
  }
  object.CountEdges();
  size_t correct_edges_num = 18;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}

TEST(OBJParserTest, Parse_Positive_third) {
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer,
                                   &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/objects/equal.obj");

  parser.SetFilePath(parent_path);
  parser.Parse();

  std::vector<GLfloat> correct_vertices = {1, 2, 3, 2, 3, 4};

  std::vector<GLuint> correct_faces = {1, 2};
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 2;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 1;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++) {
    EXPECT_EQ(faces[i], correct_faces[i] - 1);
  }
  object.CountEdges();
  size_t correct_edges_num = 1;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}

TEST(OBJParserTest, Parse_Positive_fourth) {
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer,
                                   &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/objects/skull.obj");

  parser.SetFilePath(parent_path);
  parser.Parse();

  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 6122;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 9537;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  object.CountEdges();
  size_t correct_edges_num = 16223;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}

TEST(OBJParserTest, Parse_Negative_first) {
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer,
                                   &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/objects/incorrect/invalid_pretoken.obj");

  parser.SetFilePath(parent_path);
  parser.Parse();

  std::vector<GLfloat> correct_vertices = {
      0.5000000,  0.500000,  -0.500000, 0.5000000,  -0.500000,  -0.500000,
      0.5000000,  0.500000,  0.500000,  0.5000000,  -0.5000000, 0.500000,
      -0.5000000, 0.5000000, -0.500000, -0.5000000, -0.5000000, -0.500000,
      -0.5000000, 0.5000000, 0.500000,  -0.5000000, -0.5000000, 0.500000};

  std::vector<GLuint> correct_faces = {
      4294967295, 4, 6, 4294967295, 6, 2, 3, 2, 6, 3, 6, 7, 7, 6, 4, 7, 4, 5,
      5,          1, 3, 5,          3, 7, 1, 0, 2, 1, 2, 3, 5, 4, 0, 5, 0, 1};
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 8;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 6;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++) {
    EXPECT_EQ(faces[i], correct_faces[i]);
  }
  object.CountEdges();
  size_t correct_edges_num = 14;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}

// TEST(OBJParserTest, Parse_Negative_second)
// {
//   std::vector<GLfloat> vertices_array;
//   std::vector<GLuint> faces_array;
//   std::vector<s21::Face> raw_faces_array_;
//   std::vector<GLuint> face_buffer;
//   std::vector<GLuint> triangle_buffer;

//   s21::Object object = s21::Object(&vertices_array, &faces_array,
//   &face_buffer, &triangle_buffer, &raw_faces_array_); s21::OBJParser
//   parser(&object);

//   std::filesystem::path path = std::filesystem::current_path();
//   std::string parent_path = path.parent_path();
//   parent_path.append("/src/assets/objects/incorrect/nonexist.obj");

//   parser.SetFilePath(parent_path);
//   parser.Parse();

//   // Test if the vertices were parsed correctly
//   size_t correct_vertices_num = 0;
//   EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

//   // Test if the faces were parsed correctly
//   size_t correct_faces_num = 0;
//   EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

//   object.CountEdges();
//   size_t correct_edges_num = 0;
//   EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
// }
