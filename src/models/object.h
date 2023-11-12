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
enum RenderType {TRIANGLE_RENDER, LINE_RENDER};

struct Vertex {
  float x;
  float y;
  float z;
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
  Object(
    QVector<GLfloat> *v_array, 
    QVector<GLuint> *f_array, 
    QVector<GLuint> *f_buffer, 
    QVector<GLuint> *t_buffer)
      : vertices_array_(v_array)
      , faces_array_(f_array)
      , face_buffer_(f_buffer)
      , triangle_buffer_(t_buffer) {}
  QVector<GLfloat> GetFlattenedVertices();
  QVector<GLuint> GetFlattenedFaces();

  void Clear();
  void CountEdges();
  size_t GetVertexCount() { return vertex_count_; }
  size_t GetFaceCount() { return face_count_; }
  size_t GetEdgeCount();

  void PushBackVertice(float, float, float);
  void AppendFace();
  void AppendTriangulatedFace();
  void SetRenderType(RenderType);
  RenderType GetRenderType();

  void ClearFaceBuffer();
  GLuint GetFaceBufferAt(size_t i);
  void PushToFaceBuffer(GLuint);
  size_t GetFaceBufferSize();

  void ClearTriangleBuffer();
  void PushToTriangleBuffer(GLuint);
  size_t GetTriangleBufferSize();
  void ReserveTriangleBuffer();

  void Normalize();

 private:
  QVector<GLfloat> *vertices_array_;
  QVector<GLuint> *faces_array_;
  QVector<GLuint> *face_buffer_;
  QVector<GLuint> *triangle_buffer_;
  RenderType render_type_;

  size_t vertex_count_{};
  size_t face_count_{};
  size_t edge_count_{};
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
