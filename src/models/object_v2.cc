#include "object.h"

namespace s21 {

Object::Object()
    : vertex_count_(0), 
      face_count_(0),
      edge_count_(0) {}

void Object::AddVertex(float x, float y, float z) {
  vertices_array_.push_back(x);
  vertices_array_.push_back(y);
  vertices_array_.push_back(z);
  vertex_count_++;
}

void Object::AddFace(QVector<GLuint> face_indices) {
  faces_array_.append(face_indices);
  face_count_++;
}

// void Object::CountEdges() {
//   std::unordered_set<std::vector<unsigned>, VectorHash, VectorEqual> edges;
//   for (const auto& face : faces_) {
//     int num_vertices = face.vertex_indices.size();
//     for (int i = 0; i < num_vertices; i++) {
//       std::vector<unsigned> edge = {face.vertex_indices[i], face.vertex_indices[(i + 1) % num_vertices]};
//       std::sort(edge.begin(), edge.end());
//       edges.insert(edge);
//     }
//   }
//   edge_count_ = edges.size();
// }

QVector<GLfloat> Object::GetFlattenedVertices() {
  return vertices_array_;
}

QVector<GLuint> Object::GetFlattenedFaces() {
  return faces_array_;
}

void Object::Clear() {
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
}

}  // namespace s21
