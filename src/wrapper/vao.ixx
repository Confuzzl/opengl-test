module;

#include "util/gl_utils.hpp"

export module wrapper.vao;

import wrapper.gl_object;
import wrapper.buffer_object;

export struct VAO : public GLObject {
  const VBO *boundedVBO = nullptr;
  const EBO *boundedEBO = nullptr;
  GLsizei stride = -1;

  constexpr VAO(const GLsizei stride) : stride{stride} {}
  ~VAO();

  void bindVBO(const VBO &vbo);
  void bindEBO(const EBO &ebo);

  void bindVertexArray();
};