#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H

#include "object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


namespace s21
{
class OBJParser {
 public:
  OBJParser(Object *obj) : object_(obj) {};
  void Parse();
  void SetFilePath(const std::string&);
  void SetObject(Object *);
  std::vector<Face> TriangulateFace(const Face& face);

 private:
  Object *object_;
  std::string file_path_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H