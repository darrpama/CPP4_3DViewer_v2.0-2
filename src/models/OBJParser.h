#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Object.h"

namespace s21
{

class OBJParser
{
  public:
    OBJParser(const std::string& filepath) : filepath(filepath) {};
    void Parse();
    Object GetObject();

  private:
    std::string filepath;
    Object object;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJPARSER_H