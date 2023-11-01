#include "obj_parser.h"
#include <chrono>
#include <iostream>

namespace s21 {

void OBJParser::Parse() {
  auto start = std::chrono::high_resolution_clock::now();
  
  std::ifstream file(file_path_);
  std::string line;
  unsigned vertices_in_faces = 0;

  while (std::getline(file, line)) {
    if (line.size() >= 2 && line[0] == 'v' && line[1] == ' ') {
      Vertex v;
      std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
      object_->AddVertex(v);
    } else if (line.size() >= 2 && line[0] == 'f' && line[1] == ' ') {
      Face f;
      std::istringstream iss(line.substr(2));  // Remove the "f " part
      std::string vertex_index_str;

      while (iss >> vertex_index_str) {
        std::istringstream vertex_iss(vertex_index_str);
        std::string vertex_index;
        std::getline(vertex_iss, vertex_index, '/');  // Extract the vertex index

        int index = std::stoi(vertex_index);
        if (index < 0) {
          index = object_->GetVertexCount() + index + 1;
        }

        f.vertex_indices.push_back(static_cast<unsigned>(index));
        vertices_in_faces++;
      }

      object_->AddFace(f);
      object_->SetVerticesInFaces(vertices_in_faces);
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "OBJParser::Parse() without triangulation Execution time: " << duration << " milliseconds" << std::endl;

  auto start2 = std::chrono::high_resolution_clock::now();
  // Triangulation
  std::vector<Face> triangulated_faces;
  for (const auto& face : object_->GetFaces()) {
    if (face.vertex_indices.size() > 3) {
      std::vector<Face> triangles = TriangulateFace(face);
      triangulated_faces.insert(triangulated_faces.end(), triangles.begin(), triangles.end());
    }
    else {
      triangulated_faces.push_back(face);
    }
  }
  object_->SetFaces(triangulated_faces);

  auto end2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
  std::cout << "OBJParser::Parse() only triangulation Execution time: " << duration2 << " milliseconds" << std::endl;
}

void s21::OBJParser::SetFilePath(const std::string &file_path) {
  file_path_ = file_path;
}

void OBJParser::SetObject(Object *object) {
  object_ = object;
}

std::vector<Face> OBJParser::TriangulateFace(const Face& face) {
  std::vector<Face> triangles;

  unsigned first_vertex = face.vertex_indices[0];
  for (unsigned int i = 1; i < face.vertex_indices.size() - 1; ++i) {
    Face triangle;
    triangle.vertex_indices.push_back(first_vertex);
    triangle.vertex_indices.push_back(face.vertex_indices[i]);
    triangle.vertex_indices.push_back(face.vertex_indices[i + 1]);
    triangles.push_back(triangle);
  }
  return triangles;
}

}  // namespace s21
