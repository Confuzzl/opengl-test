module;

#include "util/gl_utils.hpp"

export module wrapper.program.base_program;

import util.glm;
import wrapper.gl_object;
import wrapper.vao;

export class BaseProgram : public GLObject {
public:
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  GLchar infoLog[512]{};
  VAO vao;
  std::string vertexSource, fragmentSource;

  ~BaseProgram();

  void useProgram();
  void deleteProgram();

  void setVec3(const char *name, const Vec3 vec);
  void setMat4(const char *name, const Mat4 matrix);

  virtual void defineVAO() = 0;
  void create();

protected:
  BaseProgram(const GLsizei stride, const std::string vertexSource,
              const std::string fragmentSource);

  void createShaders(const std::string vertex, const std::string fragment);

private:
  static void createShader(const GLenum type, GLuint &ID,
                           const std::string source, GLchar (&log)[512]);
};