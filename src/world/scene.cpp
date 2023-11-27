module world.scene;

import world.game_object;
import world.entity.player;
import app.app;
import util.debug;
import world.factory.factories;
import util.polyhedron;
import util.debug;

Scene::Scene() { std::cout << "scene constructing\n"; }
Scene::~Scene() = default;

void Scene::start() {
  try {
    Vec3List coordinates1{
        {-1, -1, +1}, {+1, -1, -1}, {+1, +1, +1}, {-1, +1, -1}};
    for (auto &v : coordinates1)
      v /= 2;

    Vec3List coordinates2{{-1, -1, 1},  {+1, -1, +1}, {+1, +1, +1},
                          {-1, +1, +1}, {-1, +1, -1}, {+1, +1, -1},
                          {+1, -1, -1}, {-1, -1, -1}};
    for (auto &v : coordinates2)
      v /= 2;

    auto &go1{GameObject::from(SIMPLEX_FACTORY, coordinates1)};
    go1.translate({2, 0, 0});
    testObject = &go1;

    auto &aaa{GameObject::from(SIMPLEX_FACTORY, coordinates1)};
    aaa.translate({3, 0, 0});

    auto &go2{GameObject::from(PRISM_FACTORY, coordinates2)};
    go2.translate({0, -2, 0});
    auto &go3{GameObject::from(PRISM_FACTORY, coordinates2)};
    go3.translate({0, 0, 2});
    auto &go4{GameObject::from(PRISM_FACTORY, coordinates2)};
    go4.translate({-2, 0, 0});
    auto &go5{GameObject::from(PRISM_FACTORY, coordinates2)};
    go5.translate({0, 0, -2});

    // auto &go2{GameObject::from(PRISM_FACTORY, coordinates2)};
    // go2.translate({0, -2, 0});
  } catch (const std::runtime_error &e) {
    mainApp.catchException(e);
  }
}