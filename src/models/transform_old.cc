#include "transform_old.h"

namespace s21 {

  void Transform::SetObject(Object *object) {
    object_ = object;
  }

  void Transform::ApplyTranslationX(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float current_offset = object_->GetOffset(X);
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].x += offset - current_offset;
    }
    object_->SetVertices(vertices);
    object_->SetOffset(X, offset);

  }

  void Transform::ApplyTranslationY(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float current_offset = object_->GetOffset(Y);
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].y += offset - current_offset;
    }
    object_->SetVertices(vertices);
    object_->SetOffset(Y, offset);
  }

  void Transform::ApplyTranslationZ(float offset) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float current_offset = object_->GetOffset(Z);
    for (size_t i = 0; i < vertices.size(); ++i) {
      vertices[i].z += offset - current_offset;
    }
    object_->SetVertices(vertices);
    object_->SetOffset(Z, offset);
  }

  void Transform::ApplyRotationX(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_y = 0;
    float temp_z = 0;
    float current_angle = object_->GetAngle(X);
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_y = vertices[i].y;
      temp_z = vertices[i].z;
      vertices[i].y = cos(angle - current_angle) * temp_y - sin(angle - current_angle) * temp_z;
      vertices[i].z = sin(angle - current_angle) * temp_y + cos(angle - current_angle) * temp_z;
    }
    object_->SetVertices(vertices);
    object_->SetAngle(X, angle);
  }

  void Transform::ApplyRotationY(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_x = 0;
    float temp_z = 0;
    float current_angle = object_->GetAngle(Y);
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_x = vertices[i].x;
      temp_z = vertices[i].z;
      vertices[i].x = cos(angle - current_angle) * temp_x + sin(angle - current_angle) * temp_z;
      vertices[i].z = sin(angle - current_angle) * -temp_x + cos(angle - current_angle) * temp_z;
    }
    object_->SetVertices(vertices);
    object_->SetAngle(Y, angle);
  }

  void Transform::ApplyRotationZ(float angle) {
    std::vector<Vertex> vertices = object_->GetVertices();
    float temp_x = 0;
    float temp_y = 0;
    float current_angle = object_->GetAngle(Z);
    for (size_t i = 0; i < vertices.size(); ++i) {
      temp_x = vertices[i].x;;
      temp_y = vertices[i].y;;
      vertices[i].x = cos(angle - current_angle) * temp_x - sin(angle - current_angle) * temp_y;
      vertices[i].y = sin(angle - current_angle) * temp_x + cos(angle - current_angle) * temp_y;
    }
    object_->SetVertices(vertices);
    object_->SetAngle(Z, angle);
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
