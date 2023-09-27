#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_PARSER_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace s21
{

struct Vertex
{
  float x, y, z;
};

struct Normal
{
  float x, y, z;
};

struct TextureCoordinate
{
  float u,v;
};

struct Face
{
  int v1, v2, v3;
  int n1, n2, n3;
  int t1, t2, t3;
};



class Parser
{
  public:
    Parser(const std::string& filename) : filename(filename) {};
    void parse();

  private:
    std::string filename;
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    std::vector<TextureCoordinate> textureCoordinates;
    std::vector<Face> faces;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_PARSER_H