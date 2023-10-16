module;

#include "util/gl_utils.hpp"

module wrapper.program.programs:font;

import wrapper.program.vertex_formats;
import util.debug;

FontProgram::FontProgram() : BaseProgram(FontVertex::WIDTH, "font", "font") {}

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