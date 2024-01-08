module;

#include "util/gl_utils.hpp"

module wrapper.buffer_object;

import util.debug;

template <typename T> BufferObject<T>::~BufferObject() {
  glDeleteBuffers(1, &GLid);
}
template <typename T>
void BufferObject<T>::allocateBufferObject(const GLsizeiptr size) {
  this->size = size;
  glCreateBuffers(1, &GLid);
  glNamedBufferStorage(GLid, size, NULL, GL_DYNAMIC_STORAGE_BIT);
  markAsAllocated();
}

template struct BufferObject<GLfloat>;
template struct BufferObject<GLuint>;