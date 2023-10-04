#include "face_uv_list.h"
#include "texture_tile.h"
#include "util/debug_utils.h"

FaceUVList FaceUVList::generateFromPixels(
    const std::vector<std::vector<glm::lowp_u16vec2>> &facePixels) {
  for (const auto &face : facePixels) {
    for (const auto &vertex : face)
      std::cout << glm::to_string(vertex) << " ";
    std::cout << "\n";
  }
  return {facePixels};
}

FaceUVList
FaceUVList::generateFromUVs(const std::vector<std::vector<vec2>> &faceUVs) {
  std::vector<std::vector<glm::lowp_u16vec2>> pixels;
  for (const auto &face : faceUVs) {
    std::vector<glm::lowp_u16vec2> vertices;
    for (const auto &vertex : face) {
      std::cout << glm::to_string(vertex) << " ";

      vertices.emplace_back((unsigned short)(vertex[0] * TexTile::TEXEL_RANGE),
                            (unsigned short)(vertex[1] * TexTile::TEXEL_RANGE));
    }
    std::cout << "\n";

    pixels.emplace_back(std::move(vertices));
  }
  return {pixels};
}