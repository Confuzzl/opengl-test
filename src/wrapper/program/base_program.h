#pragma once
#include "util/gl_utils.h"
#include "util/glm_utils.h"
#include "wrapper/gl_object.h";
#include "wrapper/vao.h"

class BaseProgram : public GLObject {
public:
  GLchar infoLog[512]{};
  VAO vao;
  std::string vertexSource, fragmentSource;

  ~BaseProgram();

  void useProgram();
  void deleteProgram();

  void setVec3(const char *name, const vec3 vec);
  void setMat4(const char *name, const mat4 matrix);

  virtual void defineVAO() = 0;
  virtual void create() = 0;

protected:
  BaseProgram(const GLsizei stride);

  void create(const std::string vertex, const std::string fragment);

private:
  static void createShader(const GLenum type, GLuint &ID,
                           const std::string source, GLchar (&log)[512]);
};