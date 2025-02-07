#include <cmath>

#define INV_DIST 1.0f / 1024.0f;

namespace s21 {

class Matrix4x4 {
 public:
  Matrix4x4() : matrix_{} { SetToIdentity(); }
  explicit Matrix4x4(int) : matrix_{} {}
  Matrix4x4(float, float, float, float, float, float, float, float, float,
            float, float, float, float, float, float, float);
  Matrix4x4 &operator*=(const Matrix4x4 &other);
  friend Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);
  void SetToIdentity();
  void Translate(float x, float y, float z);
  void Rotate(float angle, float x, float y, float z);
  void Scale(float factor);
  float at(unsigned, unsigned);

 private:
  float matrix_[4][4];

  void PreCalculateSinCos(float angle, float *sin, float *cos);
  void RotateZ(Matrix4x4 *m, float sin, float cos);
  void RotateY(Matrix4x4 *m, float sin, float cos);
  void RotateX(Matrix4x4 *m, float sin, float cos);
};

}  // namespace s21
