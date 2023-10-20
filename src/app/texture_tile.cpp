module;

#include <ranges>

module app.texture_tile;

import util.math;

const std::map<std::string, glm::lowp_u16vec4> TexTile::textureDict = {
    {"error", {0, 0, 16, 16}},         {"debug_1", {16, 0, 16, 16}},
    {"debug_2", {32, 0, 16, 16}},      {"grass", {0, 16, 16, 16}},
    {"cobblestone", {16, 16, 16, 16}}, {"stone", {32, 16, 16, 16}},
    {"log_side", {48, 16, 16, 16}},    {"log_top", {64, 16, 16, 16}},
    {"test", {112, 112, 16, 16}}};
const Vector<std::string> TexTile::textureKeys = {
    std::views::keys(TexTile::textureDict).begin(),
    std::views::keys(TexTile::textureDict).end()};

TexTile TexTile::getTile(const std::string name, const TexObject &texObject) {
  float width = static_cast<float>(texObject.width),
        height = static_cast<float>(texObject.height);
  Vec4 info{textureDict.at(textureDict.contains(name) ? name : "error")};
  info[1] = height - info[1] - info[3]; // flip y values
  info /= Vec4{width, height, width, height};
  info *= Vec4{TEXEL_RANGE};
  return {info};
}
std::string TexTile::getRandomTexture() {
  return TexTile::textureKeys[(unsigned int)random(
      0, static_cast<double>(TexTile::textureDict.size()))];
}
TexTile TexTile::getRandomTile(const TexObject &texObject) {
  return getTile(getRandomTexture(), texObject);
}

TexTile::TexTile(const glm::lowp_u16vec4 info)
    : coordinates{info[0], info[1]}, dimensions{info[2], info[3]} {}