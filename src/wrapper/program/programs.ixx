module;

#include "util/gl_utils.hpp"

export module wrapper.program.programs;

export import :colored;
export import :font;

import wrapper.gl_object;
import wrapper.vao;
import util.glm;
import <stdexcept>;

export namespace Programs {
struct Base : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  // GLchar infoLog[512]{};
  static std::string errorLog;
  VAO vao;
  std::string vertexSource, fragmentSource;

  ~Base();

  void useProgram();

  void setVec3(const char *name, const Vec3 vec);
  void setMat4(const char *name, const Mat4 matrix);

  virtual void defineVAO() = 0;
  void create();

protected:
  Base(const GLsizei stride, const std::string &vertexSource,
       const std::string &fragmentSource);

private:
  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source);
  void createShaders(const std::string &vertex, const std::string &fragment);
};
} // namespace Programs