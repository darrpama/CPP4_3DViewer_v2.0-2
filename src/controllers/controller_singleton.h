#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H

#include <string>
#include <unordered_map>

#include "../models/model_facade.h"

namespace s21 {

// singleton
class ControllerSingleton {
 public:
  static ControllerSingleton &GetInstance() {
    static ControllerSingleton instance;
    return instance;
  }

  void SetModel(ModelFacade *model) { model_ = model; }
  // render
  void InitOpenGL();
  void SetViewPort(int, int);
  void PaintGL();

  // parser
  void ParseObjFile(QString &);

  // projection
  void SetProjectionType(const ProjectionType &);
  const ProjectionType &GetProjectionType();

  // transform
  void NormalizeObject();
  void SetTranslationX(float);
  void SetTranslationY(float);
  void SetTranslationZ(float);
  void SetRotationX(float);
  void SetRotationY(float);
  void SetRotationZ(float);
  void ApplyScale(float);

  float GetTranslationX();
  float GetTranslationY();
  float GetTranslationZ();

  float GetRotationX();
  float GetRotationY();
  float GetRotationZ();

  float GetScale();

  // colors
  void SetColor(ColorType, const QColor &);
  QColor GetColor(const ColorType &);

  // edges
  const EdgeType &GetEdgeType();
  void SetEdgeType(EdgeType);
  void SetEdgeThickness(int);
  int GetEdgeThickness();

  // vertices
  void SetVerticeType(VerticeType);
  const VerticeType &GetVerticeType();
  void SetVerticeSize(int);
  int GetVerticeSize();

  void MakeScreenshot(QWidget *, ScreenshotType);

  // object parameters
  unsigned GetVertexCount();
  unsigned GetFaceCount();
  unsigned GetEdgeCount();

 private:
  ModelFacade *model_;

  ControllerSingleton() : model_(){};
  ControllerSingleton(const ControllerSingleton &);
  ControllerSingleton &operator=(const ControllerSingleton &) = delete;
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
