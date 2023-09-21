#pragma once
#include "buffer_objects.h"
#include "gl_object.h"
struct VAO : public GLObject {
  VBO boundedVBO;
  EBO boundedEBO;
  GLsizei stride;

  VAO(const GLsizei stride);
  ~VAO();

  void bindVBO(const VBO& vbo);
  void bindEBO(const EBO& ebo);

  void bindVertexArray();
};