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
  void SetProjectionType(ProjectionType);

  // transform
  void ApplyTranslation(float, float, float);
  void ApplyRotation(float, float, float);
  void ApplyScale(float);
  
  // colors
  void SetBackgroundColor(QColor);
  void SetPointsColor(QColor);
  void SetLinesColor(QColor);

  // edge
  void SetEdgeType(EdgeType);
  void SetEdgeThikness(int);

  // vertices
  void SetVerticeType(VerticeType);
  void SetVerticeSize(int);

 private:
  Model *model_;
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
