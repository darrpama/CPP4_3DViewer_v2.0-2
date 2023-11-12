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

  // PROJECTION
  void SetProjectionType(const ProjectionType &type);
  const ProjectionType &GetProjectionType();

  // COLORS
  void SetColor(ColorType, const QColor &);
  const QColor &GetColor(const ColorType &);

  // EDGE
  void inline SetEdgeType(EdgeType type) { render_->SetEdgeType(type); }
  void inline SetEdgeThikness(int position) { render_->SetEdgeThikness(position); }

  // VERTICES
  void inline SetVerticeType(VerticeType type) { render_->SetVerticeType(type); }
  void inline SetVerticeSize(int size) { render_->SetVerticeSize(size); }

  // MODEL PARAMETERS
  size_t inline GetVertexCount() { return object_->GetVertexCount(); }
  size_t inline GetFaceCount() { return object_->GetFaceCount(); }
  size_t inline GetEdgeCount() { return object_->GetEdgeCount(); }

 private:
  Renderer *render_;
  Transform *transform_;
  OBJParser *parser_;
  Object *object_;
  Settings *settings_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H