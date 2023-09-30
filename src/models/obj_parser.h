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

class OBJParser
{
  public:
    OBJParser(const std::string& filepath) : filepath_(filepath) {};
    void Parse();
    Object GetObject();
    unsigned GetVertexCount();
    unsigned GetFaceCount();

  private:
    std::string filepath_;
    Object object_{};
    unsigned vertex_count_{};
    unsigned face_count_{};
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJ_PARSER_H