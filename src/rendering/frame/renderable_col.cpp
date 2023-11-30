module rendering.renderable_col;

RenderableCol::RenderableCol(const EBO &ebo, const VBO &vbo,
                             const Vec3List &coordinates,
                             const render::IndexList &indexList,
                             const render::ColList &colList)
    : BaseRenderable<VertexFormats::_3D::Colored>(ebo, vbo, coordinates,
                                                  indexList),
      colList{colList} {}