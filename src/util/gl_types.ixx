module;

#include "util/gl_utils.hpp"

export module util.gl_types;

import <map>;
import <typeinfo>;
import <typeindex>;

export const std::map<std::type_index, unsigned int> typeToMacro{
    {typeid(GLbyte), GL_BYTE},   {typeid(GLubyte), GL_UNSIGNED_BYTE},
    {typeid(GLshort), GL_SHORT}, {typeid(GLushort), GL_UNSIGNED_SHORT},
    {typeid(GLint), GL_INT},     {typeid(GLuint), GL_UNSIGNED_INT},
    {typeid(GLfloat), GL_FLOAT},
};

export template <typename T> unsigned int macroOf() {
  return typeToMacro.at(typeid(T));
}
