#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TYPE_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TYPE_H

namespace s21 {

enum EdgeType {NO_EDGE, SOLID, DASHED};
enum VerticeType {NO_VERTICE, CIRCLE, SQUARE};
enum ProjectionType {CENTRAL, PARALLEL};
enum ColorType {BG_COLOR, VERTICE_COLOR, EDGE_COLOR};
enum ScreenshotType {BMP, JPG};

struct Color {
  int red;
  int green;
  int blue;

  Color(int r, int g, int b) 
    : red(r)
    , green(g)
    , blue(b) {}

  float redF() { return (float) red / 255.0f; }
  float greenF() { return (float) green / 255.0f; }
  float blueF() { return (float) blue / 255.0f; }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_TYPE_H