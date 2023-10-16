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
  using UVList = Vector2D<Vec2>;

private:
  const FaceVertexList &faceVertexIndices;
  UVList faceTextureList;
  Vector<SimpleVertex> vertexInfo;

  void initializeVertexInfo();

public:
  EBO &ebo;
  VBO &sharedVBO;
  Renderable(EBO &ebo, VBO &sharedVBO, const Vec3List &coordinates,
             const FaceVertexList &faceVertexIndices,
             const UVList &faceTextureList);

  void writeToSharedVBO();
};