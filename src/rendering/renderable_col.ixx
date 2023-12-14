export module rendering.renderable_col;

import rendering.base_renderable;
import shaders.vertex_formats;
import wrapper.buffer_object;
import util.rendering;
import util.polyhedron;

export class RenderableCol
    : public BaseRenderable<VertexFormats::_3D::Colored> {
  const render::ColList &colList;

public:
  RenderableCol(const EBO &ebo, const VBO &vbo, const Vec3List &coordinates,
                const render::IndexList &indexList,
                const render::ColList &colList);

private:
  bool exceptionCondition() override;

  void specializeConstruction() override;

  // void specializeFaceInfo(const unsigned short f) override;
  // void specializeTriInfo(const unsigned short f,
  //                        const unsigned short t) override;
  // void specializeVertexInfo(const unsigned short f, const unsigned short t,
  //                           const unsigned short v) override;
};