#include "object.h"

namespace s21 {

QVector<GLfloat> Object::GetFlattenedVertices() {
  return *vertices_array_;
}

QVector<GLuint> Object::GetFlattenedFaces() {
  return *faces_array_;
}

void Object::Normalize() {
  
  GLfloat max_value = *std::max_element(
    vertices_array_->constBegin(), 
    vertices_array_->constEnd()
  );

  GLfloat min_value = *std::min_element(
    vertices_array_->constBegin(), 
    vertices_array_->constEnd()
  );

  GLfloat normalize_coef = (abs(min_value) > abs(max_value)) ? min_value : max_value;

  for (int i = 0; i < vertices_array_->size(); ++i) {
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
  faces_array_->append(*face_buffer_);
  face_count_++;
}

void Object::AppendTriangulatedFace() {
  faces_array_->append(*triangle_buffer_);
  face_count_++;
}

void Object::CountEdges() {
  // std::unordered_set<std::vector<unsigned>, VectorHash, VectorEqual> edges;
  // for (const auto& face : faces_) {
  //   int num_vertices = face.vertex_indices.size();
  //   for (int i = 0; i < num_vertices; i++) {
  //     std::vector<unsigned> edge = {face.vertex_indices[i], face.vertex_indices[(i + 1) % num_vertices]};
  //     std::sort(edge.begin(), edge.end());
  //     edges.insert(edge);
  //   }
  // }
  // edge_count_ = edges.size();
  edge_count_ = 0;
}

void Object::SetRenderType(RenderType type) {
  render_type_ = type;
}
RenderType Object::GetRenderType() {
  return render_type_;
}

void Object::Clear() {
  vertices_array_->clear();
  faces_array_->clear();
  vertex_count_ = 0;
  face_count_ = 0;
  edge_count_ = 0;
}

size_t Object::GetEdgeCount() {
  // CountEdges();
  return edge_count_;
}

}  // namespace s21
