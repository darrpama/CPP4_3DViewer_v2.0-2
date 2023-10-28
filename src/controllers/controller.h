#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H

#include "../models/model.h"

#include <string>
#include <unordered_map>

namespace s21 {
class Controller {

 public:
  explicit Controller() : model_() {};
  explicit Controller(Model *model) : model_(model) {};

  // render
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

  // parser
  void ParseObjFile(std::string &);

  // projection
  void SetCentralProjection();
  void SetParallelProjection();

  // transform
  void ApplyTranslationX(float);
  void ApplyTranslationY(float);
  void ApplyTranslationZ(float);
  void ApplyRotationX(float);
  void ApplyRotationY(float);
  void ApplyRotationZ(float);
  void ApplyScale(float);
  
  // colors
  void SetBackgroundColor(QColor);
  void SetPointsColor(QColor);
  void SetLinesColor(QColor);

  // edge types
  void SetEdgeType(EdgeType);

 private:
  Model *model_;
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
