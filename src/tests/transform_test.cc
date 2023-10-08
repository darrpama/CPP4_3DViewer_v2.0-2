#include <gtest/gtest.h>
#include <iostream>

#include "../models/transform.h"

bool compareVertices(std::vector<s21::Vertex> v1, std::vector<s21::Vertex> v2);

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TransformTest, ApplyTranslationXTrueTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationX(2.0);
  std::vector<s21::Vertex> expected_vertices = {s21::Vertex{3, 2, 3}, s21::Vertex{6, 5, 6}};
  EXPECT_TRUE(compareVertices(obj.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyTranslationXFalseTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationX(2.0);
  std::vector<s21::Vertex> unexpected_vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  EXPECT_FALSE(compareVertices(obj.GetVertices(), unexpected_vertices));
}


TEST(TransformTest, ApplyTranslationYTrueTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationY(2.0);
  std::vector<s21::Vertex> expected_vertices = {s21::Vertex{1, 4, 3}, s21::Vertex{4, 7, 6}};
  EXPECT_TRUE(compareVertices(obj.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyTranslationYFalseTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationY(2.0);
  std::vector<s21::Vertex> unexpected_vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  EXPECT_FALSE(compareVertices(obj.GetVertices(), unexpected_vertices));
}

TEST(TransformTest, ApplyTranslationZTrueTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationZ(2.0);
  std::vector<s21::Vertex> expected_vertices = {s21::Vertex{1, 2, 5}, s21::Vertex{4, 5, 8}};
  EXPECT_TRUE(compareVertices(obj.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyTranslationZFalseTest) {
  s21::Object obj;
  std::vector<s21::Vertex> vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  obj.SetVertices(vertices);
  s21::Transform transform;
  transform.SetObject(&obj);
  transform.ApplyTranslationZ(2.0);
  std::vector<s21::Vertex> unexpected_vertices = {s21::Vertex{1, 2, 3}, s21::Vertex{4, 5, 6}};
  EXPECT_FALSE(compareVertices(obj.GetVertices(), unexpected_vertices));
}


bool compareVertices(std::vector<s21::Vertex> v1, std::vector<s21::Vertex> v2) {
    bool res = true;
    for (size_t i = 0; i < v1.size() && res; ++i) {
        res = (v1[i].x == v2[i].x && v1[i].y == v2[i].y && v1[i].z == v2[i].z);
    }
    return res;
}