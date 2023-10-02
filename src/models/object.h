#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <forward_list>

namespace s21
{

struct Vertex
{
  float x{}, y{}, z{};
};

struct Face
{
  std::vector<unsigned> vertex_indices{};
};


class Object
{
  public:
    Object();
    Object(std::vector<Vertex>, std::vector<Face>);
    std::vector<Vertex> GetVertices();
    std::vector<Face> GetFaces();
    void SetVertices(std::vector<Vertex>);
    void SetFaces(std::vector<Face>);
    void AddVertex(Vertex);
    void AddFace(Face);

  private:
    std::vector<Vertex> vertices_;
    std::vector<Face> faces;
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H