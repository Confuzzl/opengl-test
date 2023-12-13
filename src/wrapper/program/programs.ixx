module;

#include "util/gl_utils.hpp"

export module wrapper.program.programs;

import wrapper.gl_object;
import wrapper.vao;
import wrapper.program.vertex_formats;
import util.glm;
import <stdexcept>;

export namespace Programs {
struct Base : public GLObject {
  struct FailedShaderCompilationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  static std::string errorLog;
  VAO vao;
  // std::string vertexSource, fragmentSource;
  const char *vertexSource, *fragmentSource;

  void useProgram();

  void setVec3(const char *name, const Vec3 vec) const;
  void setMat4(const char *name, const Mat4 matrix) const;

  virtual void defineVAO() = 0;
  void create();

  constexpr Base(const GLsizei stride, const char *vertexSource,
                 const char *fragmentSource)
      : vao{stride}, vertexSource{vertexSource},
        fragmentSource{fragmentSource} {}
  ~Base();

private:
  static void createShader(const GLenum type, GLuint &ID,
                           const std::string &source);
  void createShaders(const std::string &vertex, const std::string &fragment);
};

struct Col : public Base {
  constexpr Col() : Base(VertexFormats::_3D::Colored::WIDTH, "col", "col") {}
  void defineVAO() override;
};
struct Tex : public Base {
  constexpr Tex() : Base(VertexFormats::_3D::Textured::WIDTH, "tex", "tex") {}
  void defineVAO() override;
};
struct ColTex : public Base {
  constexpr ColTex()
      : Base(VertexFormats::_3D::ColTex::WIDTH, "coltex", "coltex") {}
  void defineVAO() override;
};
struct Font : public Base {
  static constexpr int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;

  constexpr Font() : Base(VertexFormats::_2D::Font::WIDTH, "font", "font") {}
  void defineVAO() override;
};
} // namespace Programs