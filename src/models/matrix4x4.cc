#include "matrix4x4.h"

namespace s21 {

float Matrix4x4::at(unsigned x, unsigned y) {
  return matrix_[x][y];
}

void Matrix4x4::SetToIdentity() {
  matrix_[0][0] = 1.0f;
  matrix_[0][1] = 0.0f;
  matrix_[0][2] = 0.0f;
  matrix_[0][3] = 0.0f;
  matrix_[1][0] = 0.0f;
  matrix_[1][1] = 1.0f;
  matrix_[1][2] = 0.0f;
  matrix_[1][3] = 0.0f;
  matrix_[2][0] = 0.0f;
  matrix_[2][1] = 0.0f;
  matrix_[2][2] = 1.0f;
  matrix_[2][3] = 0.0f;
  matrix_[3][0] = 0.0f;
  matrix_[3][1] = 0.0f;
  matrix_[3][2] = 0.0f;
  matrix_[3][3] = 1.0f;
}

void Matrix4x4::Translate(float x, float y, float z) {
  matrix_[3][0] = x;
  matrix_[3][1] = y;
  matrix_[3][2] = z;
}

void Matrix4x4::PreCalculateSinCos(float angle, float *sin, float *cos) {
  if (angle == 90.0f || angle == -270.0f) {
    *sin = 1.0f;
    *cos = 0.0f;
  } else if (angle == -90.0f || angle == 270.0f) {
    *sin = -1.0f;
    *cos = 0.0f;
  } else if (angle == 180.0f || angle == -180.0f) {
    *sin = 0.0f;
    *cos = -1.0f;
  } else {
    float a = angle * M_PI / 180.0f;
    *cos = cosf(a);
    *sin = sinf(a);
  }
}

void Matrix4x4::Rotate(float angle, float x, float y, float z) {
  if (angle == 0.0f)
    return;
  Matrix4x4 m(1);
  float sin, cos;
  PreCalculateSinCos(angle, &sin, &cos);
  if (x == 0.0f) {
    if (y == 0.0f) {
      if (z != 0.0f) {
        RotateZ(&m, z, sin, cos);
      }
    } else if (z == 0.0f) {
      RotateY(&m, y, sin, cos);
    }
  } else if (y == 0.0f && z == 0.0f) {
    RotateZ(&m, x, sin, cos);
  }
  *this *= m;
}

void Matrix4x4::RotateZ(Matrix4x4 *m, float z, float sin, float cos) {
  m->SetToIdentity();
  m->matrix_[0][0] = cos;
  m->matrix_[1][1] = cos;
  if (z < 0.0f) {
      m->matrix_[1][0] = sin;
      m->matrix_[0][1] = -sin;
  } else {
      m->matrix_[1][0] = -sin;
      m->matrix_[0][1] = sin;
  }
}

void Matrix4x4::RotateY(Matrix4x4 *m, float y, float sin, float cos) {
  m->SetToIdentity();
  m->matrix_[0][0] = cos;
  m->matrix_[2][2] = cos;
  if (y < 0.0f) {
    m->matrix_[2][0] = -sin;
    m->matrix_[0][2] = sin;
  } else {
    m->matrix_[2][0] = sin;
    m->matrix_[0][2] = -sin;
  }
}

void Matrix4x4::RotateX(Matrix4x4 *m, float x, float sin, float cos) {
  m->SetToIdentity();
  m->matrix_[1][1] = cos;
  m->matrix_[2][2] = cos;
  if (x < 0.0f) {
    m->matrix_[2][1] = sin;
    m->matrix_[1][2] = -sin;
  } else {
    m->matrix_[2][1] = -sin;
    m->matrix_[1][2] = sin;
  }
}

void Matrix4x4::Scale(float factor) {
  matrix_[0][0] *= factor;
  matrix_[0][1] *= factor;
  matrix_[0][2] *= factor;
  matrix_[0][3] *= factor;
  matrix_[1][0] *= factor;
  matrix_[1][1] *= factor;
  matrix_[1][2] *= factor;
  matrix_[1][3] *= factor;
  matrix_[2][0] *= factor;
  matrix_[2][1] *= factor;
  matrix_[2][2] *= factor;
  matrix_[2][3] *= factor;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
  *this = *this * other;
  return *this;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
  Matrix4x4 m(1);
  m.matrix_[0][0] = m1.matrix_[0][0] * m2.matrix_[0][0] +
                    m1.matrix_[1][0] * m2.matrix_[0][1] +
                    m1.matrix_[2][0] * m2.matrix_[0][2] +
                    m1.matrix_[3][0] * m2.matrix_[0][3];
  
  m.matrix_[0][1] = m1.matrix_[0][1] * m2.matrix_[0][0] +
                    m1.matrix_[1][1] * m2.matrix_[0][1] +
                    m1.matrix_[2][1] * m2.matrix_[0][2] +
                    m1.matrix_[3][1] * m2.matrix_[0][3];
  
  m.matrix_[0][2] = m1.matrix_[0][2] * m2.matrix_[0][0] +
                    m1.matrix_[1][2] * m2.matrix_[0][1] +
                    m1.matrix_[2][2] * m2.matrix_[0][2] +
                    m1.matrix_[3][2] * m2.matrix_[0][3];
  
  m.matrix_[0][3] = m1.matrix_[0][3] * m2.matrix_[0][0] +
                    m1.matrix_[1][3] * m2.matrix_[0][1] +
                    m1.matrix_[2][3] * m2.matrix_[0][2] +
                    m1.matrix_[3][3] * m2.matrix_[0][3];
  
  m.matrix_[1][0] = m1.matrix_[0][0] * m2.matrix_[1][0] +
                    m1.matrix_[1][0] * m2.matrix_[1][1] +
                    m1.matrix_[2][0] * m2.matrix_[1][2] +
                    m1.matrix_[3][0] * m2.matrix_[1][3];
  
  m.matrix_[1][1] = m1.matrix_[0][1] * m2.matrix_[1][0] +
                    m1.matrix_[1][1] * m2.matrix_[1][1] +
                    m1.matrix_[2][1] * m2.matrix_[1][2] +
                    m1.matrix_[3][1] * m2.matrix_[1][3];
  
  m.matrix_[1][2] = m1.matrix_[0][2] * m2.matrix_[1][0] +
                    m1.matrix_[1][2] * m2.matrix_[1][1] +
                    m1.matrix_[2][2] * m2.matrix_[1][2] +
                    m1.matrix_[3][2] * m2.matrix_[1][3];
  
  m.matrix_[1][3] = m1.matrix_[0][3] * m2.matrix_[1][0] +
                    m1.matrix_[1][3] * m2.matrix_[1][1] +
                    m1.matrix_[2][3] * m2.matrix_[1][2] +
                    m1.matrix_[3][3] * m2.matrix_[1][3];
  
  m.matrix_[2][0] = m1.matrix_[0][0] * m2.matrix_[2][0] +
                    m1.matrix_[1][0] * m2.matrix_[2][1] +
                    m1.matrix_[2][0] * m2.matrix_[2][2] +
                    m1.matrix_[3][0] * m2.matrix_[2][3];
  
  m.matrix_[2][1] = m1.matrix_[0][1] * m2.matrix_[2][0] +
                    m1.matrix_[1][1] * m2.matrix_[2][1] +
                    m1.matrix_[2][1] * m2.matrix_[2][2] +
                    m1.matrix_[3][1] * m2.matrix_[2][3];
  
  m.matrix_[2][2] = m1.matrix_[0][2] * m2.matrix_[2][0] +
                    m1.matrix_[1][2] * m2.matrix_[2][1] +
                    m1.matrix_[2][2] * m2.matrix_[2][2] +
                    m1.matrix_[3][2] * m2.matrix_[2][3];
  
  m.matrix_[2][3] = m1.matrix_[0][3] * m2.matrix_[2][0] +
                    m1.matrix_[1][3] * m2.matrix_[2][1] +
                    m1.matrix_[2][3] * m2.matrix_[2][2] +
                    m1.matrix_[3][3] * m2.matrix_[2][3];
  
  m.matrix_[3][0] = m1.matrix_[0][0] * m2.matrix_[3][0] +
                    m1.matrix_[1][0] * m2.matrix_[3][1] +
                    m1.matrix_[2][0] * m2.matrix_[3][2] +
                    m1.matrix_[3][0] * m2.matrix_[3][3];
  
  m.matrix_[3][1] = m1.matrix_[0][1] * m2.matrix_[3][0] +
                    m1.matrix_[1][1] * m2.matrix_[3][1] +
                    m1.matrix_[2][1] * m2.matrix_[3][2] +
                    m1.matrix_[3][1] * m2.matrix_[3][3];
  
  m.matrix_[3][2] = m1.matrix_[0][2] * m2.matrix_[3][0] +
                    m1.matrix_[1][2] * m2.matrix_[3][1] +
                    m1.matrix_[2][2] * m2.matrix_[3][2] +
                    m1.matrix_[3][2] * m2.matrix_[3][3];
  
  m.matrix_[3][3] = m1.matrix_[0][3] * m2.matrix_[3][0] +
                    m1.matrix_[1][3] * m2.matrix_[3][1] +
                    m1.matrix_[2][3] * m2.matrix_[3][2] +
                    m1.matrix_[3][3] * m2.matrix_[3][3];
  return m;
}

}  // namespace s21