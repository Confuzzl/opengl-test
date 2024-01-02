export module rendering.renderable_info;

import rendering.vertex_formats.types;
import util.rendering;

import <optional>;

import <concepts>;

export namespace Renderable {
template <VertexFormats::writable> struct Info;

template <> struct Info<VertexFormats::_3D::Col> {
  std::optional<render::ColList> colInfo{std::nullopt};
};

template <> struct Info<VertexFormats::_3D::Tex> {
  std::optional<Vector<std::string>> faceTextures{std::nullopt};
  std::optional<render::TexList> UVs{std::nullopt};
};

template <> struct Info<VertexFormats::_3D::ColTex> {
  std::optional<render::ColList> colInfo{std::nullopt};
  std::optional<Vector<std::string>> faceTextures{std::nullopt};
  std::optional<render::TexList> UVs{std::nullopt};
};
} // namespace Renderable