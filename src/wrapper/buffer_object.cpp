module;

#include "util/gl_utils.hpp"

module wrapper.buffer_object;

template <typename T> BufferObject<T>::~BufferObject() {
  glDeleteBuffers(1, &ID);
  // std::cout << std::format("buffer object {} deleted\n", ID);
}
template <typename T>
void BufferObject<T>::allocateBufferObject(const GLsizeiptr size) {
  this->size = size;
  glCreateBuffers(1, &ID);
  glNamedBufferStorage(
      ID, size, NULL,
      GL_DYNAMIC_STORAGE_BIT); // factories possibly initialized before?
  // std::cout << std::format("buffer object {} allocated\n", ID);
  markAsAllocated();
}

template struct BufferObject<GLfloat>;
template struct BufferObject<GLuint>;