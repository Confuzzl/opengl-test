module;

#include "util/gl_utils.hpp"

export module rendering.shaders.global;

import rendering.shaders;
import rendering.vertex_formats.types;

export namespace Shaders::_2D {
struct FontProgram
    : public Specialized<VertexFormats::_2D::Font, VertexAttribute<GLfloat>,
                         VertexAttribute<GLushort>> {
  static constexpr int CHAR_WIDTH = 16, CHAR_HEIGHT = 32;

  constexpr FontProgram()
      : Specialized("font", "font", {2, GL_FALSE}, {2, GL_FALSE}) {}
};
constinit FontProgram FONT{};
} // namespace Shaders::_2D

export namespace Shaders::_3D {
using ColProgram =
    Specialized<VertexFormats::_3D::Col, VertexAttribute<GLfloat>,
                VertexAttribute<GLubyte>>;
constinit ColProgram COL{
    "col",
    "col",
    {3, GL_FALSE},
    {3, GL_TRUE},
};

using TexProgram =
    Specialized<VertexFormats::_3D::Tex, VertexAttribute<GLfloat>,
                VertexAttribute<GLushort>>;
constinit TexProgram TEX{
    "tex",
    "tex",
    {3, GL_FALSE},
    {2, GL_FALSE},
};

using ColTexProgram =
    Specialized<VertexFormats::_3D::ColTex, VertexAttribute<GLfloat>,
                VertexAttribute<GLubyte>, VertexAttribute<GLushort>>;
constinit ColTexProgram COLTEX{
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
