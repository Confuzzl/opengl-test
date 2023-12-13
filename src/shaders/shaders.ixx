module;

#include "util/gl_utils.hpp"

export module shaders;

import wrapper.gl_object;
import wrapper.vao;
import util.glm;
import <stdexcept>;
import <typeindex>;

export namespace Shaders {
struct VertexAttribute {
  unsigned char n;
  std::type_index type;
};

constinit VertexAttribute a{1, typeid(int)};

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

  constexpr ShaderProgram(
      const char *vertexSource, const char *fragmentSource,
      const std::initializer_list<VertexAttribute> &attributes)
      : vao{vertexAttributesWidth(vertexAttributes)},
        vertexSource{vertexSource}, fragmentSource{fragmentSource},
        vertexAttributes(attributes) {}
  ~ShaderProgram();

private:
  static std::string errorLog;

  const char *vertexSource, *fragmentSource;
  std::initializer_list<VertexAttribute> vertexAttributes;

  static constexpr GLsizei vertexAttributesWidth(
      const std::initializer_list<VertexAttribute> &attributes) {
    GLsizei width = 0;
    for (const auto &attribute : attributes)
      width += attribute.n * sizeof(attribute.type);
    return width;
  }

  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source);
  void createShaders(const std::string &vertex, const std::string &fragment);
};
} // namespace Shaders