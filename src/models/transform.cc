#include "transform.h"

namespace s21 {

Transform::Transform(Settings *s) : settings_(s) {
  translation_matrix_.SetToIdentity();
  rotation_matrix_.SetToIdentity();
  scale_matrix_.SetToIdentity();
}

void Transform::UpdateTranslationMatrix() {
  translation_matrix_.SetToIdentity();
  translation_matrix_.Translate(settings_->GetTranslation().x,
                                settings_->GetTranslation().y,
                                settings_->GetTranslation().z);
}

void Transform::UpdateRotationMatrix() {
  rotation_matrix_.SetToIdentity();
  rotation_matrix_.Rotate(settings_->GetRotation().x, 1.0f, 0.0f, 0.0f);
  rotation_matrix_.Rotate(settings_->GetRotation().y, 0.0f, 1.0f, 0.0f);
  rotation_matrix_.Rotate(settings_->GetRotation().z, 0.0f, 0.0f, 1.0f);
}

void Transform::UpdateScaleMatrix() {
  scale_matrix_.SetToIdentity();
  scale_matrix_.Scale(settings_->GetScale());
}

Matrix4x4 Transform::GetTransformMatrix() {
  transform_matrix_ = translation_matrix_ * rotation_matrix_ * scale_matrix_;
  return transform_matrix_;
}

}  // namespace s21
