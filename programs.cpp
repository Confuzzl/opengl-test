module;

#include "util/gl_utils.hpp"
#include <fstream>

module wrapper.program.programs;

import util.debug;

Programs::Base::Base(const GLsizei stride, const std::string &vertexSource,
                     const std::string &fragmentSource)
    : vao{stride}, vertexSource{vertexSource}, fragmentSource{fragmentSource} {}
Programs::Base::~Base() {
  glDeleteProgram(ID);
  std::cout << "shader program deleted\n";
}

void Programs::Base::useProgram() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", ID)};
  glUseProgram(ID);
}

void Programs::Base::setVec3(const char *name, const Vec3 vec) {
  glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}
void Programs::Base::setMat4(const char *name, const Mat4 matrix) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

void Programs::Base::create() {
  createShaders(vertexSource, fragmentSource);
  defineVAO();
}

static std::string sourceToString(const std::string &name) {
  std::ifstream in{name};
  return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}
void Programs::Base::createShader(const GLenum type, GLuint &ID,
                                  const std::string &source) {
  GLint success = 0;
  ID = glCreateShader(type);
  const std::string raw{sourceToString(source)};
  const char *chars = raw.c_str();
  glShaderSource(ID, 1, &chars, NULL);
  glCompileShader(ID);
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
  if (not success) {
    GLint logLength = 0;
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLength);
    glGetShaderInfoLog(ID, logLength, NULL, log);
    throw FailedShaderCompilationException{
        std::format("{} FAILED TO COMPILE\n{}\n", source, log)};
  }
}
void Programs::Base::createShaders(const std::string &vertex,
                                   const std::string &fragment) {}