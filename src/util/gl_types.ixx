module;

#include "util/gl_utils.hpp"

export module util.gl_types;

import <map>;
import <typeinfo>;
import <typeindex>;

export enum GLPrimitive : unsigned int {
  POINTS = GL_POINTS,
  LINE_STRIP = GL_LINE_STRIP,
  LINE_LOOP = GL_LINE_LOOP,
  LINES = GL_LINES,
  LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
  LINES_ADJACENCY = GL_LINES_ADJACENCY,
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  TRIANGLE_FAN = GL_TRIANGLE_FAN,
  TRIANGLES = GL_TRIANGLES,
  TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
  TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
  PATCHES = GL_PATCHES,
};

export enum GLNumeric : unsigned int {
  BYTE = GL_BYTE,
  UBYTE = GL_UNSIGNED_BYTE,
  SHORT = GL_SHORT,
  USHORT = GL_UNSIGNED_SHORT,
  INT = GL_INT,
  UINT = GL_UNSIGNED_INT,
  FLOAT = GL_FLOAT,
};

const std::map<std::type_index, GLNumeric> typeToMacro() {
  static std::map<std::type_index, GLNumeric> map{
      {typeid(GLbyte), GLNumeric::BYTE},
      {typeid(GLubyte), GLNumeric::UBYTE},
      {typeid(GLshort), GLNumeric::SHORT},
      {typeid(GLushort), GLNumeric::USHORT},
      {typeid(GLint), GLNumeric::INT},
      {typeid(GLuint), GLNumeric::UINT},
      {typeid(GLfloat), GLNumeric::FLOAT},
  };
  return map;
};

export template <typename T> unsigned int macroOf() {
  return typeToMacro().at(typeid(T));
}
