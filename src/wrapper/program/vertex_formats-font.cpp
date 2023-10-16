module wrapper.program.vertex_formats:font;

import util.debug;

FontVertex::FontVertex(GLfloat x, GLfloat y, GLushort u, GLushort v) {
  posInfo[0] = x, posInfo[1] = y;
  texInfo[0] = u, texInfo[1] = v;
}

std::ostream &operator<<(std::ostream &os, const FontVertex &vertex) {
  os << std::format("font: ({},{}),({},{})", vertex.posInfo[0],
                    vertex.posInfo[1], vertex.texInfo[0], vertex.texInfo[1]);
  return os;
}