module;

#include "util/gl_utils.hpp"
#include <iostream>

export module wrapper.program.vertex_formats:font;

export struct FontVertex {
  static const GLsizeiptr POS_WIDTH = 2 * sizeof(GLfloat);
  static const GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + TEX_WIDTH;

  GLfloat posInfo[2];
  GLushort texInfo[2];

  FontVertex() = default;
  FontVertex(GLfloat x, GLfloat y, GLushort u, GLushort v);

  friend std::ostream &operator<<(std::ostream &os, const FontVertex &vertex);
};