export module rendering.frame.frame;

import util.glm;

export struct Frame {
  const Mat4 transform;

  Frame(const Mat4 &transform);
};