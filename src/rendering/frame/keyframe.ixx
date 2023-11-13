export module rendering.frame.keyframe;

import rendering.frame.frame;
import util.memory;
import util.glm;

export struct Keyframe : public Frame {
  const double time;

  Keyframe(const Mat4 &transform, const double time);

  static UPtr<const Keyframe> start();
  static UPtr<const Keyframe> from(const Mat4 &transform, const double time);
};