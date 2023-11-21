#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_SETTINGS_H

#include "type.h"
#include <QColor>
#include <QVector3D>
#include <iostream>
#include <fstream>

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

  void SaveSettings();
  void LoadSettings();

  void SetProjectionType(const ProjectionType &);
  const ProjectionType &GetProjectionType();
  
  void SetColor(ColorType, const QColor &);
  const QColor &GetColor(const ColorType &);
  
  void SetEdgeType(const EdgeType &);
  const EdgeType &GetEdgeType();

  void SetVerticeType(const VerticeType &);
  const VerticeType & GetVerticeType();

  void SetEdgeThickness(int);
  int GetEdgeThickness();

  void SetVerticeSize(int);
  int GetVerticeSize();

  void SetTranslation(float, float, float);
  const QVector3D &GetTranslation();

  float GetTranslationX();
  float GetTranslationY();
  float GetTranslationZ();

  void SetRotation(float, float, float);
  const QVector3D &GetRotation();

  float GetRotationX();
  float GetRotationY();
  float GetRotationZ();

  void SetScale(float);
  float GetScale();

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