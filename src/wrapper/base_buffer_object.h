#pragma once
#include "gl_object.h"
template <typename T> struct BufferObject : public GLObject {
  GLsizeiptr size = 0;
  ~BufferObject();
  void allocateBufferObject(const GLsizeiptr size);
};