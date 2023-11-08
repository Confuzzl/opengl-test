#include "util/gl_utils.hpp"

import app.app;
import util.debug;
import world.factory.factories;
import world.game_object;
import util.polyhedron;

int main() {
  Vec3List coordinates1{{-1, -1, +1}, {+1, -1, -1}, {+1, +1, +1}, {-1, +1, -1}};
  for (auto &v : coordinates1)
    v /= 2;

  Vec3List coordinates2{{-1, -1, 1},  {+1, -1, +1}, {+1, +1, +1}, {-1, +1, +1},
                        {-1, +1, -1}, {+1, +1, -1}, {+1, -1, -1}, {-1, -1, -1}};
  for (auto &v : coordinates2)
    v /= 2;

  auto &go1{GameObject::from(SIMPLEX_FACTORY, coordinates1)};

  auto &go2{GameObject::from(PRISM_FACTORY, coordinates2)};
  go2.translate({0, -2, 0});

  glLineWidth(5);
  glPolygonMode(GL_FRONT, GL_FILL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glfwSwapInterval(0);

  app.start();
}
