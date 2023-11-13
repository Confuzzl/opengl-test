module;

#include "util/gl_utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

module wrapper.tex_object;

import util.debug;

TexObject::TexObject(const std::string &name) : name{name} {}
TexObject::~TexObject() {
  glDeleteTextures(1, &ID);
  // std::cout << std::format("tex {} \"{}\" deleted\n", ID, name);
}

void TexObject::initTexture() {
  std::string path = "assets/" + name + ".png";
  glCreateTextures(GL_TEXTURE_2D, 1, &ID);
  glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
  if (not data) {
    stbi_image_free(data);
    throw FailedTextureLoadException{
        std::format("TEXTURE {} FAILED TO LOAD\n", name)};
  }
  glTextureStorage2D(ID, 1, GL_RGBA8, width, height);
  glTextureSubImage2D(ID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
                      data);
  glGenerateTextureMipmap(ID);
  stbi_image_free(data);

  markAsAllocated();
}

void TexObject::bindTextureUnit() {
  if (not allocated)
    throw UnallocatedGLObjectUsageException{
        "TEXTURE WAS BOUND BEFORE INITIALIZATION\n"};
  glBindTextureUnit(0, ID);
}
