module;

#include "util/gl_utils.hpp"
#include <fstream>

export module rendering.shaders;

import wrapper.gl_object;
import wrapper.vao;

// import rendering.vertex_formats.types;

import app.app;

import util.glm;
import util.debug;
import util.gl_types;

import <typeinfo>;
import <stdexcept>;

std::string sourceToString(const std::string &name) {
  std::ifstream in{name};
  return std::string{std::istreambuf_iterator<char>(in),
                     std::istreambuf_iterator<char>()};
}

template <typename... Attributes>
constexpr GLsizei vertexAttributesWidth(Attributes &&...attributes) {
  GLsizei width = 0;
  ((width += attributes.width()), ...);
  return width;
}

export namespace Shaders {
template <typename T> struct VertexAttribute {
  const unsigned char n;
  const GLboolean normalize;
  constexpr unsigned char width() { return n * sizeof(T); }
};

struct Base : public GLObject {
  VAO vao;

  constexpr Base(const GLsizei stride) : vao{stride} {}

  void useProgram() const {
    if (not allocated)
      throw UnallocatedGLObjectUsageException{
          std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", GLid)};
    glUseProgram(GLid);
  }

  void setVec3(const char *name, const Vec3 &vec) const {
    glUniform3fv(glGetUniformLocation(GLid, name), 1, glm::value_ptr(vec));
  }
  void setMat4(const char *name, const Mat4 &matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(GLid, name), 1, GL_FALSE,
                       glm::value_ptr(matrix));
  }
};

template <typename VertexFormat, typename... Attributes>
struct Specialized : public Base {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  void create() {
    GLid = glCreateProgram();
    createShaders(vertexSource, fragmentSource);
    defineVAO();
  }

  constexpr Specialized(const char *vertexSource, const char *fragmentSource,
                        Attributes &&...attributes)
      : Base(vertexAttributesWidth(attributes...)), vertexSource{vertexSource},
        fragmentSource{fragmentSource},
        attributes{std::make_tuple(attributes...)} {}
  ~Specialized() {
    glDeleteProgram(GLid);
    std::cout << std::format("SHADER PROGRAM {} DELETED\n", GLid);
  }

private:
  const char *vertexSource, *fragmentSource;

  const std::tuple<Attributes...> attributes;
  template <typename T>
  void handleAttribute(const Shaders::VertexAttribute<T> &attr, GLuint &offset,
                       GLuint &index) const {
    glEnableVertexArrayAttrib(vao.GLid, index);
    glVertexArrayAttribFormat(vao.GLid, index, attr.n, macroOf<T>(),
                              attr.normalize, offset);
    glVertexArrayAttribBinding(vao.GLid, index, 0);
    offset += attr.n * sizeof(T);
    index++;
  }
  void defineVAO() const {
    GLuint offset = 0, index = 0;
    std::apply(
        [this, &offset, &index](auto &&...args) {
          ((this->handleAttribute(args, offset, index)), ...);
        },
        attributes);
  }

  void compileShader(const GLenum type, GLuint &ID,
                     const std::string &source) const {
    std::cout << std::format("ATTEMPING TO COMPILE {}\n", source);
    GLint success = 0;
    ID = glCreateShader(type);

    std::string temp = sourceToString(source);
    const char *chars = temp.c_str();
    glShaderSource(ID, 1, &chars, NULL);

    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

    if (not success) {
      throw FailedShaderCompilationException{
          std::format("{} FAILED TO COMPILE\n", source)};
    }
  }
  void createShaders(const std::string &vertex, const std::string &fragment) {
    GLuint vertexID = 0, fragmentID = 0;
    try {
      compileShader(GL_VERTEX_SHADER, vertexID,
                    std::format("assets/shader/{}.vert", vertex));
      compileShader(GL_FRAGMENT_SHADER, fragmentID,
                    std::format("assets/shader/{}.frag", fragment));
    } catch (const FailedShaderCompilationException &e) {
      mainApp.catchException(e);
    }
    glAttachShader(GLid, vertexID);
    glAttachShader(GLid, fragmentID);
    glLinkProgram(GLid);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    markAsAllocated();
  }
};
} // namespace Shaders