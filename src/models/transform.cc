#include "transform.h"

namespace s21 {

  void Transform::SetObject(Object *object) {
    object_ = object;
  }

  void Transform::ApplyTranslationX(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].x += offset;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyTranslationY(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].y += offset;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyTranslationZ(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].z += offset;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyRotationX(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_y = 0;
    float temp_z = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_y = vertices[i].y;
      temp_z = vertices[i].z;
      vertices[i].y = cos(angle) * temp_y - sin(angle) * temp_z;
      vertices[i].z = sin(angle) * temp_y + cos(angle) * temp_z;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyRotationY(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_x = 0;
    float temp_z = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_x = vertices[i].x;
      temp_z = vertices[i].z;
      vertices[i].x = cos(angle) * temp_x + sin(angle) * temp_z;
      vertices[i].z = sin(angle) * -temp_x + cos(angle) * temp_z;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyRotationZ(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_x = 0;
    float temp_y = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_x = vertices[i].x;
      temp_y = vertices[i].y;
      vertices[i].x = cos(angle) * temp_x - sin(angle) * temp_y;
      vertices[i].y = sin(angle) * temp_x + cos(angle) * temp_y;
    }
    object_->SetVertices(vertices);
  }

  void Transform::ApplyScale(float k) {
    std::vector<Vertex> vertices = object_->GetVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].x *= k;
      vertices[i].y *= k;
      vertices[i].z *= k;
    }
    object_->SetVertices(vertices);
  }

}  // namespace s21
