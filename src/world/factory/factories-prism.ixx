export module world.factory.factories:prism;

import world.factory.base_factory;
import util.polyhedron;

export class PrismFactory : public AbstractFactory {
public:
  PrismFactory()
      : AbstractFactory(
            8, 6,
            VertexNeighborList{},
            EdgeNeighborList{},
            EdgeNeighborList{},
            FaceNeighborList{},
            RFaceCoordinateIndexList{
                {},
            RFaceUVList{},
            36) {}
};