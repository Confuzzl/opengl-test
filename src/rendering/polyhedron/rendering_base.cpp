module;

#include "util/gl_utils.hpp"

module rendering.base;

Renderable::Base::Base(Shaders::Base &program, const EBO &ebo, const VBO &vbo,
                       const Vec3List &coordinates)
    : BasePolyhedron(coordinates), ID{COUNT++}, program{program}, ebo{ebo},
      vbo{vbo} {}

template <VertexFormats::writable VertexFormat>
void Renderable::Specialized<VertexFormat>::writeToVBO() const {
  GLintptr offset = 0;
  for (const auto &vertex : vertexInfo)
    vertex.writeVertexTo(offset, vbo.GLid);
}