module;

#include "util/gl_utils.hpp"

export module wrapper.program.vertex_formats;

import <array>;

// export import :simple;
// export import :font;

export namespace VertexFormats {
template <std::size_t n> struct Vertex {
  static constexpr GLsizeiptr POS_WIDTH = n * sizeof(GLfloat);
  std::array<GLfloat, n> posInfo;
  Base3(GLfloat pos...) : posInfo{{pos...}} {}
};
namespace _2D {}
namespace _3D {}
struct Base3 {
  static constexpr GLsizeiptr POS_WIDTH = 3 * sizeof(GLfloat);

  std::array<GLfloat, 3> posInfo;

  Base3(GLfloat x, GLfloat y, GLfloat z);
};
struct Col : virtual public Base3 {
  static constexpr GLsizeiptr COL_WIDTH = 3 * sizeof(GLubyte);
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH;

  std::array<GLubyte, 3> colInfo;

  Col(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b);
};
struct Tex : virtual public Base3 {
  static const GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + TEX_WIDTH;

  std::array<GLushort, 2> texInfo;

  Tex(GLfloat x, GLfloat y, GLfloat z, GLushort u, GLushort v);
};
struct ColTex : public Col, public Tex {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH + TEX_WIDTH;

  ColTex(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b,
         GLushort u, GLushort v);
};

using Font = Tex;
} // namespace VertexFormats