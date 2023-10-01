#include <gtest/gtest.h>
#include "obj_parser.h"


TEST(OBJParserTest, Parse_Positive)
{
  s21::OBJParser parser("../assets/objects/cube.obj");
  parser.Parse();
  s21::Object object = parser.GetObject();
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

  // Test if the vertices were parsed correctly
  EXPECT_EQ(parser.GetVertexCount(), 8);

  // Test if the faces were parsed correctly
  EXPECT_EQ(parser.GetFaceCount(), 12);

  for (size_t i = 0; i < vertices.size(); i++)
  {
    EXPECT_FLOAT_EQ(vertices[i].x, correct_vertices[i].x);
    EXPECT_FLOAT_EQ(vertices[i].y, correct_vertices[i].y);
    EXPECT_FLOAT_EQ(vertices[i].z, correct_vertices[i].z);
  }

}

TEST(OBJParserTest, Parse_Negative)
{
  s21::OBJParser parser("nonexistent.obj");
  parser.Parse();

  // Test if the parser handles non-existent file gracefully
  EXPECT_EQ(parser.GetVertexCount(), 0);
  EXPECT_EQ(parser.GetFaceCount(), 0);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}