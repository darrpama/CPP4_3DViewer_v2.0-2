#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H

#include "type.h"
#include <QColor>
#include <QVector3D>
#include <iostream>

namespace s21 {
// facade
class Settings {
 public:
  Settings()
    : projection_type_(ProjectionType::CENTRAL)
    , bg_color_(QColor(20,20,20))
    , points_color_(QColor(0, 255, 255))
    , lines_color_(QColor(255, 0, 0))
    , edge_type_(EdgeType::SOLID)
    , vertice_type_(VerticeType::SQUARE)
    , edge_thickness_(1)
    , vertice_size_(1)
    , translation_(0.0f, 0.0f, 0.0f)
    , rotation_(0.0f, 0.0f, 0.0f)
    , scale_(1.0f)
    {}

  void SetColor(ColorType, const QColor &);
  const QColor &GetColor(const ColorType &);
  
  void SetProjectionType(const ProjectionType &type) { projection_type_ = type; }
  const ProjectionType &GetProjectionType() { return projection_type_; }
  
  void SetEdgeType(const EdgeType &type) { edge_type_ = type; }
  const EdgeType &GetEdgeType() { return edge_type_; }

  void SetVerticeType(const VerticeType &type) { vertice_type_ = type; }
  const VerticeType & GetVerticeType() { return vertice_type_; }

  void SetEdgeThickness(int val) { edge_thickness_ = val; }
  int GetEdgeThickness() { return edge_thickness_; }

  void SetVerticeSize(int val) { vertice_size_ = val; }
  int GetVerticeSize() {return vertice_size_; }

  void SetTranslation(float, float, float);
  const QVector3D &GetTranslation() { return translation_; }

  void SetRotation(float, float, float);
  const QVector3D &GetRotation() { return rotation_; }

  void SetScale(float f) { scale_ = f; }
  float GetScale() { return scale_; }

 private:
  ProjectionType projection_type_;
  QColor bg_color_;
  QColor points_color_;
  QColor lines_color_;
  EdgeType edge_type_;
  VerticeType vertice_type_;
  int edge_thickness_;
  int vertice_size_;
  QVector3D translation_;
  QVector3D rotation_;
  float scale_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_SETTINGS_H