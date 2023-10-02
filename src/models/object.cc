#include "Object.h"

using namespace s21;

Object::Object() :
              vertices_(),
              faces_() {};


Object::Object(std::vector<Vertex> vertices,
               std::vector<Face> faces) :
               vertices_(vertices),
               faces_(faces) {};

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