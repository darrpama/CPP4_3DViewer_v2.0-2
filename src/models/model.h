#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H

#include "type.h"
#include "object.h"
#include "obj_parser.h"
#include "transform.h"
#include "renderer.h"
#include "settings.h"

namespace s21 {
// facade
class Model {
 public:
  Model(Object *o, OBJParser *p, Transform *t, Renderer *r, Settings *s)
    : object_(o)
    , parser_(p) 
    , transform_(t)
    , render_(r)
    , settings_(s) {}

  // RENDER methods
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

  // PARSER methods
  void ParseObjFile(QString&);

  // TRANSFRORM methods
  void NormalizeObject();
  void ApplyTranslation(float, float, float);
  void ApplyRotation(float, float, float);
  void ApplyScale(float);

  float GetTranslationX();
  float GetTranslationY();
  float GetTranslationZ();

  float GetRotationX();
  float GetRotationY();
  float GetRotationZ();

  float GetScale();

  // PROJECTION
  void SetProjectionType(const ProjectionType &type);
  const ProjectionType &GetProjectionType();

  // COLORS
  void SetColor(ColorType, const QColor &);
  const QColor &GetColor(const ColorType &);

  // EDGE
  void SetEdgeType(EdgeType type) { settings_->SetEdgeType(type); }
  const EdgeType &GetEdgeType() { return settings_->GetEdgeType(); }
  void SetEdgeThickness(int val) { settings_->SetEdgeThickness(val); }
  int GetEdgeThickness() { return settings_->GetEdgeThickness(); }

  // VERTICES
  void SetVerticeType(VerticeType type) { settings_->SetVerticeType(type); }
  const VerticeType &GetVerticeType() { return settings_->GetVerticeType(); }
  void SetVerticeSize(int size) { settings_->SetVerticeSize(size); }
  int GetVerticeSize() { return settings_->GetVerticeSize(); }

  // MODEL PARAMETERS
  size_t GetVertexCount() { return object_->GetVertexCount(); }
  size_t GetFaceCount() { return object_->GetFaceCount(); }
  size_t GetEdgeCount() { return object_->GetEdgeCount(); }

 private:
  Renderer *render_;
  Transform *transform_;
  OBJParser *parser_;
  Object *object_;
  Settings *settings_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H