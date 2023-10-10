#include <gtest/gtest.h>
#include "obj_parser.h"


TEST(OBJParserTest, Parse_Positive_first)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("../assets/objects/cube.obj");
  parser.SetObject(&object);
  parser.Parse();

  std::vector<s21::Vertex> vertices = object.GetVertices();
  std::vector<s21::Vertex> correct_vertices =
  {
    {1, -1, -1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, -1, -1},
    {1, 1, -1},
    {1, 1, 1},
    {-1, 1, 1},
    {-1, 1, -1}
  };

  std::vector<s21::Face> faces = object.GetFaces();
  std::vector<s21::Face> correct_faces = 
  {
    {{2, 3, 4}},
    {{8, 7, 6}},
    {{5, 6, 2}},
    {{6, 7, 3}},
    {{3, 7, 8}},
    {{1, 4, 8}},
    {{1, 2, 4}},
    {{5, 8, 6}},
    {{1, 5, 2}},
    {{2, 6, 3}},
    {{4, 3, 8}},
    {{5, 1, 8}}
  };
  // Test if the vertices were parsed correctly
  EXPECT_EQ(object.GetVertexCount(), 8);

  // Test if the faces were parsed correctly
  EXPECT_EQ(object.GetFaceCount(), 12);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

  for (size_t i = 0; i < faces.size(); i++)
  {
    for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
    {
      EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
    }
  }
  object.CountEdges();
  EXPECT_EQ(object.GetEdgeCount(), 18);
}


TEST(OBJParserTest, Parse_Positive_second)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("../assets/objects/cube2.obj");
  parser.SetObject(&object);
  parser.Parse();


  std::vector<s21::Vertex> vertices = object.GetVertices();
  std::vector<s21::Vertex> correct_vertices =
  {
    {1, -1, -1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, -1, -1},
    {1, 1, -0.999999},
    {0.999999, 1, 1.000001},
    {-1, 1, 1},
    {-1, 1, -1}
  };

  std::vector<s21::Face> faces = object.GetFaces();
  std::vector<s21::Face> correct_faces = 
  {
    {{2, 3, 4}},
    {{8, 7, 6}},
    {{5, 6, 2}},
    {{6, 7, 3}},
    {{3, 7, 8}},
    {{1, 4, 8}},
    {{1, 2, 4}},
    {{5, 8, 6}},
    {{1, 5, 2}},
    {{2, 6, 3}},
    {{4, 3, 8}},
    {{5, 1, 8}}
  };
  // Test if the vertices were parsed correctly
  EXPECT_EQ(object.GetVertexCount(), 8);

  // Test if the faces were parsed correctly
  EXPECT_EQ(object.GetFaceCount(), 12);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

  for (size_t i = 0; i < faces.size(); i++)
  {
    for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
    {
      EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
    }
  }
}


TEST(OBJParserTest, Parse_Positive_third)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("../assets/objects/cube3.obj");
  parser.SetObject(&object);
  parser.Parse();

  std::vector<s21::Vertex> vertices = object.GetVertices();
  std::vector<s21::Vertex> correct_vertices =
  {
    {1, -1, -1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, -1, -1},
    {1, 1, -0.999999},
    {0.999999, 1, 1.000001},
    {-1, 1, 1},
    {-1, 1, -1}
  };

  std::vector<s21::Face> faces = object.GetFaces();
  std::vector<s21::Face> correct_faces = 
  {
    {{2, 3, 4}},
    {{8, 7, 6}},
    {{5, 6, 2}},
    {{6, 7, 3}},
    {{3, 7, 8}},
    {{1, 4, 8}},
    {{1, 2, 4}},
    {{5, 8, 6}},
    {{1, 5, 2}},
    {{2, 6, 3}},
    {{4, 3, 8}},
    {{5, 1, 8}}
  };
  // Test if the vertices were parsed correctly
  EXPECT_EQ(object.GetVertexCount(), 8);

  // Test if the faces were parsed correctly
  EXPECT_EQ(object.GetFaceCount(), 12);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

  for (size_t i = 0; i < faces.size(); i++)
  {
    for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
    {
      EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
    }
  }
}


// TEST(OBJParserTest, Parse_Positive_fourth)
// {
//   s21::OBJParser parser{};
//   s21::Object object{};
//   parser.SetFilePath("../assets/objects/cube4.obj");
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

TEST(OBJParserTest, Parse_Positive_five)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("../assets/objects/pyramide.obj");
  parser.SetObject(&object);
  parser.Parse();

  std::vector<s21::Vertex> vertices = object.GetVertices();
  std::vector<s21::Vertex> correct_vertices =
  {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
  };

  std::vector<s21::Face> faces = object.GetFaces();
  std::vector<s21::Face> correct_faces = 
  {
    {{1, 2, 3}},
    {{1, 2, 4}},
    {{2, 3, 4}},
    {{3, 1, 4}},
    {{1, 3, 4}}
  };
  // Test if the vertices were parsed correctly
  EXPECT_EQ(object.GetVertexCount(), 4);

  // Test if the faces were parsed correctly
  EXPECT_EQ(object.GetFaceCount(), 5);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

  for (size_t i = 0; i < faces.size(); i++)
  {
    for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
    {
      EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
    }
  }
  object.CountEdges();
  EXPECT_EQ(object.GetEdgeCount(), 6);
}

TEST(OBJParserTest, Parse_Positive_six)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("../assets/objects/negative_pyramide.obj");
  parser.SetObject(&object);
  parser.Parse();

  std::vector<s21::Vertex> vertices = object.GetVertices();
  std::vector<s21::Vertex> correct_vertices =
  {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
  };

  std::vector<s21::Face> faces = object.GetFaces();
  std::vector<s21::Face> correct_faces = 
  {
    {{1, 2, 3}},
    {{1, 2, 4}},
    {{2, 3, 4}},
    {{3, 1, 4}},
    {{1, 3, 4}}
  };
  // Test if the vertices were parsed correctly
  EXPECT_EQ(object.GetVertexCount(), 4);

  // Test if the faces were parsed correctly
  EXPECT_EQ(object.GetFaceCount(), 5);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

  for (size_t i = 0; i < faces.size(); i++)
  {
    for (size_t j = 0; j < faces[i].vertex_indices.size(); j++)
    {
      EXPECT_EQ(faces[i].vertex_indices[j], correct_faces[i].vertex_indices[j]);
    }
  }
  object.CountEdges();
  EXPECT_EQ(object.GetEdgeCount(), 6);
}


TEST(OBJParserTest, Parse_Negative)
{
  s21::OBJParser parser{};
  s21::Object object{};
  parser.SetFilePath("nonexistent.obj");
  parser.SetObject(&object);
  parser.Parse();

  // Test if the parser handles non-existent file gracefully
  EXPECT_EQ(object.GetVertexCount(), 0);
  EXPECT_EQ(object.GetFaceCount(), 0);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}