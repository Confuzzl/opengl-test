#include "texture_tile.h"
#include "util/debug_utils.h"

const std::map<std::string, glm::lowp_u16vec4> TexTile::textureDict{
    {"error", {0, 0, 16, 16}},         {"debug_1", {16, 0, 16, 16}},
    {"debug_2", {32, 0, 16, 16}},      {"grass", {0, 16, 16, 16}},
    {"cobblestone", {16, 16, 16, 16}}, {"stone", {32, 16, 16, 16}},
    {"log_side", {48, 16, 16, 16}},    {"log_top", {64, 16, 16, 16}},
    {"test", {112, 112, 16, 16}}};

TexTile TexTile::getTile(const std::string name, const TexObject &texObject) {
  float width = (float)texObject.width, height = (float)texObject.height;
  vec4 info = {textureDict.at(textureDict.contains(name) ? name : "error")};
  info[1] = height - info[1] - info[3]; // flip y values
  info /= vec4{width, height, width, height};
  info *= vec4{TEXEL_RANGE};
  return {info};
}

TexTile::TexTile(const glm::lowp_u16vec4 info)
    : coordinates{info[0], info[1]}, dimensions{info[2], info[3]} {}