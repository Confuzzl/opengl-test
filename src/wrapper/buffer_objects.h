#pragma once
#include "base_buffer_object.h"
struct VBO : public BufferObject<GLfloat> {};
struct EBO : public BufferObject<GLuint> {};