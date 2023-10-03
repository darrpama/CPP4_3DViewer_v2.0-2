#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H

#include "object.h"
#include "observable.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


namespace s21
{
class OBJParser
{
 public:
  OBJParser() {};
  void Parse();
  void SetFilePath(const std::string&);
  void SetObject(Object *);
  unsigned GetVertexCount();
  unsigned GetFaceCount();

 private:
  Object *object_;
  std::string file_path_;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H