module;

#include "util/gl_utils.hpp"

export module rendering.base_renderable;

import world.base_polyhedron;
import shaders.vertex_formats;
import wrapper.buffer_object;
import util.rendering;
import util.polyhedron;

// import wrapper.program.programs;
import shaders;

export template </*VertexFormats::IsVertexFormat*/ typename VertexType>
class BaseRenderable : public BasePolyhedron {
public:
  const /*Programs::Base*/ Shaders::ShaderProgram &program;

  const EBO &ebo;
  const VBO &vbo;

  const render::IndexList &indexList;

  Vector<VertexType> vertexInfo;

  void writeToVBO() const {
    GLintptr offset = 0;
    for (const auto &vertex : vertexInfo) {
      vertex.writeVertexTo(offset, vbo.ID);
    }
  }

  void finishConstruction() {
    vertexInfo.reserve(coordinates.size());

    specializeConstruction();
  }

protected:
  BaseRenderable(const /*Programs::Base*/ Shaders::ShaderProgram &program,
                 const EBO &ebo, const VBO &vbo, const Vec3List &coordinates,
                 const render::IndexList &indexList)
      : BasePolyhedron(coordinates), program{program}, ebo{ebo}, vbo{vbo},
        indexList{indexList} {}

  virtual bool exceptionCondition() = 0;

  virtual void specializeConstruction() = 0;
};