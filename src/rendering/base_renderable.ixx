module;

#include "util/gl_utils.hpp"

export module rendering.base_renderable;

import world.base_polyhedron;
import wrapper.program.vertex_formats;
import wrapper.buffer_object;
import util.rendering;
import util.polyhedron;

export template </*VertexFormats::IsVertexFormat*/ typename VertexType>
class BaseRenderable : public BasePolyhedron {
public:
  const EBO &ebo;
  const VBO &vbo;

  const render::IndexList &indexList;

  Vector<VertexType> vertexInfo;

  void writeToVBO() const { GLintptr offset = 0; }

  void finishConstruction() {
    vertexInfo.reserve(coordinates.size());
    for (unsigned short f = 0; f < indexList.size(); f++) {
      initializeFaceInfo(f);
    }
  }

protected:
  BaseRenderable(const EBO &ebo, const VBO &vbo, const Vec3List &coordinates,
                 const render::IndexList &indexList)
      : BasePolyhedron(coordinates), ebo{ebo}, vbo{vbo}, indexList{indexList} {
    // initialize(); call in factory after ctor
  }

  virtual bool exceptionCondition() = 0;

  virtual void specializeFaceInfo(const unsigned short f) = 0;
  virtual void specializeTriInfo(const unsigned short f,
                                 const unsigned short t) = 0;
  virtual void specializeVertexInfo(const unsigned short f,
                                    const unsigned short t,
                                    const unsigned short v) = 0;

  void initializeFaceInfo(const unsigned short f) {
    // const auto &indexFace = posList[f];
    specializeFaceInfo(f);
    for (unsigned short t = 0; t < indexList[f].size(); t++) {
      initializeTriInfo(f, t);
    }
  }

  void initializeTriInfo(const unsigned short f, const unsigned short t) {
    // const auto &indexTri = posList[f][t];
    specializeTriInfo(f, t);
    for (unsigned short v = 0; v < indexList[f][t].size(); v++) {
      initializeVertexInfo(f, t, v);
    }
  }

  void initializeVertexInfo(const unsigned short f, const unsigned short t,
                            const unsigned short v) {
    const unsigned short &vertexIndex = indexList[f][t][v];
    const Vec3 &pos = coordinates[vertexIndex];
    specializeVertexInfo(f, t, v);
  }
};