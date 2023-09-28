#include "Object.h"

using namespace s21;


Object::Object(std::vector<Vertex> vertices,
               std::vector<Texture> textures,
               std::vector<Normal> normals,
               std::vector<Face> faces) :
               vertices(vertices),
               textures(textures),
               normals(normals),
               faces(faces) {};


std::vector<Vertex> Object::GetVertices()
{
  return vertices;
}


std::vector<Texture> Object::GetTextures()
{
  return textures;
}


std::vector<Normal> Object::GetNormals()
{
  return normals;
}


std::vector<Face> Object::GetFaces()
{
  return faces;
}


void Object::SetVertices(std::vector<Vertex> vertices) 
{
  this->vertices = vertices;
}


void Object::SetTextures(std::vector<Texture> textures) 
{
  this->textures = textures;
}


void Object::SetNormals(std::vector<Normal> normals) 
{
  this->normals = normals;
}


void Object::SetFaces(std::vector<Face> faces) 
{
  this->faces = faces;
}