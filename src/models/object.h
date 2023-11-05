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
  QVector<GLfloat> GetFlattenedVertices();
  QVector<GLuint> GetFlattenedFaces();

  void Clear();
  void CountEdges();
  size_t GetVertexCount() { return vertex_count_; }
  size_t GetFaceCount() { return face_count_; }
  size_t GetEdgeCount();

  void PushBackVertice(float, float, float);
  void AppendFace(QVector<GLuint> face);

 private:
  QVector<GLfloat> vertices_array_;
  QVector<GLuint> faces_array_;

  size_t vertex_count_{};
  size_t face_count_{};
  size_t edge_count_{};
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
