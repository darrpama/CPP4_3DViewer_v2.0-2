#include "../models/transform.h"

#include <gtest/gtest.h>

#include <iostream>

bool compareMatrices(s21::Matrix4x4& m1, s21::Matrix4x4& m2);
void printMatrix(s21::Matrix4x4& matrix);

TEST(TransformTest, ApplyTranslationXTrueTest) {
  s21::Matrix4x4 expected_matrix(1.0f, 0.0f, 0.0f, 1.056, 0.0f, 1.0f, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetTranslationX(1.056f);
  transform.UpdateTranslationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyTranslationYTrueTest) {
  s21::Matrix4x4 expected_matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 1.056, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                                 0.0f, 1.0f);

  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetTranslationY(1.056f);
  transform.UpdateTranslationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyTranslationZTrueTest) {
  s21::Matrix4x4 expected_matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                 0.0f, 0.0f, 1.0f, 1.056, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetTranslationZ(1.056f);
  transform.UpdateTranslationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyRotationXTrueTest) {
  s21::Matrix4x4 expected_matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
                                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetRotationX(90);
  transform.UpdateRotationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyRotationYTrueTest) {
  s21::Matrix4x4 expected_matrix(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetRotationY(-90);
  transform.UpdateRotationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyRotationZTrueTest) {
  s21::Matrix4x4 expected_matrix(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetRotationZ(180);
  transform.UpdateRotationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyRotationZ2TrueTest) {
  s21::Matrix4x4 expected_matrix(0.939693f, 0.34202f, 0.0f, 0.0f, -0.34202f,
                                 0.939693f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetRotationZ(-20);
  transform.UpdateRotationMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  printMatrix(expected_matrix);
  std::cout << std::endl;
  printMatrix(matrix);

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

TEST(TransformTest, ApplyScaleTrueTest) {
  s21::Matrix4x4 expected_matrix(0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
                                 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f,
                                 1.0f);
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetScale(0.2);
  transform.UpdateScaleMatrix();
  s21::Matrix4x4 matrix = transform.GetTransformMatrix();

  printMatrix(expected_matrix);
  std::cout << std::endl;
  printMatrix(matrix);

  EXPECT_TRUE(compareMatrices(matrix, expected_matrix));
}

bool compareMatrices(s21::Matrix4x4& m1, s21::Matrix4x4& m2) {
  float threshold = 0.00001;
  for (unsigned row = 0; row < 4; row++) {
    for (unsigned col = 0; col < 4; col++) {
      if (abs(m1.at(col, row) - m2.at(col, row)) >= threshold) {
        return false;
      }
    }
  }

  return true;
}

void printMatrix(s21::Matrix4x4& matrix) {
  for (unsigned row = 0; row < 4; row++) {
    for (unsigned col = 0; col < 4; col++) {
      std::cout << "[" << col << "][" << row << "] " << matrix.at(col, row)
                << " ";
    }
    std::cout << std::endl;
  }
}

// void print_vector(std::vector<s21::Vertex> expected_vertices, s21::Object
// &object) {
//   std::cout << "Expected vector\n";
//   for (auto elem : expected_vertices) {
//     std::cout << elem.x << " " << elem.y << " " << elem.z << std::endl;
//   }

//   std::cout << "Object vector\n";
//   for (auto elem : object.GetVertices()) {
//     std::cout << elem.x << " " << elem.y << " " << elem.z << std::endl;
//   }
// }