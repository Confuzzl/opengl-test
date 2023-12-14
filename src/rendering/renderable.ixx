export module rendering.renderable;

import world.base_polyhedron;
import util.polyhedron;
import util.rendering;
import shaders.vertex_formats;
import wrapper.buffer_object;
import <stdexcept>;

export class Renderable : public BasePolyhedron {
public:
  struct FaceUVMismatchException : std::runtime_error {
    using std::runtime_error::runtime_error;
  };

private:
  const render::IndexList faceVertexIndices;
  const render::TexList UVs;

  Vector<VertexFormats::_3D::ColTex> vertexInfo;

  void initializeVertexInfo();

  friend UPtr<Renderable>
  std::make_unique<Renderable, EBO &, VBO &, const Vec3List &,
                   const render::IndexList &, const render::TexList &>(
      EBO &, VBO &, const Vec3List &, const render::IndexList &,
      const render::TexList &);
  Renderable(const EBO &ebo, const VBO &sharedVBO, const Vec3List &coordinates,
             const render::IndexList &faceVertexIndices,
             const render::TexList &UVs);

public:
  const EBO &ebo;
  const VBO &sharedVBO;

  void writeToSharedVBO() const;
};

export using RendPtr = UPtr<Renderable>;