export module world.render.renderable;

import world.base_polyhedron;
import util.polyhedron;
import world.render.uv_list_factory;
import wrapper.program.vertex_formats;
import <stdexcept>;

export class Renderable : public BasePolyhedron {
  struct FaceUVMismatchException : std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  const FaceVertexList &faceVertexIndices;
  UVListFactory::UVList faceTextureList;
  Vector<DefaultVertex> vertexInfo;

  void initializeVertexInfo();

public:
  Renderable(const Vec3List &coordinates,
             const FaceVertexList &faceVertexIndices,
             const UVListFactory::UVList &faceTextureList);
};