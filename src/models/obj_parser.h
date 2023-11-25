#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H

#include "object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
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
