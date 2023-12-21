export module rendering.base;

import world.base_polyhedron;
import rendering.shaders;
import rendering.vertex_formats.types;
import wrapper.buffer_object;
import util.polyhedron;

import <unordered_set>;
import util.rendering;
import util.memory;

export namespace Renderable {
struct Base;

struct System {
  static std::unordered_set<Ref<Base>> entities;
};

struct Base : BasePolyhedron {
public:
  const Shaders::Base &program;

  const EBO &ebo;
  const VBO &vbo;

private:
  const render::IndexList faceVertexIndices;

protected:
  Base(const Shaders::Base &program, const EBO &ebo, const VBO &vbo,
       const Vec3List &coordinates);
};
template <typename VertexFormat> struct Specialized : public Base {
  Vector<VertexFormat> vertexInfo;

public:
  void writeToVBO() const;
};
} // namespace Renderable