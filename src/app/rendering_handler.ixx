export module app.rendering_handler;

import util.gl_types;

export struct RenderingHandler {
  GLPrimitive primitive = GLPrimitive::TRIANGLES;

  void renderFrame(const double t);

private:
  void renderText(const double t);
  void renderScene(const double t);
};