#include "object.h"

namespace s21 {

Object::Object()
    : vertices_(),
      faces_(),
      vertex_count_(0), 
      face_count_(0),
      edge_count_(0) {}

Object::Object(std::vector<Vertex> vertices, std::vector<Face> faces)
    : vertices_(std::move(vertices)), faces_(std::move(faces)),
      vertex_count_(vertices_.size()), face_count_(faces_.size()) {}

std::vector<Vertex> Object::GetVertices() {
  return vertices_;
}

QVector<GLfloat> Object::GetFlattenedVertices() {
  // QVector<GLfloat> float_array;
  // float_array.reserve(vertices_.size() * 3);
  // for (const auto& vertex : vertices_) {
  //   float_array.push_back(vertex.x);
  //   float_array.push_back(vertex.y);
  //   float_array.push_back(vertex.z);
  // }
  // return float_array;
  return flattened_vertices_array_;
}

QVector<GLuint> Object::GetFlattenedFaces() {
  QVector<GLuint> int_array;
  int_array.reserve(faces_.size() * 3);
  for (const auto& face : faces_) {
    for (const auto& index : face.vertex_indices) {
      int_array.push_back(index-1);
    }
  }
  return int_array;
}

std::vector<Face> Object::GetFaces() {
  return faces_;
}

void Object::SetFaces(std::vector<Face> faces)  {
  faces_ = faces;
  face_count_ = faces.size();
}

void Object::PushBack(float x, float y, float z) {
  flattened_vertices_array_.push_back(x);
  flattened_vertices_array_.push_back(y);
  flattened_vertices_array_.push_back(z);
  vertex_count_++;
}

void Object::Reserve(size_t size) {
  flattened_vertices_array_.reserve(size);
}

void Object::AddVertex(Vertex vertex) {
  vertices_.push_back(vertex);
  vertex_count_++;
}

void Object::AddFace(Face face) {
  faces_.push_back(face);
  face_count_++;
}

void Object::CountEdges() {
  std::unordered_set<std::vector<unsigned>, VectorHash, VectorEqual> edges;
  for (const auto& face : faces_) {
    int num_vertices = face.vertex_indices.size();
    for (int i = 0; i < num_vertices; i++) {
      std::vector<unsigned> edge = {face.vertex_indices[i], face.vertex_indices[(i + 1) % num_vertices]};
      std::sort(edge.begin(), edge.end());
      edges.insert(edge);
    }
  }
  edge_count_ = edges.size();
}

void Object::SetVerticesInFaces(unsigned vertices_in_faces) {
  this->vertices_in_faces_ = vertices_in_faces;
}

void Object::Clear() {
  faces_.clear();
  vertices_.clear();
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
  vertices_in_faces_ = 0;
}

size_t Object::GetEdgeCount() {
  // CountEdges();
  return edge_count_;
}

}  // namespace s21
