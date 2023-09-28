#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H

#include "Object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace s21
{

class OBJParser
{
  public:
    OBJParser(const std::string& filepath) : filepath_(filepath) {};
    void Parse();
    Object GetObject();

  private:
    std::string filepath_;
    Object object_{};
    unsigned vertex_count_;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H