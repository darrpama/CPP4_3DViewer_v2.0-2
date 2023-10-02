#include "obj_parser.h"

using namespace s21;

void OBJParser::Parse()
{
  std::ifstream file(filepath_);
  std::string line;

  while (std::getline(file, line))
  {
    if (line.substr(0, 2) == "v ")
    {
      Vertex v;
      std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
      object_.AddVertex(v);
      vertex_count_++;
    }
    else if (line.substr(0, 2) == "f ")
    {
      Face f;
      std::istringstream iss(line.substr(2)); // Remove the "f " part
      std::string vertexIndexStr;

      while (iss >> vertexIndexStr)
      {
        std::istringstream vertexIss(vertexIndexStr);
        std::string vertexIndex;
        std::getline(vertexIss, vertexIndex, '/'); // Extract the vertex index

        // Convert the vertex index to an integer and add it to the face
        f.vertex_indices.push_back(std::stoi(vertexIndex));
      }

      object_.AddFace(f);
      face_count_++;
    }
  }
}


unsigned OBJParser::GetVertexCount()
{
  return vertex_count_;
}


unsigned OBJParser::GetFaceCount()
{
  return face_count_;
}


Object OBJParser::GetObject()
{
  return object_;
}