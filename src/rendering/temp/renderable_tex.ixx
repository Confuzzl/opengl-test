export module rendering.renderable_tex;

import rendering.base_renderable;
import shaders.vertex_formats;
import wrapper.buffer_object;
import util.rendering;
import util.polyhedron;

export class RenderableTex
    : public BaseRenderable<VertexFormats::_3D::Textured> {
  const render::TexList &texList;

public:
  RenderableTex(const EBO &ebo, const VBO &vbo, const Vec3List &coordinates,
                const render::IndexList &indexList,
                const render::TexList &texList);

private:
  bool exceptionCondition() override;

  void specializeConstruction() override;
};