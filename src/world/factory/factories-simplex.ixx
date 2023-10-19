export module world.factory.factories:simplex;

import world.factory.base_factory;
import util.polyhedron;

export class SimplexFactory : public BaseFactory {
public:
  SimplexFactory()
      : BaseFactory(
            4, 4,
            VertexNeighborList{{0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}},
            EdgeNeighborList{{0, 1}, {1, 2}, {2, 0}, {2, 3}, {0, 3}, {1, 3}},
            EdgeNeighborList{{0, 2}, {0, 3}, {0, 1}, {1, 3}, {2, 1}, {3, 2}},
            FaceNeighborList{{0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}},
            RFaceCoordinateIndexList{
                {{0, 1, 2}}, {{0, 2, 3}}, {{1, 0, 3}}, {{2, 1, 3}}},
            RFaceUVList{{{{{0, 0}, {1, 0}, {0.5, 1}}}},
                        {{{{0, 0}, {1, 0}, {0.5, 1}}}},
                        {{{{0, 0}, {1, 0}, {0.5, 1}}}},
                        {{{{0, 0}, {1, 0}, {0.5, 1}}}}},
            12) {}
};