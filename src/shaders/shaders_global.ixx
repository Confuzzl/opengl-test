module;

#include "util/gl_utils.hpp"

export module shaders.global;

import shaders;

export namespace Shaders::_2D {
constinit ShaderProgram FONT{
    "font",
    "font",
    VertexAttribute<GLfloat>{2},
    VertexAttribute<GLushort>{2},
};
} // namespace Shaders::_2D

export namespace Shaders::_3D {

constinit ShaderProgram COL{
    "col",
    "col",
    VertexAttribute<GLfloat>{3},
    VertexAttribute<GLubyte>{3},
};
constinit ShaderProgram TEX{
    "tex",
    "tex",
    VertexAttribute<GLfloat>{3},
    VertexAttribute<GLushort>{2},
};
constinit ShaderProgram COLTEX{
    "coltex",
    "coltex",
    VertexAttribute<GLfloat>{3},
    VertexAttribute<GLubyte>{3},
    VertexAttribute<GLushort>{2},
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
