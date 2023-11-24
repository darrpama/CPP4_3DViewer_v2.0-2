#include <gtest/gtest.h>
#include <iostream>
#include <QMatrix4x4>

#include "../models/transform.h"

bool compareVertices(std::vector<s21::Vertex> v1, std::vector<s21::Vertex> v2);
void printMatrix(const QMatrix4x4& matrix);

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// load settings
// create instance of Transform
// apply transformation
//    UpdateTranslationMatrix
//    UpdateRotatitionMatrix
//    UpdateScaleMatrix
TEST(TransformTest, ApplyTranslationXTrueTest) {
  s21::Settings settings = s21::Settings();
  s21::Transform transform = s21::Transform(&settings);
  settings.SetTranslationX(1.0f);
  transform.UpdateTranslationMatrix();
  QMatrix4x4 matrix = transform.GetTransformMatrix();
  
  printMatrix(matrix);

  // EXPECT_TRUE(compareVertices(obj.GetVertices(), expected_vertices));
}


bool compareVertices(std::vector<s21::Vertex> v1, std::vector<s21::Vertex> v2) {
    bool res = true;
    for (size_t i = 0; i < v1.size() && res; ++i) {
        res = (v1[i].x == v2[i].x && v1[i].y == v2[i].y && v1[i].z == v2[i].z);
    }
    return res;
}

void printMatrix(const QMatrix4x4& matrix) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << matrix(row, col) << " ";
        }
        std::cout << std::endl;
    }
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