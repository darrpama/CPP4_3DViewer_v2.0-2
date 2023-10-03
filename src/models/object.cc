#include "Object.h"

namespace s21 {

Object::Object() :
              vertices_(),
              faces_(),
              vertex_count_(0), 
              face_count_(0) {};

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

void Object::Clear() {
  faces_.clear();
  vertices_.clear();
  vertex_count_ = 0;
  face_count_ = 0;
}

}  // namespace s21