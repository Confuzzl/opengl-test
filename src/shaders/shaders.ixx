module;

#include "util/gl_utils.hpp"

export module shaders.shaders;

import wrapper.gl_object;
import wrapper.vao;
import util.glm;
import <stdexcept>;

export namespace Shaders {
struct ShaderProgram : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static std::string errorLog;
  VAO vao;
  const std::string vertexSource, fragmentSource;

  ~ShaderProgram();

  void useProgram();

  void setVec3(const char *name, const Vec3 vec) const;
  void setMat4(const char *name, const Mat4 matrix) const;

  void defineVAO();
  void create();

protected:
  ShaderProgram(const GLsizei stride, const std::string &vertexSource,
                const std::string &fragmentSource);

private:
  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source);
  void createShaders(const std::string &vertex, const std::string &fragment);
};
} // namespace Shaders
