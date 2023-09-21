#include "programs.h"
#include "util/debug_utils.h"
#include "vertex_formats.h"
DefaultProgram::DefaultProgram() : BaseProgram(DefaultVertex::WIDTH) {}

void DefaultProgram::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0;
  glEnableVertexArrayAttrib(vao.ID, 0);
  glVertexArrayAttribFormat(vao.ID, 0, 3, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, 0, 0);

  offset += 3 * sizeof(GLfloat);
  glEnableVertexArrayAttrib(vao.ID, 1);
  glVertexArrayAttribFormat(vao.ID, 1, 3, GL_UNSIGNED_BYTE, GL_TRUE, offset);
  glVertexArrayAttribBinding(vao.ID, 1, 0);

  offset += 3 * sizeof(GLubyte);
  glEnableVertexArrayAttrib(vao.ID, 2);
  glVertexArrayAttribFormat(vao.ID, 2, 2, GL_UNSIGNED_SHORT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, 2, 0);

  std::cout << std::format("default shader vao {} defined\n", vao.ID);
  vao.markAsAllocated();
}
void DefaultProgram::create() {
  BaseProgram::create("default", "default");
  defineVAO();
}

FontProgram::FontProgram() : BaseProgram(FontVertex::WIDTH) {}

void FontProgram::defineVAO() {
  glCreateVertexArrays(1, &vao.ID);

  GLuint offset = 0;
  glEnableVertexArrayAttrib(vao.ID, 0);
  glVertexArrayAttribFormat(vao.ID, 0, 2, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, 0, 0);

  offset += 2 * sizeof(GLfloat);
  glEnableVertexArrayAttrib(vao.ID, 1);
  glVertexArrayAttribFormat(vao.ID, 1, 2, GL_UNSIGNED_SHORT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao.ID, 1, 0);

  std::cout << std::format("font shader vao {} defined\n", vao.ID);
  vao.markAsAllocated();
}
void FontProgram::create() {
  BaseProgram::create("font", "font");
  defineVAO();
}