module rendering.renderable_col;

RenderableCol::RenderableCol(const EBO &ebo, const VBO &vbo,
                             const Vec3List &coordinates,
                             const render::IndexList &indexList,
                             const render::ColList &colList)
    : BaseRenderable<VertexFormats::_3D::Colored>(ebo, vbo, coordinates,
                                                  indexList),
      colList{colList} {}

bool RenderableCol::exceptionCondition() {
  return indexList.size() != colList.size();
}

void RenderableCol::specializeFaceInfo(const unsigned short f) {}
void RenderableCol::specializeTriInfo(const unsigned short f,
                                      const unsigned short t) {}
void RenderableCol::specializeVertexInfo(const unsigned short f,
                                         const unsigned short t,
                                         const unsigned short v) {}