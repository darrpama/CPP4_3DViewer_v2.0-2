#include "object.h"

namespace s21 {

std::vector<GLfloat> Object::GetFlattenedVertices() {
  return *vertices_array_;
}

std::vector<GLuint> Object::GetFlattenedFaces() {
  return *triangulated_faces_array_;
}

std::vector<Face> Object::GetFaces() {
  return *raw_faces_array_;
}

void Object::Normalize() {
  auto max_value = std::max_element(
    vertices_array_->begin(), 
    vertices_array_->end()
  );

  auto min_value = std::min_element(
    vertices_array_->begin(), 
    vertices_array_->end()
  );

  GLfloat normalize_coef = (abs(*min_value) > abs(*max_value)) ? *min_value : *max_value;

  for (size_t i = 0; i < vertices_array_->size(); ++i) {
    (*vertices_array_)[i] /= normalize_coef;
  }
}

void Object::PushBackVertice(float x, float y, float z) {
  vertices_array_->push_back(x);
  vertices_array_->push_back(y);
  vertices_array_->push_back(z);
  vertex_count_++;
}

void Object::PushToFaceBuffer(GLuint v) {
  face_buffer_->push_back(v);
}

GLuint Object::GetFaceBufferAt(size_t i) {
  return face_buffer_->at(i);
}

size_t Object::GetFaceBufferSize() {
  return face_buffer_->size();
}

void Object::ClearFaceBuffer() {
  face_buffer_->clear();
}

void Object::PushToTriangleBuffer(GLuint v) {
  triangle_buffer_->push_back(v);
}

size_t Object::GetTriangleBufferSize() {
  return triangle_buffer_->size();
}

void Object::ClearTriangleBuffer() {
  triangle_buffer_->clear();
}

void Object::ReserveTriangleBuffer() {
  triangle_buffer_->reserve((GetFaceBufferSize() - 2) * 3);
}

void Object::AppendFace() {
  triangulated_faces_array_->insert(
    triangulated_faces_array_->end(), 
    face_buffer_->begin(), 
    face_buffer_->end()
  );
  face_count_++;
}

void Object::AppendRawFace() {
  Face face;
  std::vector<GLuint> tmp(*face_buffer_);
  for (auto it = tmp.begin(); it != tmp.end(); it++) {
    *it += 1;
  }
  face.vertices = tmp;
  raw_faces_array_->push_back(face);
}

void Object::AppendTriangulatedFace() {
  triangulated_faces_array_->insert(
    triangulated_faces_array_->end(),
    triangle_buffer_->begin(),
    triangle_buffer_->end()
  );
  // triangulated_faces_array_->append(*triangle_buffer_);
  face_count_++;
}

void Object::CountEdges() {
  std::unordered_set<std::vector<GLuint>, VectorHash, VectorEqual> edges;
  for (const auto& face : *raw_faces_array_) {
    int num_vertices = face.vertices.size();
    for (int i = 0; i < num_vertices; i++) {
      std::vector<GLuint> edge = {face.vertices[i], face.vertices[(i + 1) % num_vertices]};
      std::sort(edge.begin(), edge.end());
      edges.insert(edge);
    }
  }
  edge_count_ = edges.size();
}

void Object::SetRenderType(RenderType type) {
  render_type_ = type;
}
RenderType Object::GetRenderType() {
  return render_type_;
}

void Object::Clear() {
  vertices_array_->clear();
  triangulated_faces_array_->clear();
  raw_faces_array_->clear();
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
}

size_t Object::GetEdgeCount() {
  CountEdges();
  return edge_count_;
}

}  // namespace s21
