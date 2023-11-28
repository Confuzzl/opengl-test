module;

#include "util/gl_utils.hpp"

export module wrapper.program.vertex_formats;

import <array>;
import <concepts>;

export namespace VertexFormats {
template <std::size_t n> struct Vertex {
  static constexpr GLsizeiptr POS_WIDTH = n * sizeof(GLfloat);

  std::array<GLfloat, n> posInfo;

  template <std::same_as<GLfloat>... Args>
  Vertex(Args... pos) : posInfo{{pos...}} {}
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

namespace _2D {
using Vertex = VertexFormats::Vertex<2>;
struct Font : public Vertex, public Texturable {
  static constexpr GLsizeiptr WIDTH = Vertex::POS_WIDTH + Texturable::TEX_WIDTH;

  Font(GLfloat x, GLfloat y, GLushort u, GLushort v)
      : Vertex(x, y), Texturable(u, v) {}
};
} // namespace _2D

namespace _3D {
using Vertex = VertexFormats::Vertex<3>;
struct Colored : virtual public Vertex, public Colorable {
  static constexpr GLsizeiptr WIDTH = Vertex::POS_WIDTH + Colorable::COL_WIDTH;

  Colored(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b)
      : Vertex(x, y, z), Colorable(r, g, b) {}
};

struct Textured : virtual public Vertex, public Texturable {
  static constexpr GLsizeiptr WIDTH = Vertex::POS_WIDTH + Texturable::TEX_WIDTH;

  Textured(GLfloat x, GLfloat y, GLfloat z, GLushort u, GLushort v)
      : Vertex(x, y, z), Texturable(u, v) {}
};
struct ColTex : public Vertex, public Colorable, public Texturable {
  static constexpr GLsizeiptr WIDTH =
      Vertex::POS_WIDTH + Colorable::COL_WIDTH + Texturable::TEX_WIDTH;

  ColTex(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b,
         GLushort u, GLushort v)
      : Vertex(x, y, z), Colorable(r, g, b), Texturable(u, v) {}
};
} // namespace _3D
} // namespace VertexFormats