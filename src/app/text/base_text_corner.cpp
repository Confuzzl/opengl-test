module;

#include "util/gl_utils.hpp"
#include <numeric>

module app.text.base_text_corner;

import wrapper.program.programs;
import wrapper.program.vertex_formats;
import app.app;
import wrapper.buffer_object;
import util.vector;
import util.glm;

const BaseTextCorner::OffsetEquation BaseTextCorner::xNormal =
    [](const float x, const float, const std::string) { return x; };
const BaseTextCorner::OffsetEquation BaseTextCorner::xShift =
    [](const float x, const float scale, const std::string msg) {
      return App::WIDTH - msg.size() * FontProgram::CHAR_WIDTH * scale - x;
    };
const BaseTextCorner::OffsetEquation BaseTextCorner::yNormal =
    [](const float y, const float, const std::string) { return y; };
const BaseTextCorner::OffsetEquation BaseTextCorner::yShift =
    [](const float y, const float scale, const std::string msg) {
      return App::HEIGHT - FontProgram::CHAR_HEIGHT * scale - y;
    };

BaseTextCorner::BaseTextCorner(const OffsetEquation &xEquation,
                               const OffsetEquation &yEquation)
    : xEquation{xEquation}, yEquation{yEquation} {}

void BaseTextCorner::drawText(const std::string &msg) { drawText(1, msg); }

void BaseTextCorner::drawText(const float scale, const std::string &msg) {
  drawText(0, 0, scale, msg);
}
void BaseTextCorner::drawText(const float x, const float y, const float scale,
                              const std::string &msg) {
  drawText(x, y, scale, msg, true, true);
}

void BaseTextCorner::drawText(const float x, const float y, const float scale,
                              const std::string &msg, bool followOffset,
                              bool addToOffset) {
  const float x2 = xEquation(x, scale, msg),
              y2 = yEquation(y + textOffsetY, scale, msg);
  float xOffset = x2;
  const size_t vertexCount = 6 * msg.size();

  Vector<GLuint> indices{};
  indices.resize(vertexCount);
  std::iota(indices.begin(), indices.end(), 0);

  EBO ebo{};
  ebo.allocateBufferObject(vertexCount * sizeof(GLuint));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, indices.data());

  Vector<FontVertex> vertices{};
  vertices.reserve(vertexCount);

  const float width = FontProgram::CHAR_WIDTH * scale,
              height = FontProgram::CHAR_HEIGHT * scale;
  for (const char &c : msg) {
    TexTile tex = app.consolas.getTile(c);
    for (int tri = 0; tri < 2; tri++) {
      for (int vertex = 0; vertex < 3; vertex++) {
        const Vec2 pos{xOffset + width * QUAD_UVS[tri][vertex][0],
                       y2 + height * QUAD_UVS[tri][vertex][1]};
        const glm::lowp_u16vec2 uv{tex.coordinates +
                                   tex.dimensions * QUAD_UVS[tri][vertex]};
        vertices.emplace_back(pos[0], pos[1], uv[0], uv[1]);
      }
    }

    xOffset += width * 1;
  }

  VBO vbo{};
  vbo.allocateBufferObject(vertexCount * FontVertex::WIDTH);
  GLintptr offset = 0;
  for (const FontVertex &vertex : vertices) {
    glNamedBufferSubData(vbo.ID, offset, FontVertex::POS_WIDTH, vertex.posInfo);
    offset += FontVertex::POS_WIDTH;
    glNamedBufferSubData(vbo.ID, offset, FontVertex::TEX_WIDTH, vertex.texInfo);
    offset += FontVertex::TEX_WIDTH;
  }

  app.fontProgram.vao.bindEBO(ebo);
  app.fontProgram.vao.bindVBO(vbo);

  app.fontProgram.useProgram();
  app.fontProgram.setMat4("projection", App::UI_MAT);

  app.consolas.atlas.bindTextureUnit();
  app.fontProgram.vao.bindVertexArray();
  glDrawElements(GL_TRIANGLES, (GLsizei)app.fontProgram.vao.boundedEBO.size,
                 GL_UNSIGNED_INT, 0);

  if (addToOffset)
    textOffsetY += height;
}

void BaseTextCorner::resetTextOffset() { textOffsetY = 0; }