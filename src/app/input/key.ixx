export module app.input.key;

import <functional>;

export struct GLFWwindow;

export struct Key {
  bool on = false;
  const std::function<void(int, int, int)> callback;

  Key(std::function<void(int, int, int)> &&callback) : callback{callback} {};
};