#include "vao.h"
#include "util/debug_utils.h"
VAO::VAO(const GLsizei stride) : stride{stride} {}
VAO::~VAO() {
  glDeleteVertexArrays(1, &ID);
  // std::cout << std::format("vao {} deleted\n", ID);
}

void VAO::bindVBO(const VBO &vbo) {
  if (!vbo.allocated)
    throw UnallocatedGLObjectUsageException{
        "VBO {} WAS BINDED BEFORE ALLOCATION\n"};
  glVertexArrayVertexBuffer(ID, 0, vbo.ID, 0, stride);
  boundedVBO = vbo;
  // std::cout << std::format("vbo {} binded to vao {}\n", ID, this->ID);
}
void VAO::bindEBO(const EBO &ebo) {
  if (!ebo.allocated)
    throw UnallocatedGLObjectUsageException{
        "EBO {} WAS BINDED BEFORE ALLOCATION\n"};
  glVertexArrayElementBuffer(ID, ebo.ID);
  boundedEBO = ebo;
  // std::cout << std::format("ebo {} binded to vao {}\n", ID, this->ID);
}

void VAO::bindVertexArray() {
  if (!allocated)
    throw UnallocatedGLObjectUsageException{
        "VAO {} WAS BINDED BEFORE ALLOCATION\n"};
  glBindVertexArray(ID);
}