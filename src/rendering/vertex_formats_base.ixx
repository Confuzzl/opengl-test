module;

#include "util/gl_utils.hpp"

export module rendering.vertex_formats;

import <array>;

export namespace VertexFormats {
template <std::size_t n> struct Vertex {
  static constexpr GLsizeiptr POS_WIDTH = n * sizeof(GLfloat);

  std::array<GLfloat, n> posInfo;

  template <typename... Args> Vertex(Args &&...pos) : posInfo{{pos...}} {}

  virtual void writeVertexTo(GLintptr &offset, const GLuint vboID) const = 0;
};
struct Colorable {
  static constexpr GLsizeiptr COL_WIDTH = 3 * sizeof(GLubyte);

  std::array<GLubyte, 3> colInfo;

  Colorable(GLubyte r, GLubyte g, GLubyte b) : colInfo{{r, g, b}} {}
};
struct Texturable {
  static constexpr GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);

  std::array<GLushort, 2> texInfo;

  Texturable(GLushort u, GLushort v) : texInfo{{u, v}} {}
};
} // namespace VertexFormats