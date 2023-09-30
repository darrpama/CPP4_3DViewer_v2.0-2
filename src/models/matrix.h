/**
Copyright 2023 Kadyr Atakhanov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MATRIX_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MATRIX_H_

#include <math.h>

#include <iostream>

namespace s21 {

class Matrix {
 public:
  // CONSTRUCTORS
  Matrix();
  Matrix(int, int);
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;

  // ASSIGNMENTS
  Matrix operator=(const Matrix&);
  void operator+=(const Matrix&);
  void operator-=(const Matrix&);
  void operator*=(const Matrix&);
  void operator*=(const double x);
  double& operator()(int row, int col);

  // DESTRUCTOR
  ~Matrix();

  // COMPARISONS
  bool EqMatrix(const Matrix&);
  bool operator==(const Matrix&);

  // ARITHMETIC OPERAT(IONS)ORS
  void SumMatrix(const Matrix&);
  Matrix operator+(const Matrix&) const;
  void SubMatrix(const Matrix&);
  Matrix operator-(const Matrix&);
  void MulNumber(const double);
  Matrix operator*(const double);
  void MulMatrix(const Matrix&);
  Matrix operator*(const Matrix&);

  // ALGEBRAIC FUNCTIONS
  Matrix Transpose();
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  // ACCESSORS
  int GetRows() const;
  int GetCols() const;

  // MUTATORS
  void SetRows(int n);
  void SetCols(int n);

 private:
  int rows_{};
  int cols_{};
  double** matrix_{};

  // MEMORY
  void AllocSpace();
  void Swap(Matrix&);

  // ALGEBRAIC FUNCTIONS
  Matrix FindMinorMatrix(int, int);
  double CalcDeterminant(Matrix, int);
};
}  // namespace s21

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
