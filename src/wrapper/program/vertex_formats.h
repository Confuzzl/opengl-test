#pragma once
#include "util/gl_utils.h"
#include "util/glm_utils.h"
struct DefaultVertex {
  static const GLsizeiptr POS_WIDTH = 3 * sizeof(GLfloat);
  static const GLsizeiptr COL_WIDTH = 3 * sizeof(GLubyte);
  static const GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);
  static const GLsizeiptr WIDTH = POS_WIDTH + COL_WIDTH + TEX_WIDTH;

  GLfloat posInfo[3];
  GLubyte colInfo[3];
  GLushort texInfo[2];
};
struct FontVertex {
  static const GLsizeiptr POS_WIDTH = 2 * sizeof(GLfloat);
  static const GLsizeiptr TEX_WIDTH = 2 * sizeof(GLushort);
  static const GLsizeiptr WIDTH = POS_WIDTH + TEX_WIDTH;

  GLfloat posInfo[2];
  GLushort texInfo[2];
};