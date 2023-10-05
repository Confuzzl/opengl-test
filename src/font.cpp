#include "font.h"
#include "util/debug_utils.h"

const char *Font::TEST_STRING = " !\"#$%&'()*+,-./"
                                "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ["
                                "\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

Font::Font(const char *source, unsigned short charWidth,
           unsigned short charHeight)
    : atlas{source}, charWidth{charWidth}, charHeight{charHeight} {};

void Font::initAtlas() {
  atlas.initTexture();
  columns = atlas.width / charWidth;
  rows = atlas.height / charHeight;
}
TexTile Font::getTile(const char c) {
  vec4 info{atlas.width - charWidth, atlas.height - charHeight, charWidth,
            charHeight};
  // error char
  if (!(c < 32 || c >= 127)) {
    const char id = c - 32;
    unsigned char row = id / columns, column = id % columns;
    info = {column * charWidth, row * charHeight, charWidth, charHeight};
  }
  info[1] = atlas.height - info[1] - info[3]; // flip y values
  info /= vec4{atlas.width, atlas.height, atlas.width, atlas.height};
  info *= vec4{TexTile::TEXEL_RANGE};

  return {info};
}