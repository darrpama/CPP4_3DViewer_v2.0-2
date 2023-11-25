#include <gtest/gtest.h>
#include "../models/obj_parser.h"


TEST(OBJParserTest, Parse_Positive_first)
{
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer, &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  parser.SetFilePath("/Users/darrpama/projects/CPP4_3DViewer_v2.0-2/src/assets/objects/cube.obj");
  parser.Parse();

  std::vector<GLfloat> correct_vertices =
  {
    1, -1, -1,
    1, -1, 1,
    -1, -1, 1,
    -1, -1, -1,
    1, 1, -1,
    1, 1, 1,
    -1, 1, 1,
    -1, 1, -1
  };

  std::vector<GLuint> correct_faces = 
  {
    2, 3, 4,
    8, 7, 6,
    5, 6, 2,
    6, 7, 3,
    3, 7, 8,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    1, 5, 2,
    2, 6, 3,
    4, 3, 8,
    5, 1, 8
  };
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 8;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 12;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++)
  {
    EXPECT_EQ(faces[i], correct_faces[i] - 1);
    // std::cout << "parsed: " << faces[i].vertices[j] << " correct: " << correct_faces[i].vertices[j] << std::endl;
  }
  object.CountEdges();
  size_t correct_edges_num = 18;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}


TEST(OBJParserTest, Parse_Negative_first)
{
  std::vector<GLfloat> vertices_array;
  std::vector<GLuint> faces_array;
  std::vector<s21::Face> raw_faces_array_;
  std::vector<GLuint> face_buffer;
  std::vector<GLuint> triangle_buffer;

  s21::Object object = s21::Object(&vertices_array, &faces_array, &face_buffer, &triangle_buffer, &raw_faces_array_);
  s21::OBJParser parser(&object);
  parser.SetFilePath("/Users/darrpama/projects/CPP4_3DViewer_v2.0-2/src/assets/objects/incorrect/invalid_pretoken.obj");
  parser.Parse();

  std::vector<GLfloat> correct_vertices =
  {
    0.5000000, 0.500000, -0.500000,
    0.5000000,-0.500000, -0.500000,
    0.5000000, 0.500000, 0.500000,
    0.5000000, -0.5000000, 0.500000,
    -0.5000000, 0.5000000, -0.500000,
    -0.5000000, -0.5000000, -0.500000,
    -0.5000000, 0.5000000, 0.500000,
    -0.5000000, -0.5000000, 0.500000
  };

  std::vector<GLuint> correct_faces = 
  {
    4294967295, 4, 6,
    4294967295, 6, 2,
    3, 2, 6,
    3, 6, 7,
    7, 6, 4,
    7, 4, 5,
    5, 1, 3,
    5, 3, 7,
    1, 0, 2,
    1, 2, 3,
    5, 4, 0,
    5, 0, 1
  };
  // Test if the vertices were parsed correctly
  size_t correct_vertices_num = 8;
  EXPECT_EQ(object.GetVertexCount(), correct_vertices_num);

  // Test if the faces were parsed correctly
  size_t correct_faces_num = 6;
  EXPECT_EQ(object.GetFaceCount(), correct_faces_num);

  std::vector<GLfloat> vertices = object.GetFlattenedVertices();
  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i], correct_vertices[i]);
  }

  std::vector<GLuint> faces = object.GetFlattenedFaces();
  for (size_t i = 0; i < faces.size(); i++)
  {
    EXPECT_EQ(faces[i], correct_faces[i]);
    // std::cout << "parsed: " << faces[i] << " correct: " << correct_faces[i] << std::endl;
  }
  object.CountEdges();
  size_t correct_edges_num = 14;
  EXPECT_EQ(object.GetEdgeCount(), correct_edges_num);
}


// TEST(OBJParserTest, Parse_Positive_second)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("../assets/objects/cube2.obj");
//   parser.SetObject(&object);
//   parser.Parse();


//   std::vector<s21::Vertex> vertices = object.GetVertices();
//   std::vector<s21::Vertex> correct_vertices =
//   {
//     {1, -1, -1},
//     {1, -1, 1},
//     {-1, -1, 1},
//     {-1, -1, -1},
//     {1, 1, -0.999999},
//     {0.999999, 1, 1.000001},
//     {-1, 1, 1},
//     {-1, 1, -1}
//   };

//   std::vector<s21::Face> faces = object.GetFaces();
//   std::vector<s21::Face> correct_faces = 
//   {
//     {{2, 3, 4}},
//     {{8, 7, 6}},
//     {{5, 6, 2}},
//     {{6, 7, 3}},
//     {{3, 7, 8}},
//     {{1, 4, 8}},
//     {{1, 2, 4}},
//     {{5, 8, 6}},
//     {{1, 5, 2}},
//     {{2, 6, 3}},
//     {{4, 3, 8}},
//     {{5, 1, 8}}
//   };
//   // Test if the vertices were parsed correctly
//   EXPECT_EQ(object.GetVertexCount(), 8);

//   // Test if the faces were parsed correctly
//   EXPECT_EQ(object.GetFaceCount(), 12);

//   for (size_t i = 0; i < vertices.size(); i++)
//   {
//     EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
//     EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
//     EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
//   }

//   for (size_t i = 0; i < faces.size(); i++)
//   {
//     for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
//     {
//       EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
//     }
//   }
// }


// TEST(OBJParserTest, Parse_Positive_third)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("../assets/objects/cube3.obj");
//   parser.SetObject(&object);
//   parser.Parse();

//   std::vector<s21::Vertex> vertices = object.GetVertices();
//   std::vector<s21::Vertex> correct_vertices =
//   {
//     {1, -1, -1},
//     {1, -1, 1},
//     {-1, -1, 1},
//     {-1, -1, -1},
//     {1, 1, -0.999999},
//     {0.999999, 1, 1.000001},
//     {-1, 1, 1},
//     {-1, 1, -1}
//   };

//   std::vector<s21::Face> faces = object.GetFaces();
//   std::vector<s21::Face> correct_faces = 
//   {
//     {{2, 3, 4}},
//     {{8, 7, 6}},
//     {{5, 6, 2}},
//     {{6, 7, 3}},
//     {{3, 7, 8}},
//     {{1, 4, 8}},
//     {{1, 2, 4}},
//     {{5, 8, 6}},
//     {{1, 5, 2}},
//     {{2, 6, 3}},
//     {{4, 3, 8}},
//     {{5, 1, 8}}
//   };
//   // Test if the vertices were parsed correctly
//   EXPECT_EQ(object.GetVertexCount(), 8);

//   // Test if the faces were parsed correctly
//   EXPECT_EQ(object.GetFaceCount(), 12);

//   for (size_t i = 0; i < vertices.size(); i++)
//   {
//     EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
//     EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
//     EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
//   }

//   for (size_t i = 0; i < faces.size(); i++)
//   {
//     for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
//     {
//       EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
//     }
//   }
// }


// // TEST(OBJParserTest, Parse_Positive_fourth)
// // {
// //   s21::OBJParser parser{};
// //   s21::Object object{};
// //   parser.SetFilePath("../assets/objects/cube4.obj");
// //   parser.SetObject(&object);
// //   parser.Parse();

// //   std::vector<s21::Vertex> vertices = object.GetVertices();
// //   std::vector<s21::Vertex> correct_vertices =
// //   {
// //     {1, -1, -1},
// //     {1, -1, 1},
// //     {-1, -1, 1},
// //     {-1, -1, -1},
// //     {1, 1, -0.999999},
// //     {0.999999, 1, 1.000001},
// //     {-1, 1, 1},
// //     {-1, 1, -1}
// //   };

// //   std::vector<s21::Face> faces = object.GetFaces();
// //   std::vector<s21::Face> correct_faces = 
// //   {
// //     {{2, 3, 4}},
// //     {{8, 7, 6}},
// //     {{5, 6, 2}},
// //     {{6, 7, 3}},
// //     {{3, 7, 8}},
// //     {{1, 4, 8}},
// //     {{1, 2, 4}},
// //     {{5, 8, 6}},
// //     {{1, 5, 2}},
// //     {{2, 6, 3}},
// //     {{4, 3, 8}},
// //     {{5, 1, 8}}
// //   };
// //   // Test if the vertices were parsed correctly
// //   EXPECT_EQ(object.GetVertexCount(), 8);

// //   // Test if the faces were parsed correctly
// //   EXPECT_EQ(object.GetFaceCount(), 12);

// //   for (size_t i = 0; i < vertices.size(); i++)
// //   {
// //     EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
// //     EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
// //     EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
// //   }

// //   for (size_t i = 0; i < faces.size(); i++)
// //   {
// //     for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
// //     {
// //       EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
// //     }
// //   }
// // }

// TEST(OBJParserTest, Parse_Positive_five)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("../assets/objects/pyramide.obj");
//   parser.SetObject(&object);
//   parser.Parse();

//   std::vector<s21::Vertex> vertices = object.GetVertices();
//   std::vector<s21::Vertex> correct_vertices =
//   {
//     {0, 0, 0},
//     {1, 0, 0},
//     {0, 1, 0},
//     {0, 0, 1},
//   };

//   std::vector<s21::Face> faces = object.GetFaces();
//   std::vector<s21::Face> correct_faces = 
//   {
//     {{1, 2, 3}},
//     {{1, 2, 4}},
//     {{2, 3, 4}},
//     {{3, 1, 4}},
//     {{1, 3, 4}}
//   };
//   // Test if the vertices were parsed correctly
//   EXPECT_EQ(object.GetVertexCount(), 4);

//   // Test if the faces were parsed correctly
//   EXPECT_EQ(object.GetFaceCount(), 5);

//   for (size_t i = 0; i < vertices.size(); i++)
//   {
//     EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
//     EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
//     EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
//   }

//   for (size_t i = 0; i < faces.size(); i++)
//   {
//     for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
//     {
//       EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
//     }
//   }
//   object.CountEdges();
//   EXPECT_EQ(object.GetEdgeCount(), 6);
// }

// TEST(OBJParserTest, Parse_Positive_six)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("../assets/objects/negative_pyramide.obj");
//   parser.SetObject(&object);
//   parser.Parse();

//   std::vector<s21::Vertex> vertices = object.GetVertices();
//   std::vector<s21::Vertex> correct_vertices =
//   {
//     {0, 0, 0},
//     {1, 0, 0},
//     {0, 1, 0},
//     {0, 0, 1},
//   };

//   std::vector<s21::Face> faces = object.GetFaces();
//   std::vector<s21::Face> correct_faces = 
//   {
//     {{1, 2, 3}},
//     {{1, 2, 4}},
//     {{2, 3, 4}},
//     {{3, 1, 4}},
//     {{1, 3, 4}}
//   };
//   // Test if the vertices were parsed correctly
//   EXPECT_EQ(object.GetVertexCount(), 4);

//   // Test if the faces were parsed correctly
//   EXPECT_EQ(object.GetFaceCount(), 5);

//   for (size_t i = 0; i < vertices.size(); i++)
//   {
//     EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
//     EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
//     EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
//   }

//   for (size_t i = 0; i < faces.size(); i++)
//   {
//     for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
//     {
//       EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
//     }
//   }
//   object.CountEdges();
//   EXPECT_EQ(object.GetEdgeCount(), 6);
// }


// TEST(OBJParserTest, Parse_Negative)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("nonexistent.obj");
//   parser.SetObject(&object);
//   parser.Parse();

//   // Test if the parser handles non-existent file gracefully
//   EXPECT_EQ(object.GetVertexCount(), 0);
//   EXPECT_EQ(object.GetFaceCount(), 0);
// }
