export module rendering.renderable_coltex;

import rendering.base_renderable;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import util.rendering;
import util.polyhedron;

export class RenderableColTex
    : public BaseRenderable<VertexFormats::_3D::ColTex> {
  const render::ColList &colList;
  const render::TexList &texList;

public:
  RenderableColTex(const EBO &ebo, const VBO &vbo, const Vec3List &coordinates,
                   const render::IndexList &indexList,
                   const render::ColList &colList,
                   const render::TexList &texList);

private:
  bool exceptionCondition() override;

  void specializeConstruction() override;
};