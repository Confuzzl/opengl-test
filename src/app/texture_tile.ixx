export module app.texture_tile;

import app.app;

import util.glm;
import util.vector;
import <map>;
import <string>;

export struct TexObject;

export struct TexTile {
  using IntUV = glm::lowp_u16vec2;

  static const unsigned short TEXEL_RANGE = SHRT_MAX;
  static const std::map<std::string, glm::lowp_u16vec4> textureDict;
  static const Vector<std::string> textureKeys;

  const IntUV coordinates;
  const IntUV dimensions;

  static TexTile getTile(const std::string &name,
                         const TexObject &texObject = *mainApp.atlas);
  static const std::string &getRandomTexture();
  static TexTile getRandomTile(const TexObject &texObject = *mainApp.atlas);

  TexTile(const glm::lowp_u16vec4 info);

  IntUV globalIntUV(const Vec2 &uv) const;
};