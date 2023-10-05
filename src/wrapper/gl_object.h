#pragma once
#include "util/gl_utils.h"
#include <stdexcept>

struct GLObject {
  struct UnallocatedGLObjectUsageException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  GLuint ID;
  bool allocated = false;
  void markAsAllocated();
};
