module;

#include "util/gl_utils.hpp"

module app.rendering_handler;

import app.app;
import world.scene;
import world.entity.player;
import world.camera;
import app.update_cycle;
import app.text.text_corners;
import util.glm;
import util.debug;

void RenderingHandler::renderFrame(const double t) {
  glClearColor(0, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderScene(t);
  renderText(t);

  glfwSwapBuffers(mainApp.window);
}

void RenderingHandler::renderText(const double t) {
  Text::resetAllTextOffsets();

  const Camera &cam{mainApp.scene->player->getCamera()};
  const Vec3 pos{cam.getPosition()};
  Text::TOP_LT.drawText(
      std::format("POS: {:+.3f} {:+.3f} {:+.3f}", pos[0], pos[1], pos[2]));
  Text::TOP_LT.drawText(
      std::format("CAM: {:+.3f} {:+.3f}", cam.getYaw(), cam.getPitch()));

  Text::TOP_RT.drawText(std::format("FPS: {}", mainApp.frameCycle->prevCount));
  Text::TOP_RT.drawText(std::format("Time: {:.2f}s", t));
  Text::TOP_RT.drawText(std::format("LPS: {}", mainApp.loopCycle->prevCount));
  Text::TOP_RT.drawText(std::format("UPS: {}", mainApp.updateCycle->prevCount));

  Text::BOT_RT.drawText(std::format("{:.2f}", mainPlayer.speed));
}
void RenderingHandler::renderScene(const double t) {}