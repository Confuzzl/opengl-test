export module rendering.frame.keyframe;

import rendering.frame.frame;
import util.glm;

export struct Keyframe : public Frame {
  static const Keyframe START;

  const double time;

  Keyframe(const Mat4 &transform, const double time);
};