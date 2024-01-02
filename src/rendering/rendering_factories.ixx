export module rendering.factory;

import factory.base_factory;

import util.memory;
import util.polyhedron;
import rendering.base;
import rendering.shaders.global;
import rendering.vertex_formats.types;
import rendering.renderable_info;
import app.texture_tile;

export namespace Factory {
template <VertexFormats::writable VertexType>
UPtr<Renderable::Drawable<VertexType>>
createRenderable(const Base &factory, const Vec3List &coordinates,
                 const Renderable::Info<VertexType> &info = {});

template <>
UPtr<Renderable::Drawable<VertexFormats::_3D::Col>>
createRenderable(const Base &factory, const Vec3List &coordinates,
                 const Renderable::Info<VertexFormats::_3D::Col> &info) {
  Vector<VertexFormats::_3D::Col> vertexInfo{};
  for (auto f = 0; f < factory.defaultIndexList.size(); f++) {
    const render::IndexFace &indexFace = factory.defaultIndexList[f];
    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Col &colVertex =
            info.colInfo.value_or(factory.defaultColList)[f][t][v];

        vertexInfo.emplace_back(coordinate[0], coordinate[1], coordinate[2],
                                colVertex[0], colVertex[1], colVertex[2]);
      }
    }
  }
  return std::make_unique<Renderable::Drawable<VertexFormats::_3D::Col>>(
      Shaders::_3D::COL, factory.ebo, factory.sharedVBO, coordinates,
      std::move(vertexInfo));
}

template <>
UPtr<Renderable::Drawable<VertexFormats::_3D::Tex>>
createRenderable(const Base &factory, const Vec3List &coordinates,
                 const Renderable::Info<VertexFormats::_3D::Tex> &info) {
  Vector<VertexFormats::_3D::Tex> vertexInfo{};
  for (auto f = 0; f < factory.defaultIndexList.size(); f++) {
    const render::IndexFace &indexFace = factory.defaultIndexList[f];
    const TexTile &texture{TexTile::getTile(info.faceTextures.has_value()
                                                ? info.faceTextures.value()[f]
                                                : TexTile::getRandomTexture())};
    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Tex &texVertex =
            info.UVs.value_or(factory.defaultTexList)[f][t][v];
        const TexTile::IntUV intUV{texture.globalIntUV(texVertex)};

        vertexInfo.emplace_back(coordinate[0], coordinate[1], coordinate[2],
                                intUV[0], intUV[1]);
      }
    }
  }
  return std::make_unique<Renderable::Drawable<VertexFormats::_3D::Tex>>(
      Shaders::_3D::TEX, factory.ebo, factory.sharedVBO, coordinates,
      std::move(vertexInfo));
}

template <>
UPtr<Renderable::Drawable<VertexFormats::_3D::ColTex>>
createRenderable(const Base &factory, const Vec3List &coordinates,
                 const Renderable::Info<VertexFormats::_3D::ColTex> &info) {
  Vector<VertexFormats::_3D::ColTex> vertexInfo{};
  for (auto f = 0; f < factory.defaultIndexList.size(); f++) {
    const render::IndexFace &indexFace = factory.defaultIndexList[f];
    const TexTile &texture{TexTile::getTile(info.faceTextures.has_value()
                                                ? info.faceTextures.value()[f]
                                                : TexTile::getRandomTexture())};
    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Col &colVertex =
            info.colInfo.value_or(factory.defaultColList)[f][t][v];

        const render::Tex &texVertex =
            info.UVs.value_or(factory.defaultTexList)[f][t][v];
        const TexTile::IntUV intUV{texture.globalIntUV(texVertex)};

        vertexInfo.emplace_back(coordinate[0], coordinate[1], coordinate[2],
                                colVertex[0], colVertex[1], colVertex[2],
                                intUV[0], intUV[1]);
      }
    }
  }
  return std::make_unique<Renderable::Drawable<VertexFormats::_3D::ColTex>>(
      Shaders::_3D::COLTEX, factory.ebo, factory.sharedVBO, coordinates,
      std::move(vertexInfo));
}
} // namespace Factory