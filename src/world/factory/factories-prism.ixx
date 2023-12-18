export module world.factory.factories:prism;

import world.factory.base_factory;
import util.rendering;
import util.polyhedron;

export class PrismFactory : public BaseFactory {
public:
  PrismFactory()
      : BaseFactory(
            8, 6,
            VEIndexList{{0, 3, 4},
                        {0, 1, 5},
                        {1, 2, 6},
                        {2, 3, 7},
                        {7, 9, 10},
                        {6, 10, 11},
                        {5, 8, 11},
                        {4, 8, 9}},
            EVIndexList{{{0, 1},
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
            EFIndexList{{0, 5},
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
            FEIndexList{{0, 1, 2, 3},
                        {5, 11, 6, 1},
                        {8, 9, 10, 11},
                        {4, 3, 7, 9},
                        {6, 10, 7, 2},
                        {5, 0, 4, 8}},
            render::IndexList{{{0, 1, 2}, {0, 2, 3}},
                              {{1, 6, 5}, {1, 5, 2}},
                              {{6, 7, 4}, {6, 4, 5}},
                              {{7, 0, 3}, {7, 3, 4}},
                              {{3, 2, 5}, {3, 5, 4}},
                              {{7, 6, 1}, {7, 1, 0}}},
            render::repeatFaces<render::Col>(
                6, render::repeatTris<render::Col>(2, {{255, 255, 255}})),
            render::repeatFaces<render::Tex>(6,
                                             {
                                                 {{0, 0}, {1, 0}, {1, 1}},
                                                 {{0, 0}, {1, 1}, {0, 1}},
                                             }),
            36) {}
};