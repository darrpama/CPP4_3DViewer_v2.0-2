#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H

#include "type.h"
#include <QColor>
#include <iostream>

namespace s21 {
// facade
class Settings {
 public:
  Settings()
    : projection_type_(ProjectionType::CENTRAL)
    , bg_color_(QColor(20,20,20))
    , points_color_(QColor(0, 255, 255))
    , lines_color_(QColor(255, 0, 0)) {}

  const QColor &GetColor(const ColorType &);
  void SetProjectionType(const ProjectionType &type) { projection_type_ = type; }
  const ProjectionType &GetProjectionType() { return projection_type_; }

  void SetBackgroundColor(QColor color) { bg_color_ = color; }
  void SetPointsColor(QColor color) { points_color_ = color; }
  void SetLinesColor(QColor color) { lines_color_ = color; }

 private:
  ProjectionType projection_type_;
  QColor bg_color_;
  QColor points_color_;
  QColor lines_color_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_SETTINGS_H