#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H

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

struct Texture
{
  float u,v;
};

struct Face
{
  int v1, v2, v3;
  int n1, n2, n3;
  int t1, t2, t3;
};


class Object
{
  public:
    Object(std::vector<Vertex>, std::vector<Texture>, std::vector<Normal>, std::vector<Face>);
    std::vector<Vertex> GetVertices();
    std::vector<Texture> GetTextures();
    std::vector<Normal> GetNormals();
    std::vector<Face> GetFaces();
    void SetVertices(std::vector<Vertex>);
    void SetTextures(std::vector<Texture>);
    void SetNormals(std::vector<Normal>);
    void SetFaces(std::vector<Face>);

  private:
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<Normal> normals;
    std::vector<Face> faces;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H