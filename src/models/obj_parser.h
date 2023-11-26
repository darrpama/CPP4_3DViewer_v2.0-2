#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "object.h"

namespace s21 {
class OBJParser {
 public:
  explicit OBJParser(Object *obj) : object_(obj){};
  void Parse();
  void SetFilePath(const std::string &);

 private:
  Object *object_;
  std::string face_element_;
  std::string file_path_;

  void ParseVertices(std::string &);
  void ParseFaces(std::string &);
  void CheckAndFixEndLine();
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
