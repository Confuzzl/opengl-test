module;

#include "util/gl_utils.hpp"

export module wrapper.gl_object;

import <stdexcept>;

export struct GLObject {
  struct UnallocatedGLObjectUsageException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  GLuint ID;
  bool allocated = false;
  void markAsAllocated();
};