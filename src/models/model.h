#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H

#include "object.h"
#include "obj_parser.h"
#include "transform.h"
#include "renderer.h"

namespace s21 {

class Model {
 public:
  Model(Object *obj) 
    : object_(obj)
    , render_(obj)
    , transform_(obj)
    , parser_(obj) {}

// RENDER methods
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

// PARSER methods
  void ParseObjFile(std::string &);

// TRANSFRORM methods
  void ApplyTranslationX(float offset);
  void ApplyTranslationY(float offset);
  void ApplyTranslationZ(float offset);
  void ApplyRotationX(float angle);
  void ApplyRotationY(float angle);
  void ApplyRotationZ(float angle);
  void ApplyScale(float k);

// PROJECTION
  void SetCentralProjection();
  void SetParallelProjection();

// COLORS
  void SetBackgroundColor(QColor);
  void SetPointsColor(QColor);
  void SetLinesColor(QColor);

 private:
  Object *object_;
  Renderer render_;
  Transform transform_;
  OBJParser parser_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H