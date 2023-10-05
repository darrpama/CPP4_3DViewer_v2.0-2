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

std::vector<Face> Object::GetFaces() {
  return faces_;
}

void Object::SetVertices(std::vector<Vertex> vertices)  {
  vertices_ = vertices;
}

void Object::SetFaces(std::vector<Face> faces)  {
  faces_ = faces;
}

void Object::AddVertex(Vertex vertex) {
  vertices_.push_back(vertex);
  vertex_count_++;
}

void Object::AddFace(Face face) {
  faces_.push_back(face);
  face_count_++;
}

unsigned Object::GetVertexCount() {
  return vertex_count_;
}

unsigned Object::GetFaceCount() {
  return face_count_;
}

unsigned Object::GetEdgeCount() {
  return edge_count_;
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

void Object::Clear()
{
  faces_.clear();
  vertices_.clear();
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
}

}  // namespace s21