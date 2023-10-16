module wrapper.program.vertex_formats:simple;

import util.debug;

SimpleVertex::SimpleVertex(GLfloat x, GLfloat y, GLfloat z, GLubyte r,
                           GLubyte g, GLubyte b, GLushort u, GLushort v) {
  posInfo[0] = x, posInfo[1] = y, posInfo[2] = z;
  colInfo[0] = r, colInfo[1] = g, colInfo[2] = b;
  texInfo[0] = u, texInfo[1] = v;
}

std::ostream &operator<<(std::ostream &os, const SimpleVertex &vertex) {
  os << std::format("simple: ({},{},{}),({},{},{}),({},{})", vertex.posInfo[0],
                    vertex.posInfo[1], vertex.posInfo[2], vertex.colInfo[0],
                    vertex.colInfo[1], vertex.colInfo[2], vertex.texInfo[0],
                    vertex.texInfo[1]);
  return os;
}