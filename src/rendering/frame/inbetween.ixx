export module rendering.frame.inbetween;

import rendering.frame.frame;
import rendering.frame.keyframe;

export struct Inbetween : public Frame {
  static const Inbetween IDENTITY;

  using Frame::Frame;
};