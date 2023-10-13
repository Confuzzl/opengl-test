export module app.font;

export import app.texture_tile;

export struct Font {
  static const char *TEST_STRING;
  TexObject atlas;
  const unsigned short charWidth, charHeight;
  unsigned char columns = 0, rows = 0;

  Font(const char *source, unsigned short charWidth, unsigned short charHeight);

  void initAtlas();
  TexTile getTile(const char c);
};
