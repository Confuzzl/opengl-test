module;

#include "util/gl_utils.hpp"

export module shaders.global;

import shaders;

export namespace Shaders::_2D {
struct FontProgram : public ShaderProgram<VertexAttribute<GLfloat>,
                                          VertexAttribute<GLushort>> {
  static constexpr int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;

  constexpr FontProgram()
      : ShaderProgram("font", "font", {2, GL_FALSE}, {2, GL_FALSE}) {}
};
constinit FontProgram FONT{};
} // namespace Shaders::_2D

export namespace Shaders::_3D {
constinit ShaderProgram COL{
    "col",
    "collll",
    VertexAttribute<GLfloat>{3, GL_FALSE},
    VertexAttribute<GLubyte>{3, GL_TRUE},
};
constinit ShaderProgram TEX{
    "tex",
    "tex",
    VertexAttribute<GLfloat>{3, GL_FALSE},
    VertexAttribute<GLushort>{2, GL_FALSE},
};
constinit ShaderProgram COLTEX{
    "coltex",
    "coltex",
    VertexAttribute<GLfloat>{3, GL_FALSE},
    VertexAttribute<GLubyte>{3, GL_TRUE},
    VertexAttribute<GLushort>{2, GL_FALSE},
};
}; // namespace Shaders::_3D

export namespace Shaders {
void createAll() {
  _2D::FONT.create();
  _3D::COL.create();
  _3D::TEX.create();
  _3D::COLTEX.create();
}
} // namespace Shaders
