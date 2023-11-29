export module rendering.base_renderable;

// import util.memory;
import world.base_polyhedron;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import util.polyhedron;

export template <VertexFormats::IsVertexFormat VertexType>
class BaseRenderable : public BasePolyhedron {
  Vector<VertexType> vertexInfo;

  const EBO &ebo;
  const VBO &vbo;

  BaseRenderable(const EBO &ebo, const VBO &vbo, const Vec3List &coordinates)
      : BasePolyhedron(coordinates), ebo{ebo}, vbo{vbo} {}

  void initializeVertexInfo() {
    for (unsigned short f = 0; f < UVs.size(); f++) {
      initializeFaceInfo(f);
    }
  }
  void initializeFaceInfo(unsigned short f) {
    const auto &indexFace = faceVertexIndices[f];
    specializeFaceInfo(f);
    for (unsigned short t = 0; t < UVs[f].size(); t++) {
      initializeTriInfo(f, t);
    }
  }
  virtual void specializeFaceInfo(unsigned short f) = 0;
  void initializeTriInfo(unsigned short f, unsigned short t) {
    const auto &indexTri = faceVertexIndices[f][t];
    specializeTriInfo(f, t);
    for (unsigned short v = 0; v < UVs[f][t].size(); v++) {
      initializeVertexInfo(f, t, v);
    }
  }
  virtual void specializeTriInfo(unsigned short f, unsigned short t) = 0;
  void initializeVertexInfo(unsigned short f, unsigned short t,
                            unsigned short v) {
    const unsigned short &indexVertex = faceVertexIndices[f][t][v];
    const Vec3 &pos = coordinates[indexVertex];
    specializeVertexInfo(f, t, v);
  }
  virtual void specializeVertexInfo(unsigned short f, unsigned short t,
                                    unsigned short v) = 0;
};