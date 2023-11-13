module;

#include "util/gl_utils.hpp"
#include <fstream>

module wrapper.program.base_program;

import util.debug;
import app.app;

static std::string sourceToString(const std::string &name) {
  std::ifstream in{name};
  return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}

BaseProgram::BaseProgram(const GLsizei stride, const std::string &vertexSource,
                         const std::string fragmentSource)
    : vao{stride}, vertexSource{vertexSource}, fragmentSource{fragmentSource} {}

BaseProgram::~BaseProgram() { deleteProgram(); }

void BaseProgram::useProgram() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", ID)};
  glUseProgram(ID);
}
void BaseProgram::deleteProgram() {
  glDeleteProgram(ID);
  std::cout << "shader program deleted\n";
}
void BaseProgram::setVec3(const char *name, const Vec3 vec) {
  glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}
void BaseProgram::setMat4(const char *name, const glm::mat4 matrix) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

void BaseProgram::create() {
  createShaders(vertexSource, fragmentSource);
  defineVAO();
}

void BaseProgram::createShaders(const std::string &vertex,
                                const std::string &fragment) {
  GLuint vertexID = 0, fragmentID = 0;
  try {
    createShader(GL_VERTEX_SHADER, vertexID,
                 std::format("assets/shader/{}.vert", vertex), infoLog);
    createShader(GL_FRAGMENT_SHADER, fragmentID,
                 std::format("assets/shader/{}.frag", fragment), infoLog);
  } catch (const FailedShaderCompilationException &e) {
    app.catchException(e);
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertexID);
  glAttachShader(ID, fragmentID);
  glLinkProgram(ID);
  glDeleteShader(vertexID);
  glDeleteShader(fragmentID);

  markAsAllocated();
}

void BaseProgram::createShader(const GLenum type, GLuint &ID,
                               const std::string &source, GLchar (&log)[512]) {
  GLint success = 0;
  ID = glCreateShader(type);
  std::string temp = sourceToString(source);
  const char *chars = temp.c_str();
  glShaderSource(ID, 1, &chars, NULL);
  glCompileShader(ID);
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
  if (not success) {
    glGetShaderInfoLog(ID, 512, NULL, log);
    throw FailedShaderCompilationException{
        std::format("{} FAILED TO COMPILE\n{}\n", source, log)};
  }
}