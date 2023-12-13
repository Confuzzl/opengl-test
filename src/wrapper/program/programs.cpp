module;

#include "util/gl_utils.hpp"
#include <fstream>

module wrapper.program.programs;

import wrapper.program.vertex_formats;
import app.app;
import util.debug;

std::string Programs::Base::errorLog{"NONE"};

// constexpr Programs::Base::Base(const GLsizei stride,
//                                const std::string &vertexSource,
//                                const std::string &fragmentSource)
//     : vao{stride}, vertexSource{vertexSource}, fragmentSource{fragmentSource}
//     {}

Programs::Base::~Base() {
  glDeleteProgram(ID);
  std::cout << std::format("SHADER PROGRAM {} DELETED\n", ID);
}

void Programs::Base::useProgram() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", ID)};
  glUseProgram(ID);
}

void Programs::Base::setVec3(const char *name, const Vec3 vec) const {
  glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}
void Programs::Base::setMat4(const char *name, const Mat4 matrix) const {
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
void Programs::Base::createShaders(const std::string &vertex,
                                   const std::string &fragment) {
  GLuint vertexID = 0, fragmentID = 0;
  try {
    createShader(GL_VERTEX_SHADER, vertexID,
                 std::format("assets/shader/{}.vert", vertex));
    createShader(GL_FRAGMENT_SHADER, fragmentID,
                 std::format("assets/shader/{}.frag", fragment));
  } catch (const FailedShaderCompilationException &e) {
    mainApp.catchException(e);
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertexID);
  glAttachShader(ID, fragmentID);
  glLinkProgram(ID);
  glDeleteShader(vertexID);
  glDeleteShader(fragmentID);

  markAsAllocated();
}

void Programs::Base::createShader(const GLenum type, GLuint &ID,
                                  const std::string &source) {
  std::cout << std::format("ATTEMPING TO COMPILE {}\n", source);
  GLint success = 0;
  ID = glCreateShader(type);
  std::string temp = sourceToString(source);
  const char *chars = temp.c_str();
  glShaderSource(ID, 1, &chars, NULL);
  glCompileShader(ID);
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
  if (not success) {
    GLint logSize = 0;
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
    errorLog.resize(logSize);
    glGetShaderInfoLog(ID, 512, NULL, errorLog.data());
    throw FailedShaderCompilationException{
        std::format("{} FAILED TO COMPILE\n{}\n", source, errorLog)};
  }
}

// constexpr Programs::Col::Col()
//     : Base(VertexFormats::_3D::Colored::WIDTH, "col", "col") {}
void Programs::Col::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0, index = 0;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 3, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  offset += 3 * sizeof(GLfloat);
  index++;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 3, GL_UNSIGNED_BYTE, GL_TRUE,
                            offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  std::cout << std::format("COL SHADER VAO {} DEFINED\n", vao.ID);
  vao.markAsAllocated();
}

// constexpr Programs::Tex::Tex()
//     : Base(VertexFormats::_3D::Textured::WIDTH, "tex", "tex") {}
void Programs::Tex::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0, index = 0;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 3, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  offset += 3 * sizeof(GLubyte);
  index++;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 2, GL_UNSIGNED_SHORT, GL_FALSE,
                            offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  std::cout << std::format("TEX SHADER VAO {} DEFINED\n", vao.ID);
  vao.markAsAllocated();
}

// constexpr Programs::ColTex::ColTex()
//     : Base(VertexFormats::_3D::ColTex::WIDTH, "coltex", "coltex") {}
void Programs::ColTex::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0, index = 0;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 3, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  offset += 3 * sizeof(GLfloat);
  index++;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 3, GL_UNSIGNED_BYTE, GL_TRUE,
                            offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  offset += 3 * sizeof(GLubyte);
  index++;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 2, GL_UNSIGNED_SHORT, GL_FALSE,
                            offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  std::cout << std::format("COLTEX SHADER VAO {} DEFINED\n", vao.ID);
  vao.markAsAllocated();
}

// constexpr Programs::Font::Font()
//     : Base(VertexFormats::_2D::Font::WIDTH, "font", "font") {}
void Programs::Font::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0, index = 0;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 2, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  offset += 2 * sizeof(GLfloat);
  index++;

  glEnableVertexArrayAttrib(vao.ID, index);
  glVertexArrayAttribFormat(vao.ID, index, 2, GL_UNSIGNED_SHORT, GL_FALSE,
                            offset);
  glVertexArrayAttribBinding(vao.ID, index, 0);

  std::cout << std::format("FONT SHADER VAO {} DEFINED\n", vao.ID);
  vao.markAsAllocated();
}