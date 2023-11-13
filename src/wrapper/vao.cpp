module;

#include "util/gl_utils.hpp"

module wrapper.vao;

import wrapper.buffer_object;
import util.debug;

VAO::VAO(const GLsizei stride) : stride{stride} {}
VAO::~VAO() {
  glDeleteVertexArrays(1, &ID);
  // std::cout << std::format("vao {} deleted\n", ID);
}

void VAO::bindVBO(const VBO *vbo) {
  if (not vbo->allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("VBO {} WAS BINDED BEFORE ALLOCATION\n", vbo->ID)};
  glVertexArrayVertexBuffer(ID, 0, vbo->ID, 0, stride);
  boundedVBO = vbo;
  // std::cout << std::format("vbo {} binded to vao {}\n", ID, this->ID);
}
void VAO::bindEBO(const EBO *ebo) {
  if (not ebo->allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("EBO {} WAS BINDED BEFORE ALLOCATION\n", ebo->ID)};
  glVertexArrayElementBuffer(ID, ebo->ID);
  boundedEBO = ebo;
  // std::cout << std::format("ebo {} binded to vao {}\n", ID, this->ID);
}

void VAO::bindVertexArray() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("VAO {} WAS BINDED BEFORE ALLOCATION\n", ID)};
  glBindVertexArray(ID);
}