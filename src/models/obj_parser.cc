#include "obj_parser.h"
#include <chrono>
#include <iostream>

namespace s21 {

void s21::OBJParser::SetFilePath(const QString &file_path) {
  file_path_ = file_path.toStdString();
}

void OBJParser::SetObject(Object *object) {
  object_ = object;
}

void OBJParser::Parse() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream file(file_path_);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << file_path_ << std::endl;
    return;
  }

  // Read the entire file into a string
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  size_t pos = 0;
  size_t file_content_size = file_content.size();

  while (pos < file_content_size) {
    size_t line_end = file_content.find('\n', pos);
    std::string line = file_content.substr(pos, line_end - pos);

    ParseVertices(line);
    ParseFaces(line);

    pos = line_end + 1;
  }

  file.close();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "OBJParser::Parse vertices exec time: " << duration << " milliseconds" << std::endl;
}

void OBJParser::ParseVertices(std::string &line) {
  if (line.size() >= 2 && std::strncmp(line.c_str(), "v ", 2) == 0) {
    char* end;
    float x = std::strtof(line.c_str() + 2, &end);
    float y = std::strtof(end, &end);
    float z = std::strtof(end, nullptr);
    object_->PushBackVertice(x, y, z);
  }
}

void OBJParser::ParseFaces(std::string &line) {
  if (line.size() >= 2 && line[0] == 'f' && line[1] == ' ') {
    object_->ClearFaceBuffer();
    std::istringstream iss(line.data() + 2);  // Remove the "f " part
    face_element_.clear();
    while (iss >> face_element_) {
      std::istringstream element_stream(face_element_);
      std::string vertex_index_str;
      std::getline(element_stream, vertex_index_str, '/');  // Extract the vertex index
      int vertex_index = std::stoi(vertex_index_str);
      if (vertex_index < 0) {
        vertex_index = object_->GetVertexCount() + vertex_index + 1;
      }
      object_->PushToFaceBuffer(std::move(vertex_index - 1));
    }

    size_t face_vertices_size = object_->GetFaceBufferSize();
    object_->AppendRawFace();

    if (face_vertices_size > 3) {
      // Triangulate
      object_->ClearTriangleBuffer();
      object_->ReserveTriangleBuffer();
      for (size_t i = 1; i < face_vertices_size - 1; ++i) {
        object_->PushToTriangleBuffer(object_->GetFaceBufferAt(0));
        object_->PushToTriangleBuffer(object_->GetFaceBufferAt(i));
        object_->PushToTriangleBuffer(object_->GetFaceBufferAt(i + 1));
      }
      object_->SetRenderType(RenderType::TRIANGLE_RENDER);
      object_->AppendTriangulatedFace();
    } else if (face_vertices_size < 3) {
      object_->SetRenderType(RenderType::LINE_RENDER);
      object_->AppendFace();
    } else {
      object_->SetRenderType(RenderType::TRIANGLE_RENDER);
      object_->AppendFace();
    }
  }
}

}  // namespace s21
