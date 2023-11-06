export module world.collision.feature.differentiable_feature;

import world.collision.algorithms;

export class Edge;

export class DifferentiableFeature {
public:
  virtual Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                                   float l) const = 0;
};