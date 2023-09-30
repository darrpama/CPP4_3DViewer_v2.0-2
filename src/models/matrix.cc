#include "matrix.h"

namespace s21 {
// CONSTRUCTORS
Matrix::Matrix() : rows_(1), cols_(1) { this->AllocSpace(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  this->AllocSpace();
}

Matrix::Matrix(const Matrix& m) : Matrix(m.rows_, m.cols_) {
  for (int i = 0; i < m.rows_; i++)
    for (int j = 0; j < m.cols_; j++) this->matrix_[i][j] = m.matrix_[i][j];
}

Matrix::Matrix(Matrix&& other) noexcept { this->Swap(other); }

// ASSIGNMENTS
Matrix Matrix::operator=(const Matrix& other) {
  this->~Matrix();
  this->rows_ = other.GetRows();
  this->cols_ = other.GetCols();
  this->AllocSpace();
  this->SumMatrix(other);
  return *this;
}

void Matrix::operator+=(const Matrix& other) { this->SumMatrix(other); }
void Matrix::operator-=(const Matrix& other) { this->SubMatrix(other); }
void Matrix::operator*=(const Matrix& other) { this->MulMatrix(other); }
void Matrix::operator*=(const double other) { this->MulNumber(other); }

double& Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_)
    throw std::out_of_range("Incorrect input, some indexes is out of range");
  return this->matrix_[row][col];
}

// DESTRUCTOR
Matrix::~Matrix() {
  for (int i = 0; i < this->rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  this->rows_ = 0;
  this->cols_ = 0;
}

// COMPARISONS
bool Matrix::EqMatrix(const Matrix& other) {
  if ((rows_ != other.GetRows()) || (cols_ != other.GetCols())) return false;

  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > __DBL_EPSILON__)
        return false;
    }
  }
  return true;
}

bool Matrix::operator==(const Matrix& other) {
  return this->EqMatrix(other);
}

// ARITHMETIC OPERAT(IONS)ORS
void Matrix::SumMatrix(const Matrix& other) {
  if ((rows_ != other.GetRows()) || (cols_ != other.GetCols()))
    throw std::invalid_argument("different matrix dimensions");

  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

void Matrix::SubMatrix(const Matrix& other) {
  if ((rows_ != other.GetRows()) || (cols_ != other.GetCols()))
    throw std::invalid_argument("different matrix dimensions");

  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

void Matrix::MulNumber(const double number) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= number;
}

Matrix Matrix::operator*(const double x) {
  Matrix result(*this);
  result.MulNumber(x);
  return result;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (this->cols_ != other.rows_ || this->rows_ != other.cols_)
    throw std::invalid_argument("matrix 1 columns and matrix 2 rows not equal");

  Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i)
    for (int j = 0; j < other.GetCols(); ++j)
      for (int k = 0; k < this->cols_; ++k)
        result.matrix_[i][j] += (this->matrix_[i][k] * other.matrix_[k][j]);
  *this = result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// ALGEBRAIC FUNCTIONS
Matrix Matrix::Transpose() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("rows and cols must be greater then 0");

  Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < rows_; j++) result.matrix_[i][j] = matrix_[j][i];
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("the matrix is not square");

  if (this->rows_ == 1) return this->matrix_[0][0];

  if (this->rows_ == 2)
    return ((matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]));

  double result = this->CalcDeterminant(*this, rows_);
  return result;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::invalid_argument("the matrix is not square");

  Matrix result(rows_, cols_);
  Matrix minor_matrix(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor_matrix = this->FindMinorMatrix(i, j);
      double minor_result = minor_matrix.Determinant();
      result.matrix_[i][j] = minor_result * (pow(-1, i + j));
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (fabs(determinant) <= __DBL_EPSILON__)
    throw std::domain_error("matrix determinant is 0");

  Matrix min_matrix = this->CalcComplements();
  Matrix transposed_matrix = min_matrix.Transpose();
  transposed_matrix.MulNumber(1.0 / determinant);
  return transposed_matrix;
}

// ACCESSORS
int Matrix::GetRows() const { return this->rows_; }
int Matrix::GetCols() const { return this->cols_; }

// MUTATORS
void Matrix::SetRows(int n) {
  Matrix matrix(n, this->cols_);
  for (int i = 0; i < matrix.rows_; i++)
    for (int j = 0; j < matrix.cols_; j++)
      if (i < this->rows_) matrix.matrix_[i][j] = this->matrix_[i][j];
  *this = matrix;
}

void Matrix::SetCols(int n) {
  Matrix matrix(this->rows_, n);
  for (int i = 0; i < matrix.rows_; i++)
    for (int j = 0; j < matrix.cols_; j++)
      if (j < this->cols_) matrix.matrix_[i][j] = this->matrix_[i][j];
  *this = matrix;
}

// MEMORY
void Matrix::AllocSpace() {
  this->matrix_ = new double*[this->rows_]();
  for (int i = 0; i < this->rows_; ++i)
    this->matrix_[i] = new double[this->cols_]();
}

void Matrix::Swap(Matrix& right) {
  std::swap(rows_, right.rows_);
  std::swap(cols_, right.cols_);
  std::swap(matrix_, right.matrix_);
}

// ALGEBRAIC FUNCTIONS
double Matrix::CalcDeterminant(Matrix matrix, int count) {
  if (count == 1) return matrix.matrix_[0][0];

  double result = 0.0f;
  int i, j, k;
  int sign = 1;
  Matrix sub_matrix(count - 1, count - 1);
  for (i = 0; i < count; i++) {
    int m = 0;
    for (j = 0; j < count; j++) {
      if (j == i) continue;
      for (k = 0; k < count - 1; k++)
        sub_matrix.matrix_[m][k] = matrix.matrix_[j][k + 1];
      m++;
    }
    double determinant = this->CalcDeterminant(sub_matrix, count - 1);
    result += matrix.matrix_[i][0] * determinant * sign;
    sign = -sign;
  }
  return result;
}

Matrix Matrix::FindMinorMatrix(int minor_row, int minor_col) {
  int m_r_i = 0, m_c_j = 0;  // init counts
  Matrix minor_result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i != minor_row && j != minor_col)
        // collecting result (minor matrix)
        minor_result.matrix_[m_r_i][m_c_j] = this->matrix_[i][j];
      if (j != minor_col) m_c_j++;
    }
    if (i != minor_row) {
      m_r_i++;
    }
    m_c_j = 0;  // count abort
  }
  return minor_result;
}

}  // namespace s21
