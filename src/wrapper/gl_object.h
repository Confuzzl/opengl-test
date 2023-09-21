#pragma once
#include "util/gl_utils.h"

struct GLObject {
  GLuint ID;
  bool allocated = false;
  void markAsAllocated();
};
