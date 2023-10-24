#include "util/gl_utils.hpp"

import app.app;
import util.debug;
import app.text.text_corners;
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
        // unsigned short y = 16;
        // app.drawTextTopLeft(16, y += 16, 1,
        //                     std::format("Time: {:.2f}s", currTime));
        // app.drawTextTopLeft(16, 48, 1,
        //                     std::format("LPS: {}", app.loopCycle.prevCount));
        // app.drawTextTopLeft(16, 80, 1,
        //                     std::format("UPS: {}",
        //                     app.updateCycle.prevCount));
        // app.drawTextTopLeft(16, 112, 1,
        //                     std::format("FPS: {}",
        //                     app.frameCycle.prevCount));
        BOTTOM_LEFT.resetTextOffset();
        BOTTOM_LEFT.drawTextRelative(0, 0, 1, "bottom left");
        BOTTOM_LEFT.drawTextRelative(0, 0, 1, "bottom left");
        TOP_LEFT.resetTextOffset();
        TOP_LEFT.drawTextRelative(0, 0, 1, "top left");
        TOP_LEFT.drawTextRelative(0, 0, 1, "top left");
        BOTTOM_RIGHT.resetTextOffset();
        BOTTOM_RIGHT.drawTextRelative(0, 0, 1, "bottom right");
        BOTTOM_RIGHT.drawTextRelative(0, 0, 1, "bottom right");
        TOP_RIGHT.resetTextOffset();
        TOP_RIGHT.drawTextRelative(0, 0, 1, "top right");
        TOP_RIGHT.drawTextRelative(0, 0, 1, "top right");

        const auto &pos = app.scene.camera.getPosition();
        // app.drawTextTopLeft(16, 144, 1, std::format("X: {:+.3f}", pos[0]));
        // app.drawTextTopLeft(16, 176, 1, std::format("Y: {:+.3f}", pos[1]));
        // app.drawTextTopLeft(16, 208, 1, std::format("Z: {:+.3f}", pos[2]));

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
