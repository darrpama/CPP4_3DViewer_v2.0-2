#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODELS_TYPE_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODELS_TYPE_H

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace s21 {

struct Type {
  using point = std::pair<double, double>;
  using points = std::vector<point>;
  using props = std::unordered_map<std::string, std::string>;
};

struct Vector3d {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODELS_MODEL_H