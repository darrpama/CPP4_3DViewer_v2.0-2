#include "transform.h"

namespace s21 {

Transform::Transform(Settings *s) : settings_(s)
{
  TranslationMatrix_.SetToIdentity();
  RotationMatrix_.SetToIdentity();
  ScaleMatrix_.SetToIdentity();
}

void Transform::UpdateTranslationMatrix() {
  TranslationMatrix_.SetToIdentity();
  TranslationMatrix_.Translate(
    settings_->GetTranslation().x,
    settings_->GetTranslation().y,
    settings_->GetTranslation().z
  );
}

void Transform::UpdateRotatitionMatrix() {
  RotationMatrix_.SetToIdentity();
  RotationMatrix_.Rotate(
    settings_->GetRotation().x,
    1.0f, 0.0f, 0.0f
  );
  RotationMatrix_.Rotate(
    settings_->GetRotation().y,
    0.0f, 1.0f, 0.0f
  );
  RotationMatrix_.Rotate(
    settings_->GetRotation().z,
    0.0f, 0.0f, 1.0f
  );
}

void Transform::UpdateScaleMatrix() {
  ScaleMatrix_.SetToIdentity();
  ScaleMatrix_.Scale(settings_->GetScale());
}

Matrix4x4 Transform::GetTransformMatrix() {
  TransformMatrix_ = TranslationMatrix_ * RotationMatrix_ * ScaleMatrix_;
  return TransformMatrix_;
}

}  // namespace s21
