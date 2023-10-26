export module world.collision.features.differentiable_feature;

import world.collision.algorithms;

export class Edge;

export class DifferentiableFeature {
public:
  virtual Collision::VClip::DPrimeState signDPrime(const Edge &e, double l) = 0;
};