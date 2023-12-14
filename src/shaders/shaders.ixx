module;

#include "util/gl_utils.hpp"
#include <fstream>

export module shaders;

import wrapper.gl_object;
import wrapper.vao;
import app.app;
import util.glm;
import util.debug;
import <stdexcept>;
import <typeindex>;

export namespace Shaders {
template <typename T> struct VertexAttribute {
  const unsigned char n;
  T typevar = 0;
};

struct ShaderProgram : public GLObject {
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

  template <typename... Attributes>
  constexpr ShaderProgram(const char *vertexSource, const char *fragmentSource,
                          Attributes &&...attributes)
      : vao{vertexAttributesWidth(attributes...)}, vertexSource{vertexSource},
        fragmentSource{fragmentSource} {}
  ~ShaderProgram() {
    glDeleteProgram(ID);
    std::cout << "shader program deleted\n";
  }

private:
  static std::string errorLog;

  const char *vertexSource, *fragmentSource;

  template <typename... Attributes>
  static constexpr GLsizei vertexAttributesWidth(Attributes &&...attributes) {
    GLsizei width = 0;
    ((width += attributes.n * sizeof(attributes.typevar)), ...);
    return width;
  }

  void defineVAO() {}

  static std::string sourceToString(const std::string &name) {
    std::ifstream in{name};
    return {std::istreambuf_iterator<char>(in),
            std::istreambuf_iterator<char>()};
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
      GLint logSize = 0;
      glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
      errorLog.resize(logSize);
      glGetShaderInfoLog(ID, 512, NULL, errorLog.data());
      throw FailedShaderCompilationException{
          std::format("{} FAILED TO COMPILE\n{}\n", source, errorLog)};
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