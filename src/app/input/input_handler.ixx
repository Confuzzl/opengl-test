module;

#include "util/gl_utils.hpp"

export module app.input.input_handler;

import app.app;
import world.scene;
import world.entity.player;
import world.camera;

import util.vector;
import util.glm;
import util.debug;

import <map>;
import <functional>;

export struct InputHandler {
  struct Key {
    using Callback = std::function<void(const double)>;

    static const Callback NONE;

    bool on = false;
    bool justUsed = false;

    const Callback processJustOn;
    const Callback processOn;
    const Callback processJustOff;
    const Callback processOff;

    Key(const Callback &processJustOn, const Callback &processOn,
        const Callback &processJustOff, const Callback &processOff)
        : processJustOn{processJustOn}, processOn{processOn},
          processJustOff{processJustOff}, processOff{processOff} {}
    Key(const Callback &processOn, const Callback &processOff)
        : Key(processOn, processOn, processOff, processOff){};
    Key(const Callback &processOn) : Key(processOn, NONE) {}

    void change(int action) {
      switch (action) {
      case GLFW_RELEASE: {
        on = false;
        justUsed = true;
        break;
      }
      case GLFW_PRESS: {
        on = true;
        justUsed = true;
        break;
      }
      case GLFW_REPEAT: {
      }
      }
    }

    void operator()(const double dt) {
      if (on && justUsed) {
        processJustOn(dt);
        justUsed = false;
      }
      if (on && not justUsed) {
        processOn(dt);
      }
      if (not on && justUsed) {
        processJustOff(dt);
        justUsed = false;
      }
      if (not on && not justUsed) {
        processOff(dt);
      }
    }

    static Callback
    playerMoveFunction(const std::function<Vec3()> &directionSupplier,
                       const double m) {
      return [directionSupplier, m](const double dt) {
        mainPlayer.translate(directionSupplier() *
                             static_cast<float>(dt * m * mainPlayer.speed));
      };
    }

    static Callback cameraRotateFunction(const double a, const double b) {
      return [a, b](const double dt) {
        const float sens = mainCamera.getSensitivity();
        mainCamera.rotate(static_cast<float>(sens * dt * a),
                          static_cast<float>(sens * dt * b));
      };
    }
  };

  static std::map<int, Key> keys;

  static void processInput(const double dt);

  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void mouseCallback(GLFWwindow *window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow *window, double xpos, double ypos);
};