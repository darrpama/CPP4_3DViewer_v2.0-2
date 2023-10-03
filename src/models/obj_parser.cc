#include "obj_parser.h"

namespace s21 {

void OBJParser::Parse() {
  std::ifstream file(file_path_);
  std::string line;

  while (std::getline(file, line)) {
    if (line.substr(0, 2) == "v ") {
      Vertex v;
      std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
      object_->AddVertex(v);
    }
    else if (line.substr(0, 2) == "f ") {
      Face f;
      std::istringstream iss(line.substr(2));  // Remove the "f " part
      std::string vertex_index_str;

      while (iss >> vertex_index_str) {
        std::istringstream vertex_iss(vertex_index_str);
        std::string vertex_index;
        std::getline(vertex_iss, vertex_index, '/');  // Extract the vertex index

        // Convert the vertex index to an integer and add it to the face
        f.vertex_indices.push_back(std::stoi(vertex_index));
      }

      object_->AddFace(f);
    }
  }
}

void s21::OBJParser::SetFilePath(const std::string &file_path) {
  file_path_ = file_path;
}

void OBJParser::SetObject(Object *object) {
  object_ = object;
}

}  // namespace s21
