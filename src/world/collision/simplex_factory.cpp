#include "simplex_factory.h"
#include "polyhedron.h"
#include "world/render/renderable.h"

const VertexNeighborList SimplexFactory::veIndices{
    {0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}};
const EdgeNeighborList SimplexFactory::evIndices{{0, 1}, {1, 2}, {2, 0},
                                                 {2, 3}, {0, 3}, {1, 3}};
const EdgeNeighborList SimplexFactory::efIndices{{0, 2}, {0, 3}, {0, 1},
                                                 {1, 3}, {2, 1}, {3, 2}};
const FaceNeighborList SimplexFactory::feIndices{
    {0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}};

const FaceVertexList SimplexFactory::fvIndices{
    {0, 1, 2}, {0, 2, 3}, {1, 0, 3}, {2, 1, 3}};

UPtr<Polyhedron> &&
SimplexFactory::createCollidableSimplex(const Vec3List &coordinates) {
  return std::make_unique<Polyhedron>(4, coordinates, veIndices, evIndices,
                                      efIndices, feIndices);
}

UPtr<Renderable> &&
SimplexFactory::createRenderableSimplex(const Vec3List &coordinates) {
  //return std::make_unique<Renderable>(coordinates, fvIndices);
}