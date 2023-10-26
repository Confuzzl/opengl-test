export module world.collision.algorithms;

export namespace Collision {
namespace VClip {
enum class VClipOutput {
  OVERFLOW,
  OTHER,
  PENETRATION_VE,
  PENETRATION_VF,
  PENETRATION_EE,
  PENETRATION_EF,
  DONE_VV,
  DONE_VE,
  DONE_VF,
  DONE_EE
};
enum class ClipEdgeState { SIMPLE, COMPOUND, COMPLETE };
enum class PostClipEdgeState { UPPER, UNDER, DEGENERATE, NONE };
enum class DPrimeState { POSITIVE, ZERO, NEGATIVE, DEGENERATE };
} // namespace VClip
}; // namespace Collision