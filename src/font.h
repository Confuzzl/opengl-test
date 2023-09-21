#pragma once
#include "texture_tile.h"
#include "wrapper/tex_object.h"
struct Font {
  static const char *TEST_STRING;
  TexObject atlas;
  const unsigned short charWidth, charHeight;
  unsigned char columns = 0, rows = 0;

  Font(const char *source, unsigned short charWidth, unsigned short charHeight);

  void initAtlas();
  TexTile getTile(const char c);
};