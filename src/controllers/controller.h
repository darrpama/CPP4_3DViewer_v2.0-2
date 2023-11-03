#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H

#include "../models/model.h"

#include <string>
#include <unordered_map>

namespace s21 {

// singleton
class Controller {
 private:
  Controller() : model_() {};
  Controller(const Controller&);
  Controller& operator=(const Controller&) = delete;

 public:
  static Controller& GetInstance() { 
    static Controller instance;
    return instance;
  }

  void SetModel(Model *model) { model_ = model; }
  // render
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

  // parser
  void ParseObjFile(QString &);

  // projection
  void SetProjectionType(ProjectionType);

  // transform
  void ApplyTranslation(float, float, float);
  void ApplyRotation(float, float, float);
  void ApplyScale(float);
  
  // colors
  void SetColor(ColorType, QColor);

  // edge
  void SetEdgeType(EdgeType);
  void SetEdgeThikness(int);

  // vertices
  void SetVerticeType(VerticeType);
  void SetVerticeSize(int);

  // object parameters
  unsigned GetVertexCount();
  unsigned GetFaceCount();
  unsigned GetEdgeCount();

 private:
  Model *model_;
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
