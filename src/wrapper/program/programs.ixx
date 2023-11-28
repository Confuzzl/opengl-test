module;

#include "util/gl_utils.hpp"

export module wrapper.program.programs;

import wrapper.gl_object;
import wrapper.vao;
import util.glm;
import <stdexcept>;

export namespace Programs {
struct Base : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static std::string errorLog;
  VAO vao;
  const std::string vertexSource, fragmentSource;

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

struct Col : public Base {
  Col();
  void defineVAO() override;
};
struct Tex : public Base {
  Tex();
  void defineVAO() override;
};
struct ColTex : public Base {
  ColTex();
  void defineVAO() override;
};
struct Font : public Base {
  static constexpr int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;

  Font();
  void defineVAO() override;
};
} // namespace Programs