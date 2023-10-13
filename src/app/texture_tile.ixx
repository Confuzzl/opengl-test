export module app.texture_tile;

export import util.glm;
export import "wrapper/tex_object.h";
export import <map>;
export import <string>;

export struct TexTile {
  static const unsigned short TEXEL_RANGE = SHRT_MAX;
  static const std::map<std::string, glm::lowp_u16vec4> textureDict;

  glm::lowp_u16vec2 coordinates;
  glm::lowp_u16vec2 dimensions;

  static TexTile getTile(const std::string name, const TexObject &texObject);
  TexTile(const glm::lowp_u16vec4 info);
};