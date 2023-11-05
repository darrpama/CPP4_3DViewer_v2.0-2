#include "obj_parser.h"
#include <chrono>
#include <iostream>

namespace s21 {

size_t OBJParser::CountVertices() {
  std::ifstream file(file_path_); 
  std::string line;
  size_t vertices_count = 0;

  while (std::getline(file, line)) {
    if (line.size() >= 2 && line[0] == 'v' && line[1] == ' ') {
      vertices_count++;
    }
  }

  return vertices_count;
}

void OBJParser::Parse() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream file(file_path_);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << file_path_ << std::endl;
    return;
  }
  
  std::string line;
  // std::vector<Vertex> vertices;
  size_t count = CountVertices();
  object_->Reserve(count);

  std::vector<Face> faces;
  unsigned vertices_in_faces = 0;
  while (std::getline(file, line)) {
    if (line.size() >= 2 && line[0] == 'v' && line[1] == ' ') {
      // Vertex v;
      // std::sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
      // vertices.emplace_back(v);
      float x, y, z;
      std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
      object_->PushBack(x, y, z);
    } 
    // else if (line.size() >= 2 && line[0] == 'f' && line[1] == ' ') {
    //   Face f;
    //   std::istringstream iss(line.substr(2));  // Remove the "f " part
    //   std::string vertex_index_str;

    //   while (iss >> vertex_index_str) {
    //     std::istringstream vertex_iss(vertex_index_str);
    //     std::string vertex_index;
    //     std::getline(vertex_iss, vertex_index, '/');  // Extract the vertex index

    //     int index = std::stoi(vertex_index);
    //     if (index < 0) {
    //       index = object_->GetVertexCount() + index + 1;
    //     }

    //     f.vertex_indices.push_back(static_cast<unsigned>(index));
    //     vertices_in_faces++;
    //   }
    //   faces.push_back(f);
    // }
  }

  // object_->SetFaces(faces);
  // object_->SetVerticesInFaces(vertices_in_faces);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "OBJParser::Parse() without triangulation Execution time: " << duration << " milliseconds" << std::endl;
  TriangulateFaces();
}

void s21::OBJParser::SetFilePath(const QString &file_path) {
  file_path_ = file_path.toStdString();
}

void OBJParser::SetObject(Object *object) {
  object_ = object;
}

void OBJParser::TriangulateFaces() {
  auto start = std::chrono::high_resolution_clock::now();
  
  const std::vector<Face>& original_faces = object_->GetFaces();
  std::vector<Face> triangulated_faces;
  triangulated_faces.reserve(original_faces.size());

  for (const auto& face : original_faces) {
    if (face.vertex_indices.size() > 3) {
      std::vector<Face> triangles = TriangulateFace(face);
      triangulated_faces.insert(triangulated_faces.end(), triangles.begin(), triangles.end());
    } else {
      triangulated_faces.push_back(face);
    }
  }

  object_->SetFaces(triangulated_faces);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "OBJParser::TriangulateFaces() Execution time: " << duration << " milliseconds" << std::endl;
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

void OBJParser::printQVector(const QVector<GLfloat>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

}  // namespace s21
