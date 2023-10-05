#pragma once
#include "gl_object.h"
#include <stb_image.h>

struct TexObject : public GLObject {
  struct FailedTextureLoadException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  const std::string name;
  int width = 0, height = 0, channels = 0;

  TexObject(const std::string name);
  ~TexObject();

  void initTexture();

  void bindTextureUnit();
};
