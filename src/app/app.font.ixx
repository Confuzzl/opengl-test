export module app.font;

import app.texture_tile;
import wrapper.tex_object;

export struct Font {
  static const char *TEST_STRING;
  TexObject atlas;
  const unsigned short charWidth, charHeight;
  unsigned char columns = 0, rows = 0;

  Font(const char *source, unsigned short charWidth, unsigned short charHeight);

  void initAtlas();
  TexTile getTile(const char c);
};
