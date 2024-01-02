export module factory.global:simplex;

import factory.base_factory;
import util.polyhedron;
import util.rendering;

export namespace Factory {
class Simplex : Base {
public:
  Simplex()
      : Base(4, 4, VEIndexList{{0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}},
             EVIndexList{{0, 1}, {1, 2}, {2, 0}, {2, 3}, {0, 3}, {1, 3}},
             EFIndexList{{0, 2}, {0, 3}, {0, 1}, {1, 3}, {2, 1}, {3, 2}},
             FEIndexList{{0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}},
             render::IndexList{
                 {{0, 1, 2}}, {{0, 2, 3}}, {{1, 0, 3}}, {{2, 1, 3}}},
             render::repeatFaces<render::Col>(
                 4, render::repeatTris<render::Col>(1,
                                                    {
                                                        {255, 255, 255},
                                                    })),
             render::repeatFaces<render::Tex>(4,
                                              {
                                                  {
                                                      {0, 0},
                                                      {1, 0},
                                                      {0.5, 1},
                                                  },
                                              }),
             12) {}
};
} // namespace Factory