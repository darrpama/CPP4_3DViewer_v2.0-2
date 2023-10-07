#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_MODEL_H

#include "object.h"
#include "obj_parser.h"
#include "transform.h"
#include "renderer.h"

namespace s21 {

class Model : Observable{
 public:
  Model() : render_(), object_(), transform_(), parser_() {}

// RENDER methods
  void InitOpenGL();
  void SetViewPort(int, int);
  void RenderObject();

// TRANSFRORM methods
  void ApplyTranslationX(double offset);
  void ApplyTranslationY(double offset);
  void ApplyTranslationZ(double offset);
  void ApplyRotation(double, double, double);
  void ApplyScale(double, double, double);

// PARSER methods
  void ParseObjFile(std::string &);

 private:
  Renderer render_;
  Object object_;
  Transform transform_;
  OBJParser parser_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODELS_MODEL_H