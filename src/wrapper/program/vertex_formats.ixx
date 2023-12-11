module;

#include "util/gl_utils.hpp"

export module wrapper.program.vertex_formats;

import <array>;
import <concepts>;

template <typename T, std::size_t n>
void writeData(GLintptr &offset, const GLuint vboID,
               const std::array<T, n> &info) {
  const auto size = n * sizeof(T);
  glNamedBufferSubData(vboID, offset, size, info.data());
  offset += size;
}

export namespace VertexFormats {
template <std::size_t n> struct Vertex {
  static constexpr GLsizeiptr POS_WIDTH = n * sizeof(GLfloat);

  std::array<GLfloat, n> posInfo;

  template <std::same_as<GLfloat>... Args>
  Vertex(Args... pos) : posInfo{{pos...}} {}

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

namespace _3D {
struct Colored : virtual public Vertex<3>, public Colorable {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH;

  Colored(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g, GLubyte b)
      : Vertex(x, y, z), Colorable(r, g, b) {}

  void writeVertexTo(GLintptr &offset, const GLuint vboID) const override {
    writeData(offset, vboID, posInfo);
    writeData(offset, vboID, colInfo);
  }
};

struct Textured : virtual public Vertex<3>, public Texturable {
  static constexpr GLsizeiptr WIDTH = POS_WIDTH + TEX_WIDTH;

  Textured(GLfloat x, GLfloat y, GLfloat z, GLushort u, GLushort v)
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

template <typename T>
concept IsVertexFormat =
    requires(T t) { []<std::size_t n>(Vertex<n> &) {}(t); };
} // namespace VertexFormats