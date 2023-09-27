#include "parser.h"

using namespace s21;

void Parser::parse()
{
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line))
  {
    if (line.substr(0, 2) == "v ")
    {
      Vertex v;
      std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
      vertices.push_back(v);
    }
    else if (line.substr(0, 3) == "vn ")
    {
      Normal n;
      std::sscanf(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
      normals.push_back(n);
    }
    else if (line.substr(0, 3) == "vt ")
    {
      TextureCoordinate t;
      std::sscanf(line.c_str(), "vt %f %f", &t.u, &t.v);
      textureCoordinates.push_back(t);
    }
    else if (line.substr(0, 2) == "f ")
    {
      Face f;
      std::sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
        &f.v1, &f.t1, &f.n1,
        &f.v2, &f.t2, &f.n2,
        &f.v3, &f.t3, &f.n3);
      faces.push_back(f);
    }
  }
}