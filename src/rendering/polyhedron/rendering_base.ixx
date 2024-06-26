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
struct Polyhedron;

struct System {
  static std::map<unsigned int, Polyhedron *> objects;
};

struct Polyhedron : BasePolyhedron {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  Shaders::Base &program;

  const EBO &ebo;
  const VBO &vbo;

  virtual void writeToVBO() const = 0;

  ~Polyhedron();

private:
  const render::IndexList faceVertexIndices;

protected:
  Polyhedron(Shaders::Base &program, const EBO &ebo, const VBO &vbo,
             const Vec3List &coordinates);
};

template <VertexFormats::writable VertexFormat>
struct Drawable : public Polyhedron {
  Vector<VertexFormat> vertexInfo;

public:
  Drawable(Shaders::Base &program, const EBO &ebo, const VBO &vbo,
           const Vec3List &coordinates, Vector<VertexFormat> &&vertexInfo)
      : Polyhedron(program, ebo, vbo, coordinates), vertexInfo{vertexInfo} {}

  void writeToVBO() const override {
    GLintptr offset = 0;
    for (const auto &vertex : vertexInfo)
      vertex.writeVertexTo(offset, vbo.GLid);
  }
};
} // namespace Renderable

export using RendPtr = UPtr<Renderable::Polyhedron>;