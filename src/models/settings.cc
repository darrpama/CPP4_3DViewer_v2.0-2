#include "settings.h"

namespace s21 {
void Settings::SetProjectionType(const ProjectionType &type) { 
  projection_type_ = type;
  SaveSettings();
}
  
void Settings::SetColor(ColorType type, const QColor &color) {
  if (type == ColorType::BG_COLOR) bg_color_ = color;
  if (type == ColorType::VERTICE_COLOR) points_color_ = color;
  if (type == ColorType::EDGE_COLOR) lines_color_ = color;
  SaveSettings();
}

void Settings::SetEdgeType(const EdgeType &type) {
  edge_type_ = type;
  SaveSettings();
}

void Settings::SetVerticeType(const VerticeType &type) { 
  vertice_type_ = type;
  SaveSettings();
}

void Settings::SetEdgeThickness(int val) {
  edge_thickness_ = val;
  SaveSettings();
}

void Settings::SetVerticeSize(int val) {
  vertice_size_ = val;
  SaveSettings();
}
void Settings::SetScale(float f) {
  scale_ = f;
  SaveSettings();
}

void Settings::SetTranslationX(float val) {
  translation_.setX(val);
  SaveSettings();
}

void Settings::SetTranslationY(float val) {
  translation_.setY(val);
  SaveSettings();
}

void Settings::SetTranslationZ(float val) {
  translation_.setZ(val);
  SaveSettings();
}

void Settings::SetRotationX(float val) {
  rotation_.setX(val);
  SaveSettings();
}

void Settings::SetRotationY(float val) {
  rotation_.setY(val);
  SaveSettings();
}

void Settings::SetRotationZ(float val) {
  rotation_.setZ(val);
  SaveSettings();
}

// GETTERS
const ProjectionType &Settings::GetProjectionType() {
  return projection_type_;
}

const QColor &Settings::GetColor(const ColorType &type) {
  if (type == ColorType::BG_COLOR) return bg_color_;
  if (type == ColorType::VERTICE_COLOR) return points_color_;
  if (type == ColorType::EDGE_COLOR) return lines_color_;
  return bg_color_;
}

const EdgeType &Settings::GetEdgeType() {
  return edge_type_;
}

const VerticeType & Settings::GetVerticeType() { 
  return vertice_type_;
}

int Settings::GetEdgeThickness() {
  return edge_thickness_;
}

int Settings::GetVerticeSize() {
  return vertice_size_;
}

float Settings::GetTranslationX() {
  return translation_.x();
}

float Settings::GetTranslationY() {
  return translation_.y();
}

float Settings::GetTranslationZ() {
  return translation_.z();
}

const QVector3D &Settings::GetTranslation() {
  return translation_;
}

const QVector3D &Settings::GetRotation() {
  return rotation_;
}

float Settings::GetRotationX() {
  return rotation_.x();
}

float Settings::GetRotationY() {
  return rotation_.y();
}

float Settings::GetRotationZ() {
  return rotation_.z();
}

float Settings::GetScale() {
  return scale_;
}

void Settings::SaveSettings() {
  std::ofstream outfile("settings.dat");
  outfile << projection_type_ << std::endl;       // 1
  outfile << bg_color_.red() << std::endl;        // 2
  outfile << bg_color_.green() << std::endl;      // 3
  outfile << bg_color_.blue() << std::endl;       // 4
  outfile << points_color_.red() << std::endl;    // 5
  outfile << points_color_.green() << std::endl;  // 6
  outfile << points_color_.blue() << std::endl;   // 7
  outfile << lines_color_.red() << std::endl;     // 8
  outfile << lines_color_.green() << std::endl;   // 9
  outfile << lines_color_.blue() << std::endl;    // 11
  outfile << edge_type_ << std::endl;             // 11
  outfile << vertice_type_ << std::endl;          // 12
  outfile << edge_thickness_ << std::endl;        // 13
  outfile << vertice_size_ << std::endl;          // 14
  outfile << translation_.x() << std::endl;       // 15
  outfile << translation_.y() << std::endl;       // 16
  outfile << translation_.z() << std::endl;       // 17
  outfile << rotation_.x() << std::endl;          // 18
  outfile << rotation_.y() << std::endl;          // 19
  outfile << rotation_.z() << std::endl;          // 20
  outfile << scale_ << std::endl;                 // 21

  outfile.close();
}

void Settings::LoadSettings() {
  std::ifstream infile("settings.dat");
  int projection_type;
  infile >> projection_type;
  projection_type_ = (ProjectionType) projection_type;

  int bg_color_red, bg_color_green, bg_color_blue;
  infile >> bg_color_red; 
  infile >> bg_color_green;
  infile >> bg_color_blue;
  bg_color_ = QColor(bg_color_red, bg_color_green, bg_color_blue);

  int points_color_red, points_color_green, points_color_blue;
  infile >> points_color_red; 
  infile >> points_color_green;
  infile >> points_color_blue;
  points_color_ = QColor(points_color_red, points_color_green, points_color_blue);

  int lines_color_red, lines_color_green, lines_color_blue;
  infile >> lines_color_red; 
  infile >> lines_color_green;
  infile >> lines_color_blue;
  lines_color_ = QColor(lines_color_red, lines_color_green, lines_color_blue);

  int edge_type;
  infile >> edge_type;
  edge_type_ = (EdgeType) edge_type;

  int vertice_type;
  infile >> vertice_type;
  vertice_type_ = (VerticeType) vertice_type;

  infile >> edge_thickness_;
  infile >> vertice_size_;

  float translation_x;
  float translation_y;
  float translation_z;
  infile >> translation_x;
  infile >> translation_y;
  infile >> translation_z;
  translation_.setX(translation_x);
  translation_.setY(translation_y);
  translation_.setZ(translation_z);

  float rotation_x, rotation_y, rotation_z;
  infile >> rotation_x;
  infile >> rotation_y;
  infile >> rotation_z;
  rotation_.setX(rotation_x);
  rotation_.setY(rotation_y);
  rotation_.setZ(rotation_z);

  infile >> scale_;
}

}  // namespace s21

