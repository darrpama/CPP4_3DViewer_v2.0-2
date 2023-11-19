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

void Settings::SaveSettings() {
  std::ofstream outfile("/Users/myregree/Desktop/projects/CPP4_3DViewer_v2.0-2/src/settings.dat");
  outfile << projection_type_ << std::endl;
  outfile << bg_color_.red() << std::endl;
  outfile << bg_color_.green() << std::endl;
  outfile << bg_color_.blue() << std::endl;
  outfile << points_color_.red() << std::endl;
  outfile << points_color_.green() << std::endl;
  outfile << points_color_.blue() << std::endl;
  outfile << lines_color_.red() << std::endl;
  outfile << lines_color_.green() << std::endl;
  outfile << lines_color_.blue() << std::endl;
  outfile << edge_type_ << std::endl;
  outfile << vertice_type_ << std::endl;
  outfile << edge_thickness_ << std::endl;
  outfile << vertice_size_ << std::endl;
  outfile << translation_.x() << std::endl;
  outfile << translation_.y() << std::endl;
  outfile << translation_.z() << std::endl;
  outfile << rotation_.x() << std::endl;
  outfile << rotation_.y() << std::endl;
  outfile << rotation_.z() << std::endl;
  outfile << scale_ << std::endl;
  outfile.close();
}

}  // namespace s21

