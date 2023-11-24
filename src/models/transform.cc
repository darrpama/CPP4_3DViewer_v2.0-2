#include "transform.h"

namespace s21 {

Transform::Transform(Settings *s) : settings_(s) {
  TranslationMatrix_.setToIdentity();
  RotationMatrix_.setToIdentity();
  ScaleMatrix_.setToIdentity();
}

void Transform::UpdateTranslationMatrix() {
  TranslationMatrix_.setToIdentity();
  TranslationMatrix_.translate(
    settings_->GetTranslation().x,
    settings_->GetTranslation().y,
    settings_->GetTranslation().z
  );
}

void Transform::UpdateRotatitionMatrix() {
  RotationMatrix_.setToIdentity();
  
  RotationMatrix_.rotate(
    settings_->GetRotation().x,
    1.0f, 0.0f, 0.0f
  );
  
  RotationMatrix_.rotate(
    settings_->GetRotation().y,
    0.0f, 1.0f, 0.0f
  );
  
  RotationMatrix_.rotate(
    settings_->GetRotation().z,
    0.0f, 0.0f, 1.0f
  );
}

void Transform::UpdateScaleMatrix() {
  ScaleMatrix_.setToIdentity();
  ScaleMatrix_.scale(settings_->GetScale());
}

QMatrix4x4 Transform::GetTransformMatrix() {
  TransformMatrix_ = TranslationMatrix_ * RotationMatrix_ * ScaleMatrix_;
  return TransformMatrix_;
}

}  // namespace s21
