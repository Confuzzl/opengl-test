export module world.factory.factories:prism;

import world.factory.base_factory;
import util.polyhedron;

export class PrismFactory : public BaseFactory {
public:
  PrismFactory()
      : BaseFactory(
            8, 6,
            VertexNeighborList{{0, 3, 4},
                               {0, 1, 5},
                               {1, 2, 6},
                               {2, 3, 7},
                               {7, 9, 10},
                               {6, 10, 11},
                               {5, 8, 11},
                               {4, 8, 9}},
            EdgeNeighborList{{{0, 1},
                              {1, 2},
                              {2, 3},
                              {3, 0},
                              {7, 0},
                              {1, 6},
                              {5, 2},
                              {3, 4},
                              {6, 7},
                              {7, 4},
                              {4, 5},
                              {5, 6}}},
            EdgeNeighborList{{0, 5},
                             {0, 1},
                             {0, 4},
                             {0, 3},
                             {3, 5},
                             {1, 5},
                             {1, 4},
                             {3, 4},
                             {2, 5},
                             {2, 3},
                             {2, 4},
                             {2, 1}},
            FaceNeighborList{{0, 1, 2, 3},
                             {5, 11, 6, 1},
                             {8, 9, 10, 11},
                             {4, 3, 7, 9},
                             {6, 10, 7, 2},
                             {5, 0, 4, 8}},
            RFaceCoordinateIndexList{{{}, {}}, {{}}, {{}}, {{}}, {{}}, {{}}},
            RFaceUVList{
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
                {{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}},
            },
            36) {}
};