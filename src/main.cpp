#include "util/gl_utils.hpp"

import app.app;
import util.debug;
import app.text.text_corners;
import world.factory.factories;
import world.game_object;
import util.polyhedron;

int main() {
  Vec3 a{1, 1, 1};
  a *= 2;

  Vec3List coordinates1{{-1, -1, +1}, {+1, -1, -1}, {+1, +1, +1}, {-1, +1, -1}};
  for (auto &v : coordinates1)
    v /= 2;

  Vec3List coordinates2{{-1, -1, 1},  {+1, -1, +1}, {+1, +1, +1}, {-1, +1, +1},
                        {-1, +1, -1}, {+1, +1, -1}, {+1, -1, -1}, {-1, -1, -1}};
  for (auto &v : coordinates2)
    v /= 2;

  GameObject go1{SIMPLEX_FACTORY.createCollidable(coordinates1),
                 SIMPLEX_FACTORY.createRenderable(coordinates1)};

  GameObject go2{PRISM_FACTORY.createCollidable(coordinates2),
                 PRISM_FACTORY.createRenderable(coordinates2)};
  go2.translate({0, -2, 0});

  glLineWidth(5);
  glPolygonMode(GL_FRONT, GL_FILL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(app.window)) {
    try {
      double currTime = glfwGetTime();

      app.loopCycle.pushNewTime(currTime);
      if (app.updateCycle.pastLength(currTime)) {
        app.updateCycle.pushNewTime(currTime);
        glfwPollEvents();
        app.processInput();
      }
      if (app.frameCycle.pastLength(currTime)) {
        app.frameCycle.pushNewTime(currTime);

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        app.drawScene();

        Text::resetAllTextOffsets();

        const auto &cam = app.scene.camera;
        const auto &pos = cam.getPosition();
        Text::TOP_LT.drawText(std::format("POS: {:+.3f} {:+.3f} {:+.3f}",
                                          pos[0], pos[1], pos[2]));
        Text::TOP_LT.drawText(
            std::format("CAM: {:+.3f} {:+.3f}", cam.getYaw(), cam.getPitch()));

        Text::TOP_RT.drawText(std::format("FPS: {}", app.frameCycle.prevCount));
        Text::TOP_RT.drawText(std::format("Time: {:.2f}s", currTime));
        Text::TOP_RT.drawText(std::format("LPS: {}", app.loopCycle.prevCount));
        Text::TOP_RT.drawText(
            std::format("UPS: {}", app.updateCycle.prevCount));

        glfwSwapBuffers(app.window);
      }
      if (currTime - app.seconds >= 1) {
        app.seconds++;
        app.loopCycle.pushCount();
        app.updateCycle.pushCount();
        app.frameCycle.pushCount();
      }
    } catch (const std::runtime_error &e) {
      app.catchException(e);
    }
  }
  std::cout << std::format("app terminated at {:.2f}s\n", glfwGetTime());
  glfwTerminate();
}
