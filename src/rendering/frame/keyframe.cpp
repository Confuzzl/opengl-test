module rendering.frame.keyframe;

Keyframe::Keyframe(const Mat4 &transform, const double time)
    : Frame(transform), time{time} {}

UPtr<const Keyframe> Keyframe::start() { return from(Mat4{1.0f}, 0); }
UPtr<const Keyframe> Keyframe::from(const Mat4 &transform, const double time) {
  return std::make_unique<const Keyframe>(transform, time);
}