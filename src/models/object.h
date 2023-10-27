#ifndef CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
#define CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <QVector>
#include <forward_list>
#include <unordered_set>
#include <algorithm>
using GLfloat = float;
using GLuint = unsigned int;
namespace s21
{

enum coordinate {X, Y, Z};
struct Vertex {
  float x{}, y{}, z{};
};

struct Face {
  std::vector<unsigned int> vertex_indices{};
};

struct VectorHash {
  template <typename T>
  std::size_t operator()(const std::vector<T>& vec) const {
    std::size_t seed = vec.size();
    for (const auto& element : vec) {
      seed ^= std::hash<T>{}(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

struct VectorEqual {
  template <typename T>
  bool operator()(const std::vector<T>& lhs, const std::vector<T>& rhs) const {
    return lhs == rhs;
  }
};

class Object {
 public:
  Object();
  Object(std::vector<Vertex>, std::vector<Face>);

  std::vector<Vertex> GetVertices();
  std::vector<Face> GetFaces();
  QVector<GLfloat> GetFlattenedVertices();
  QVector<GLuint> GetFlattenedFaces();

  std::vector<std::vector<unsigned>> faces;

  void SetVertices(std::vector<Vertex>);
  void SetFaces(std::vector<Face>);
  void SetVerticesInFaces(unsigned);
  void AddVertex(Vertex);
  void AddFace(Face);
  void Clear();
  size_t GetVertexCount();
  unsigned GetFaceCount();
  unsigned GetEdgeCount();
  float GetOffset(coordinate);
  void SetOffset(coordinate, float);
  float GetAngle(coordinate);
  void SetAngle(coordinate, float);
  void CountEdges();
 

 private:
  std::vector<Vertex> vertices_;
  std::vector<Face> faces_;
  float *vertices_array_;
  unsigned *faces_array_;
  unsigned vertex_count_{};
  unsigned face_count_{};
  unsigned edge_count_{};
  unsigned vertices_in_faces_{};
  float current_x_offset_{};
  float current_y_offset_{};
  float current_z_offset_{};
  float current_x_angle_{};
  float current_y_angle_{};
  float current_z_angle_{};
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
