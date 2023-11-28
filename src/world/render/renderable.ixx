export module world.render.renderable;

import world.base_polyhedron;
import util.polyhedron;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import <stdexcept>;

export class Renderable : public BasePolyhedron {
public:
  struct FaceUVMismatchException : std::runtime_error {
    using std::runtime_error::runtime_error;
  };

private:
  const RenCoordinateIndexList &faceVertexIndices;
  const UVList UVs;

  Vector<VertexFormats::_3D::ColTex> vertexInfo;

  void initializeVertexInfo();

public:
  const EBO &ebo;
  const VBO &sharedVBO;
  Renderable(const EBO &ebo, const VBO &sharedVBO, const Vec3List &coordinates,
             const RenCoordinateIndexList &faceVertexIndices,
             const UVList &UVs);

  void writeToSharedVBO() const;
};

export using RendPtr = UPtr<Renderable>;