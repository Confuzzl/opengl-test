module;

#include "util/gl_utils.hpp"

export module world.factory.base_factory;

export class Collider;
export class Renderable;

import util.polyhedron;
import util.rendering;
import util.memory;
import wrapper.buffer_object;
import world.game_object;
import world.collision.collider;
import rendering.renderable;

// import rendering.base_renderable;
import rendering.renderable_col;
import rendering.renderable_tex;
import rendering.renderable_coltex;

export class BaseFactory {
  const unsigned short vertexCount;
  const unsigned short faceCount;

  const VEIndexList veIndices;
  const EVIndexList evIndices;
  const EFIndexList efIndices;
  const FEIndexList feIndices;

  const render::IndexList defaultIndexList;
  const render::ColList defaultColList;
  const render::TexList defaultTexList;

  const unsigned int rVertexCount;
  mutable bool buffersInitialized = false;
  mutable Vector<GLuint> eboIndices{};

  void initializeBuffers() const;
  void initializeEBO() const;
  void allocateVBO() const;

  BaseFactory(const BaseFactory &) = delete;
  BaseFactory(BaseFactory &&) = delete;
  BaseFactory &operator=(const BaseFactory &) = delete;
  BaseFactory &operator=(BaseFactory &&) = delete;

protected:
  BaseFactory(const unsigned short vertexCount, const unsigned short faceCount,
              const VEIndexList &veIndices, const EVIndexList &evIndices,
              const EFIndexList &efIndices, const FEIndexList &feIndices,
              const render::IndexList &defaultIndexList,
              const render::ColList &defaultColList,
              const render::TexList &defaultTexList,
              const unsigned int rVertexCount);

public:
  ~BaseFactory();

  mutable EBO ebo{};
  mutable VBO sharedVBO{};

  CollPtr createCollidable(const Vec3List &coordinates) const;
  RendPtr createRenderable(const Vec3List &coordinates) const;
  RendPtr createRenderable(const Vec3List &coordinates,
                           const render::TexList &texList) const;

  UPtr<RenderableCol> renCol(const Vec3List &coordinates) const;
  UPtr<RenderableCol> renCol(const Vec3List &coordinates,
                             const render::ColList &colList) const;
  UPtr<RenderableTex> renTex(const Vec3List &coordinates) const;
  UPtr<RenderableTex> renTex(const Vec3List &coordinates,
                             const render::TexList &texList) const;

  UPtr<RenderableColTex> renColTex(const Vec3List &coordinates) const;
  UPtr<RenderableColTex> renColTex(const Vec3List &coordinates,
                                   const render::ColList &colList) const;
  UPtr<RenderableColTex> renColTex(const Vec3List &coordinates,
                                   const render::TexList &texList) const;
  UPtr<RenderableColTex> renColTex(const Vec3List &coordinates,
                                   const render::ColList &colList,
                                   const render::TexList &texList) const;
};