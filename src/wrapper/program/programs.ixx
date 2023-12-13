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
  std::string vertexSource, fragmentSource;

  void useProgram();

  void setVec3(const char *name, const Vec3 vec) const;
  void setMat4(const char *name, const Mat4 matrix) const;

  virtual void defineVAO() = 0;
  void create();

  Base(const GLsizei stride, const std::string &vertexSource,
       const std::string &fragmentSource);
  ~Base();
  // Base(const Base &) = default;
  // Base(Base &&) = default;
  // Base &operator=(const Base &) = default;
  // Base &operator=(Base &&) = default;

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