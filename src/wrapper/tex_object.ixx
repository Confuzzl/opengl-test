export module wrapper.tex_object;

import wrapper.gl_object;
import <stb_image.h>;

export struct TexObject : public GLObject {
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
