export module wrapper.gl_object;

import "util/gl_utils.h";
import <stdexcept>;

export struct GLObject {
  struct UnallocatedGLObjectUsageException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  GLuint ID;
  bool allocated = false;
  void markAsAllocated();
};