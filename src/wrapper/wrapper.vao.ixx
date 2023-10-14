module;

#include "util/gl_utils.h"

export module wrapper.vao;

import wrapper.gl_object;
import wrapper.buffer_object;

export struct VAO : public GLObject {
  VBO boundedVBO;
  EBO boundedEBO;
  GLsizei stride;

  VAO(const GLsizei stride);
  ~VAO();

  void bindVBO(const VBO &vbo);
  void bindEBO(const EBO &ebo);

  void bindVertexArray();
};