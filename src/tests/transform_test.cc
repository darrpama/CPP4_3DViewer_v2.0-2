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

TEST(TransformTest, ApplyRotationXPositiveAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{0, 1, 0},
    s21::Vertex{0, 0, 1},
    s21::Vertex{0, -1, 0}
  };
  object.SetVertices(vertices);
  float angle = 0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationX(angle);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{0, cos(angle), sin(angle)},
    s21::Vertex{0, -sin(angle), cos(angle)},
    s21::Vertex{0, -cos(angle), -sin(angle)}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyRotationXNegativeAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{0, 1, 0},
    s21::Vertex{0, 0, 1},
    s21::Vertex{0, -1, 0}
  };
  object.SetVertices(vertices);
  float angle = -0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationX(angle);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{0, cos(angle), sin(angle)},
    s21::Vertex{0, -sin(angle), cos(angle)},
    s21::Vertex{0, -cos(angle), -sin(angle)}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyRotationYPositiveAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 0, 0},
    s21::Vertex{0, 0, 1},
    s21::Vertex{-1, 0, 0}
  };
  object.SetVertices(vertices);
  float angle = 0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationY(angle);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{cos(angle), 0, -sin(angle)},
    s21::Vertex{sin(angle), 0, cos(angle)},
    s21::Vertex{-cos(angle), 0, sin(angle)}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyRotationYNegativeAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 0, 0},
    s21::Vertex{0, 0, 1},
    s21::Vertex{-1, 0, 0}
  };
  object.SetVertices(vertices);
  float angle = -0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationY(angle);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{cos(angle), 0, -sin(angle)},
    s21::Vertex{sin(angle), 0, cos(angle)},
    s21::Vertex{-cos(angle), 0, sin(angle)}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyRotationZPositiveAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 0, 0},
    s21::Vertex{0, 1, 0},
    s21::Vertex{0, 0, 1}
  };
  object.SetVertices(vertices);
  float angle = 0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationZ(angle);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{cos(angle), sin(angle), 0},
    s21::Vertex{-sin(angle), cos(angle), 0},
    s21::Vertex{0, 0, 1}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyRotationZNegativeAngle) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 0, 0},
    s21::Vertex{0, 1, 0},
    s21::Vertex{0, 0, 1}
  };
  object.SetVertices(vertices);
  float angle = -0.5;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyRotationZ(angle);

  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{cos(angle), sin(angle), 0},
   s21::Vertex{-sin(angle), cos(angle), 0},
    s21::Vertex{0, 0, 1}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}


TEST(TransformTest, ApplyScalePositiveK) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 2, 3},
    s21::Vertex{4, 5, 6},
    s21::Vertex{7, 8, 9}
  };
  object.SetVertices(vertices);
  float k = 2.0;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyScale(k);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{2, 4, 6},
    s21::Vertex{8, 10, 12},
    s21::Vertex{14, 16, 18}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}

TEST(TransformTest, ApplyScaleNegativeK) {
  s21::Object object;
  std::vector<s21::Vertex> vertices = {
    s21::Vertex{1, 2, 3},
   s21::Vertex{4, 5, 6},
    s21::Vertex{7, 8, 9}
  };
  object.SetVertices(vertices);
  float k = -2.0;
  s21::Transform transform;
  transform.SetObject(&object);
  transform.ApplyScale(k);
  std::vector<s21::Vertex> expected_vertices = {
    s21::Vertex{-2, -4, -6},
    s21::Vertex{-8, -10, -12},
    s21::Vertex{-14, -16, -18}
  };
  EXPECT_TRUE(compareVertices(object.GetVertices(), expected_vertices));
}


bool compareVertices(std::vector<s21::Vertex> v1, std::vector<s21::Vertex> v2) {
    bool res = true;
    for (size_t i = 0; i < v1.size() && res; ++i) {
        res = (v1[i].x == v2[i].x && v1[i].y == v2[i].y && v1[i].z == v2[i].z);
    }
    return res;
}

// void print_vector(std::vector<s21::Vertex> expected_vertices, s21::Object &object) {
//   std::cout << "Expected vector\n";
//   for (auto elem : expected_vertices) {
//     std::cout << elem.x << " " << elem.y << " " << elem.z << std::endl; 
//   }

//   std::cout << "Object vector\n";
//   for (auto elem : object.GetVertices()) {
//     std::cout << elem.x << " " << elem.y << " " << elem.z << std::endl; 
//   }
// }