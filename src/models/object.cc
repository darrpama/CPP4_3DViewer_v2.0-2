#include "object.h"

namespace s21 {

Object::Object()
    : vertices_array_(),
      faces_array_(),
      vertex_count_(0), 
      face_count_(0),
      edge_count_(0) {}

QVector<GLfloat> Object::GetFlattenedVertices() {
  return vertices_array_;
}

QVector<GLuint> Object::GetFlattenedFaces() {
  return faces_array_;
}

void Object::PushBackVertice(float x, float y, float z) {
  vertices_array_.push_back(x);
  vertices_array_.push_back(y);
  vertices_array_.push_back(z);
  vertex_count_++;
}

void Object::AppendFace(QVector<GLuint> face) {
  faces_array_.append(face);
  face_count_++;
}

void Object::CountEdges() {
  // std::unordered_set<std::vector<unsigned>, VectorHash, VectorEqual> edges;
  // for (const auto& face : faces_) {
  //   int num_vertices = face.vertex_indices.size();
  //   for (int i = 0; i < num_vertices; i++) {
  //     std::vector<unsigned> edge = {face.vertex_indices[i], face.vertex_indices[(i + 1) % num_vertices]};
  //     std::sort(edge.begin(), edge.end());
  //     edges.insert(edge);
  //   }
  // }
  // edge_count_ = edges.size();
  edge_count_ = 0;
}

void Object::Clear() {
  vertices_array_.clear();
  faces_array_.clear();
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
}

size_t Object::GetEdgeCount() {
  // CountEdges();
  return edge_count_;
}

}  // namespace s21
