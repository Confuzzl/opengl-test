export module rendering.base_renderable;

// import util.memory;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import util.vector;

export template <VertexFormats::IsVertexFormat VertexType>
class BaseRenderable {
  Vector<VertexType> vertexInfo;

  const EBO &ebo;
  const VBO &vbo;

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
  }
  virtual void specializeTriInfo() = 0;
  void initializeVertexInfo();
  virtual void specializeVertexInfo() = 0;
};