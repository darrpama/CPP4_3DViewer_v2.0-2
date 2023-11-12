#include "settings.h"

namespace s21 {

void Settings::SetColor(ColorType type, const QColor &color) {
  if (type == ColorType::BG_COLOR) bg_color_ = color;
  if (type == ColorType::VERTICE_COLOR) points_color_ = color;
  if (type == ColorType::EDGE_COLOR) lines_color_ = color;
}

const QColor &Settings::GetColor(const ColorType &type) {
  if (type == ColorType::BG_COLOR) return bg_color_;
  if (type == ColorType::VERTICE_COLOR) return points_color_;
  if (type == ColorType::EDGE_COLOR) return lines_color_;
  return QColor(120, 60, 30);
}

void Settings::SetTranslation(float x, float y, float z) {
  translation_.setX(x);
  translation_.setY(y);
  translation_.setZ(z);
}

void Settings::SetRotation(float x, float y, float z) {
  rotation_.setX(x);
  rotation_.setY(y);
  rotation_.setZ(z);
}

}  // namespace s21

