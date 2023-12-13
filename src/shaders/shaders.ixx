module;

#include "util/gl_utils.hpp"

export module shaders.shaders;

import wrapper.gl_object;
import wrapper.vao;
import util.glm;
import <stdexcept>;
import <typeindex>;

export namespace Shaders {
struct VertexAttribute {
  unsigned char n;
  std::type_index type;

  VertexAttribute(const unsigned char n, std::type_index &&type)
      : n{n}, type{type} {}
};

struct ShaderProgram : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  VAO vao;

  void useProgram();

  void setVec3(const char *name, const Vec3 vec) const;
  void setMat4(const char *name, const Mat4 matrix) const;

  void defineVAO();
  void create();

  ShaderProgram(const std::string &vertexSource,
                const std::string &fragmentSource,
                const std::initializer_list<VertexAttribute> &attributes);
  ~ShaderProgram();

private:
  static std::string errorLog;

  std::string vertexSource;
  std::string fragmentSource;
  std::initializer_list<VertexAttribute> vertexAttributes;

  static GLsizei vertexAttributesWidth(
      const std::initializer_list<VertexAttribute> &vertexAttributes);

  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source);
  void createShaders(const std::string &vertex, const std::string &fragment);
};
} // namespace Shaders