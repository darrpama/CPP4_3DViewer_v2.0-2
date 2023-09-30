#include "object.h"

using namespace s21;

Object::Object() :
              vertices_(),
              faces() {};


Object::Object(std::vector<Vertex> vertices,
               std::vector<Face> faces) :
               vertices_(vertices),
               faces(faces) {};


std::vector<Vertex> Object::GetVertices()
{
  return vertices_;
}


std::vector<Face> Object::GetFaces()
{
  return faces;
}


void Object::SetVertices(std::vector<Vertex> vertices) 
{
  this->vertices_ = vertices;
}


void Object::SetFaces(std::vector<Face> faces) 
{
  this->faces = faces;
}


void Object::AddVertex(Vertex vertex)
{
  this->vertices_.push_back(vertex);
}


void Object::AddFace(Face face)
{
  this->faces.push_back(face);
}