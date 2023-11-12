#include "settings.h"

namespace s21 {

const QColor &Settings::GetColor(const ColorType &type) {
  if (type == ColorType::BG_COLOR) return bg_color_;
  if (type == ColorType::VERTICE_COLOR) return points_color_;
  if (type == ColorType::EDGE_COLOR) return lines_color_;
  return QColor(120, 60, 30);
}

}  // namespace s21
