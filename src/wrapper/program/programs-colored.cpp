module;

#include "util/gl_utils.hpp"

module wrapper.program.programs:colored;

import wrapper.program.vertex_formats;
import util.debug;

ColoredProgram::ColoredProgram()
    : BaseProgram(VertexFormats::_3D::ColTex::WIDTH, "coltex", "coltex") {}

void ColoredProgram::defineVAO() {
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