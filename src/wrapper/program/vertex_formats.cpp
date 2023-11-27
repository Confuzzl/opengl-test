module wrapper.program.vertex_formats;

import util.vector;

VertexFormats::Base3::Base3(GLfloat x, GLfloat y, GLfloat z)
    : posInfo{{x, y, z}} {}
VertexFormats::Col::Col(GLfloat x, GLfloat y, GLfloat z, GLubyte r, GLubyte g,
                        GLubyte b)
    : Base3(x, y, z), colInfo{{r, g, b}} {}
VertexFormats::Tex::Tex(GLfloat x, GLfloat y, GLfloat z, GLushort u, GLushort v)
    : Base3(x, y, z), texInfo{{u, v}} {}
VertexFormats::ColTex::ColTex(GLfloat x, GLfloat y, GLfloat z, GLubyte r,
                              GLubyte g, GLubyte b, GLushort u, GLushort v)
    : Base3(x, y, z), Col(x, y, z, r, g, b), Tex(x, y, z, u, v) {}
