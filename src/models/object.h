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

struct Face {
  QVector<GLuint> vertices;
};

struct VectorHash {
  template <typename T>
  std::size_t operator()(const QVector<T>& vec) const {
    std::size_t seed = vec.size();
    for (const auto& element : vec) {
      seed ^= std::hash<T>{}(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

struct VectorEqual {
  template <typename T>
  bool operator()(const QVector<T>& lhs, const QVector<T>& rhs) const {
    return lhs == rhs;
  }
};

class Object {
 public:
  Object(
    QVector<GLfloat> *v_array, 
    QVector<GLuint> *f_array, 
    QVector<GLuint> *f_buffer, 
    QVector<GLuint> *t_buffer,
    QVector<Face> *raw_faces_array_)
      : vertices_array_(v_array)
      , triangulated_faces_array_(f_array)
      , face_buffer_(f_buffer)
      , triangle_buffer_(t_buffer) 
      , raw_faces_array_(raw_faces_array_) {}
  QVector<GLfloat> GetFlattenedVertices();
  QVector<GLuint> GetFlattenedFaces();

  void Clear();
  void CountEdges();
  size_t GetVertexCount() { return vertex_count_; }
  size_t GetFaceCount() { return face_count_; }
  size_t GetEdgeCount();

  void PushBackVertice(float, float, float);
  void AppendRawFace();
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
  QVector<GLuint> *triangulated_faces_array_;
  QVector<GLuint> *face_buffer_;
  QVector<GLuint> *triangle_buffer_;
  QVector<Face> *raw_faces_array_;
  RenderType render_type_;

  size_t vertex_count_{};
  size_t face_count_{};
  size_t edge_count_{};
};

}

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_MODELS_OBJECT_H
