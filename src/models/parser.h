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



}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_PARSER_H