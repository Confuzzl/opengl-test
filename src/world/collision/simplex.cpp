#include "simplex.h"

const Simplex::VertexNeighborList Simplex::veIndices{
    {0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}};
const Simplex::EdgeNeighborList Simplex::evIndices{{0, 1}, {1, 2}, {2, 0},
                                                   {2, 3}, {0, 3}, {1, 3}};
const Simplex::EdgeNeighborList Simplex::efIndices{{0, 2}, {0, 3}, {0, 1},
                                                   {1, 3}, {2, 1}, {3, 2}};
const Simplex::FaceEdgeIndexList Simplex::feIndices{
    {0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}};

Simplex::Simplex(const Vec3List &coordinates)
    : Polyhedron(4, coordinates, veIndices, evIndices, efIndices, feIndices) {}