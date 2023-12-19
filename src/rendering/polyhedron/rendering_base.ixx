export module rendering.base;

import world.base_polyhedron;
import rendering.shaders;
import wrapper.buffer_object;
import util.polyhedron;

import <unordered_set>;
import util.memory;

export namespace Renderable {
struct Base;

struct System {
  static std::unordered_set<Ref<Base>> entities;
};

struct Base : BasePolyhedron {
  const Shaders::Base &program;

  const EBO &ebo;
  const VBO &vbo;

  Base(const Shaders::Base &program, const EBO &ebo, const VBO &vbo,
       const Vec3List &coordinates)
      : BasePolyhedron(coordinates), program{program}, ebo{ebo}, vbo{vbo} {}
};
template <typename VertexFormat> struct Specialized : public Base {};
} // namespace Renderable