module;

#include "util/gl_utils.hpp"

module wrapper.vao;

import wrapper.buffer_object;
import util.debug;

// VAO::VAO(const GLsizei stride) : stride{stride} {}
VAO::~VAO() { glDeleteVertexArrays(1, &GLid); }

void VAO::bindVBO(const VBO &vbo) {
  if (not vbo.allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("VBO {} WAS BINDED BEFORE ALLOCATION\n", vbo.GLid)};
  glVertexArrayVertexBuffer(GLid, 0, vbo.GLid, 0, stride);
  boundedVBO = &vbo;
}
void VAO::bindEBO(const EBO &ebo) {
  if (not ebo.allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("EBO {} WAS BINDED BEFORE ALLOCATION\n", ebo.GLid)};
  glVertexArrayElementBuffer(GLid, ebo.GLid);
  boundedEBO = &ebo;
}

void VAO::bindVertexArray() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("VAO {} WAS BINDED BEFORE ALLOCATION\n", GLid)};
  glBindVertexArray(GLid);
}