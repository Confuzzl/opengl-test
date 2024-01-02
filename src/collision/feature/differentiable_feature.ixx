export module collision.feature.differentiable_feature;

import collision.algorithms;

export class Edge;

export class DifferentiableFeature {
public:
  virtual Collision::VClip::DPrimeState signDPrime(const Edge &e,
                                                   const float l) const = 0;
};