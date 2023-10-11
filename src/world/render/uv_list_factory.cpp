#include "uv_list_factory.h"
#include "app/texture_tile.h"
#include "util/debug_utils.h"

UVListFactory::UVListFactory(const UVList &facePixels) : faceUVs{facePixels} {}

UVListFactory::UVList
UVListFactory::generateFromPixels(const UVList &facePixels) {
  // for (const auto &face : facePixels) {
  //   for (const auto &vertex : face)
  //     std::cout << glm::to_string(vertex) << " ";
  //   std::cout << "\n";
  // }
  return facePixels;
}

UVListFactory::UVList
UVListFactory::generateFromUVs(const Vector2D<Vec2> &faceUVs) {
  UVList pixels;
  for (const auto &face : faceUVs) {
    std::vector<glm::lowp_u16vec2> vertices;
    for (const auto &vertex : face) {
      // std::cout << glm::to_string(vertex) << " ";

      vertices.emplace_back((unsigned short)(vertex[0] * TexTile::TEXEL_RANGE),
                            (unsigned short)(vertex[1] * TexTile::TEXEL_RANGE));
    }
    // std::cout << "\n";

    pixels.emplace_back(std::move(vertices));
  }
  return pixels;
}