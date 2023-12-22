export module rendering.base;

import world.base_polyhedron;
import rendering.shaders;
import rendering.vertex_formats.types;
import wrapper.buffer_object;

import util.polyhedron;
import util.rendering;
import util.memory;

import <map>;

export namespace Renderable {
struct Base;

struct System {
  static std::map<unsigned int, Base *> objects;
};

struct Base : BasePolyhedron {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  Shaders::Base &program;

  const EBO &ebo;
  const VBO &vbo;

  virtual void writeToVBO() const = 0;

private:
  const render::IndexList faceVertexIndices;

protected:
  Base(Shaders::Base &program, const EBO &ebo, const VBO &vbo,
       const Vec3List &coordinates);
};
template <VertexFormats::writable VertexFormat>
struct Specialized : public Base {
  Vector<VertexFormat> vertexInfo;

public:
  using Base::Base;

  void writeToVBO() const override;
};
} // namespace Renderable