#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H

#include "object.h"
#include "obj_parser.h"
#include "transform.h"
#include "renderer.h"

namespace s21 {

class Model {
 public:
  Model(Object *obj, Transform *m)
    : object_(obj)
    , render_(obj, m)
    , parser_(obj) {}

// RENDER methods
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

// PARSER methods
  void ParseObjFile(std::string &);

// TRANSFRORM methods
  void ApplyTranslation(float, float, float);
  void ApplyRotation(float, float, float);
  void ApplyScale(float);

// PROJECTION
  void SetCentralProjection();
  void SetParallelProjection();

// COLORS
  void SetBackgroundColor(QColor);
  void SetPointsColor(QColor);
  void SetLinesColor(QColor);

// EDGE
  void SetEdgeType(EdgeType type) { render_.SetEdgeType(type); }
  void SetEdgeThikness(int position) { render_.SetEdgeThikness(position); }

// VERTICES
  void SetVerticeType(VerticeType type) { render_.SetVerticeType(type); }
  void SetVerticeSize(int size) { render_.SetVerticeSize(size); }

 private:
  Object *object_;
  Renderer render_;
  Transform transform_;
  OBJParser parser_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H