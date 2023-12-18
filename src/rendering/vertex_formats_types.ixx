module;

#include "util/gl_utils.hpp"

export module rendering.vertex_formats.types;

import rendering.vertex_formats;
import <array>;

template <typename T, std::size_t n>
void writeData(GLintptr &offset, const GLuint vboID,
               const std::array<T, n> &info) {
  const auto size = n * sizeof(T);
  glNamedBufferSubData(vboID, offset, size, info.data());
  offset += size;
}

export namespace VertexFormats {
namespace _2D {
struct Font : public Vertex<2>, public Texturable {
  static constexpr GLsizeiptr WIDTH = Vertex::POS_WIDTH + Texturable::TEX_WIDTH;

  Font(GLfloat x, GLfloat y, GLushort u, GLushort v)
      : Vertex(x, y), Texturable(u, v) {}

  void writeVertexTo(GLintptr &offset, const GLuint vboID) const override {
    writeData(offset, vboID, posInfo);
    writeData(offset, vboID, texInfo);
  }
};
} // namespace _2D
} // namespace VertexFormats

export namespace VertexFormats {
namespace _3D {
struct Col : public Vertex<3>, public Colorable {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH;

  Col(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b)
      : Vertex(x, y, z), Colorable(r, g, b) {}

  void writeVertexTo(GLintptr &offset, const GLuint vboID) const override {
    writeData(offset, vboID, posInfo);
    writeData(offset, vboID, colInfo);
  }
};

struct Tex : public Vertex<3>, public Texturable {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + TEX_WIDTH;

  Tex(GLfloat x, GLfloat y, GLfloat z, GLushort u, GLushort v)
      : Vertex(x, y, z), Texturable(u, v) {}

  void writeVertexTo(GLintptr &offset, const GLuint vboID) const override {
    writeData(offset, vboID, posInfo);
    writeData(offset, vboID, texInfo);
  }
};
struct ColTex : public Vertex<3>, public Colorable, public Texturable {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH + TEX_WIDTH;

  ColTex(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b,
         GLushort u, GLushort v)
      : Vertex(x, y, z), Colorable(r, g, b), Texturable(u, v) {}

  void writeVertexTo(GLintptr &offset, const GLuint vboID) const override {
    writeData(offset, vboID, posInfo);
    writeData(offset, vboID, colInfo);
    writeData(offset, vboID, texInfo);
  }
};
} // namespace _3D
} // namespace VertexFormats
