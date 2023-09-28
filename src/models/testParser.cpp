#include <gtest/gtest.h>
#include "OBJParser.h"

//  TO DO: add vertex count and getter for it
//  Write a first test!!

TEST(OBJParserTest, Parse_Positive)
{
  s21::OBJParser parser("../assets/objects/cube.obj");
  parser.Parse();

  // Test if the vertices were parsed correctly
  EXPECT_EQ(parser.GetVertexCount(), 3);

  // Test if the faces were parsed correctly
  EXPECT_EQ(parser.GetFaceCount(), 1);
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