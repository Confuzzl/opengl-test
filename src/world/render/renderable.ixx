export module world.render.renderable;

import world.base_polyhedron;
import util.polyhedron;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import <stdexcept>;
import <array>;

struct RTri {
  const Vec2 v1, v2, v3;

  const Vec2 &operator[](unsigned char index) const {
    unsigned char i = index % 3;
    switch (i) {
    case 0:
      return v1;
    case 1:
      return v2;
    case 2:
      return v3;
    }
    return v1;
  }
};

struct RFace {
  const Vector<RTri> tris;
};

export class Renderable : public BasePolyhedron {
public:
  struct FaceUVMismatchException : std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  using UVList = Vector2D<Vec2>;
  using UVListTest2 = Vector<RFace>;

private:
  const FaceVertexList &faceVertexIndices;
  UVList faceTextureList;

  UVListTest2 UVs;

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