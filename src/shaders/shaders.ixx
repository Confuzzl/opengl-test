module;

#include "util/gl_utils.hpp"
#include <fstream>

export module shaders;

import wrapper.gl_object;
import wrapper.vao;
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

template <typename... Attributes> struct ShaderProgram : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  void useProgram() {
    if (not allocated)
      throw UnallocatedGLObjectUsageException{
          std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", ID)};
    glUseProgram(ID);
  }

  void setVec3(const char *name, const Vec3 vec) const {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
  }
  void setMat4(const char *name, const Mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
                       glm::value_ptr(matrix));
  }

  void create() {
    ID = glCreateProgram();
    createShaders(vertexSource, fragmentSource);
    defineVAO();
  }

  VAO vao;

  constexpr ShaderProgram(const char *vertexSource, const char *fragmentSource,
                          Attributes &&...attributes)
      : vao{vertexAttributesWidth(attributes...)}, vertexSource{vertexSource},
        fragmentSource{fragmentSource},
        attributes{std::make_tuple(attributes...)} {}
  ~ShaderProgram() {
    glDeleteProgram(ID);
    std::cout << std::format("SHADER PROGRAM {} DELETED\n", ID);
  }

private:
  const char *vertexSource, *fragmentSource;

  std::tuple<Attributes...> attributes;
  template <typename T>
  void handleAttribute(const Shaders::VertexAttribute<T> &attr, GLuint &offset,
                       GLuint &index) {
    glEnableVertexArrayAttrib(vao.ID, index);
    glVertexArrayAttribFormat(vao.ID, index, attr.n, macroOf<T>(),
                              attr.normalize, offset);
    glVertexArrayAttribBinding(vao.ID, index, 0);
    offset += attr.n * sizeof(T);
    index++;
  }
  void defineVAO() {
    GLuint offset = 0, index = 0;
    std::apply(
        [this, &offset, &index](auto &&...args) {
          ((this->handleAttribute(args, offset, index)), ...);
        },
        attributes);
  }

  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source) {
    std::cout << std::format("ATTEMPING TO COMPILE {}\n", source);
    GLint success = 0;
    ID = glCreateShader(type);

    std::string temp = sourceToString(source);
    const char *chars = temp.c_str();
    glShaderSource(ID, 1, &chars, NULL);

    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

    if (not success) {
      // std::string errorLog = "";
      // GLchar err[512]{};

      // GLint logSize = 0;
      // glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
      // errorLog.resize(logSize);
      // glGetShaderInfoLog(ID, logSize, NULL, errorLog.data());
      throw FailedShaderCompilationException{
          std::format("{} FAILED TO COMPILE\n", source)};
    }
  }
  void createShaders(const std::string &vertex, const std::string &fragment) {
    GLuint vertexID = 0, fragmentID = 0;
    try {
      createShader(GL_VERTEX_SHADER, vertexID,
                   std::format("assets/shader/{}.vert", vertex));
      createShader(GL_FRAGMENT_SHADER, fragmentID,
                   std::format("assets/shader/{}.frag", fragment));
    } catch (const FailedShaderCompilationException &e) {
      mainApp.catchException(e);
    }
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    markAsAllocated();
  }
};
} // namespace Shaders