module;

#include "util/gl_utils.hpp"
#include <iostream>

export module wrapper.program.vertex_formats:simple;

export struct SimpleVertex {
  static const GLsizeiptr POS_WIDTH = 3 * sizeof(GLfloat);
  static const GLsizeiptr COL_WIDTH = 3 * sizeof(GLubyte);
  static const GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH + TEX_WIDTH;

  GLfloat posInfo[3];
  GLubyte colInfo[3];
  GLushort texInfo[2];

  SimpleVertex() = default;
  SimpleVertex(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b,
               GLushort u, GLushort v);

  friend std::ostream &operator<<(std::ostream &os, const SimpleVertex &vertex);
};