export module rendering.base;

import world.base_polyhedron;
import util.polyhedron;

export namespace Renderable {
struct Base : BasePolyhedron {
  Base(const Vec3List &coordinates) : BasePolyhedron(coordinates) {}
};
template <typename VertexFormat> struct Specialized : public Base {};
} // namespace Renderable