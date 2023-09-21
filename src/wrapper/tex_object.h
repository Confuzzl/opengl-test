#pragma once
#include "gl_object.h"
#include <stb_image.h>

struct TexObject : public GLObject {
  const std::string name;
  int width = 0, height = 0, channels = 0;

  TexObject(const std::string name);
  ~TexObject();

  void initTexture();

  void bindTextureUnit();
};
