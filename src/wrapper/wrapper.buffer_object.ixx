module;

#include "util/gl_utils.h"

export module wrapper.buffer_object;

import wrapper.gl_object;

export template <typename T> struct BufferObject : public GLObject {
  GLsizeiptr size = 0;
  ~BufferObject();
  void allocateBufferObject(const GLsizeiptr size);
};

export using VBO = BufferObject<GLfloat>;
export using EBO = BufferObject<GLuint>;