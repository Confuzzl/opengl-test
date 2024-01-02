export module collision.factory;

import factory.base_factory;

import collision.collider;
import util.memory;
import util.polyhedron;

export namespace Factory {
UPtr<Collider> createCollidable(const Base &factory,
                                const Vec3List &coordinates) {
  return std::make_unique<Collider>(
      factory.vertexCount, factory.faceCount, coordinates, factory.veIndices,
      factory.evIndices, factory.efIndices, factory.feIndices);
}
} // namespace Factory