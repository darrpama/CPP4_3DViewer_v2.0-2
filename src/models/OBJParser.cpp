#include "OBJParser.h"

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
    }
    else if (line.substr(0, 2) == "f ")
    {
      //  First number after ' '
      Face f;


      object_.AddFace(f);
    }
  }
}