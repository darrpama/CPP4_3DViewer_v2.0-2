#include "obj_parser.h"

namespace s21 {
  void OBJParser::Parse() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream file(file_path_);
    if (!file.is_open()) {
      std::cerr << "Failed to open file: " << file_path_ << std::endl;
      return;
    }
    std::string line;
    unsigned vertices_in_faces = 0;
    while (std::getline(file, line)) {
      if (line.size() >= 2 && line.substr(0, 2) == "v ") {
        float x, y, z = {};
        std::istringstream iss(line.substr(2));
        iss >> x >> y >> z;
        vertices_array.push_back(x);
        vertices_array.push_back(y);
        vertices_array.push_back(z);
      } else if (line.size() >= 2 && line.substr(0, 2) == "f ") {
        std::istringstream iss(line.substr(2));
        std::string vertex_index_str;
        unsigned vertice_in_face = 0;
        QVector<GLuint> face_indices;
        while (iss >> vertex_index_str) {
          vertices_in_faces++;
          vertice_in_face++;
          std::istringstream vertex_iss(vertex_index_str);
          std::string vertex_index;
          std::getline(vertex_iss, vertex_index, '/');
          int index = std::stoi(vertex_index);
          if (index < 0) {
            index = object_->GetVertexCount() + index + 1;
          }
          face_indices.push_back(static_cast<unsigned>(index));
        }
        if (vertice_in_face > 3) {
          TriangulateFace(face_indices);
        }
        faces_array.append(face_indices);
        object_->SetVerticesInFaces(vertices_in_faces);
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "OBJParser::Parse() without triangulation Execution time: " << duration << " milliseconds" << std::endl;
  }

  void OBJParser::SetFilePath(const std::string& file_path) {
    file_path_ = file_path;
  }

  void OBJParser::SetObject(Object* object) {
    object_ = object;
  }

  std::vector<unsigned> OBJParser::TriangulateFace(const std::vector<unsigned>& face_indices) {
    std::vector<unsigned> triangulated_indices;
    unsigned first_vertex = face_indices[0];
    for (unsigned int i = 1; i < face_indices.size() - 1; ++i) {
      triangulated_indices.push_back(first_vertex);
      triangulated_indices.push_back(face_indices[i]);
      triangulated_indices.push_back(face_indices[i + 1]);
    }
    return triangulated_indices;
  }
}  // namespace s21
